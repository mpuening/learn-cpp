#include <string>
#include <gtest/gtest.h>

// ==============================================

class SimpleClass {
public:
	SimpleClass() = default;
	~SimpleClass() = default;

	SimpleClass(const SimpleClass&) = delete;
	SimpleClass& operator=(const SimpleClass&) = delete;

	std::string sayHello(std::string name);
};

std::string SimpleClass::sayHello(std::string name) {
	return "Hello " + name;
}

// A function that tries to use copy c'tor
SimpleClass simpleClassFunction(SimpleClass copy) {
	// This is illegal, copy c'tor is deleted
	//return copy;

	// Do this instead
	return SimpleClass();
}

TEST(ClassesTest, DefaultConstructors) {

	SimpleClass first;
	EXPECT_EQ("Hello First", first.sayHello("First"));

	SimpleClass second = SimpleClass();
	EXPECT_EQ("Hello Second", second.sayHello("Second"));

	SimpleClass* third = new SimpleClass();
	EXPECT_EQ("Hello Third", third->sayHello("Third"));
	delete third;

	// This is illegal, copy c'tor is deleted
	// simpleClassFunction(first);

	// This is illegal, operator= is deleted
	// first = third;
}

// ==============================================

enum CopyType { DEFAULT_CTOR, COPY_CTOR, ASSIGNMENT };

static int destroyedCopies { };

class CopyCountTracker {
public:
	CopyCountTracker();
	~CopyCountTracker();

	CopyCountTracker(const CopyCountTracker& other);
	CopyCountTracker& operator=(const CopyCountTracker& other);

	int getCount();
	CopyType getType();

private:
	int _copyCount;
	CopyType _copyType;
};

CopyCountTracker::CopyCountTracker() :
		_copyCount(0),
		_copyType(CopyType::DEFAULT_CTOR) {
};

CopyCountTracker::~CopyCountTracker() {
	destroyedCopies++;
};

CopyCountTracker::CopyCountTracker(const CopyCountTracker& other) :
		_copyType(CopyType::COPY_CTOR) {
	this->_copyCount = other._copyCount + 1;
}

CopyCountTracker& CopyCountTracker::operator=(const CopyCountTracker& other) {
    if (this == &other)
        return *this;

    this->_copyCount = other._copyCount + 1;
    this->_copyType = CopyType::ASSIGNMENT;

    return *this;
}

int CopyCountTracker::getCount() {
	return this->_copyCount;
}

CopyType CopyCountTracker::getType() {
	return this->_copyType;
}

// A function that uses copy c'tor
CopyCountTracker copyCountTrackerFunction(CopyCountTracker copy, int currentCount) {
	EXPECT_EQ(currentCount + 1, copy.getCount());
	return copy;
}

void wastefulCopyCountTrackerFunction() {
	for (size_t i {}; i < 5; i++) {
		CopyCountTracker wasteful;
		EXPECT_EQ(CopyType::DEFAULT_CTOR, wasteful.getType());
		// exiting the loop should destroy the object
	}
}

TEST(ClassesTest, CopyConstructors) {

	EXPECT_EQ(0, destroyedCopies);

	CopyCountTracker first;
	EXPECT_EQ(0, first.getCount());
	EXPECT_EQ(CopyType::DEFAULT_CTOR, first.getType());

	EXPECT_EQ(0, destroyedCopies);

	// Use of copy constructor
	CopyCountTracker second = first;
	EXPECT_EQ(1, second.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, second.getType());

	EXPECT_EQ(0, destroyedCopies);

	// Two uses of copy constructor via parameter passing and initialization
	CopyCountTracker third = copyCountTrackerFunction(second, second.getCount());
	EXPECT_EQ(3, third.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, third.getType());

	EXPECT_EQ(1, destroyedCopies);

	// Direct use of copy constructor
	CopyCountTracker fourth = CopyCountTracker(third);
	EXPECT_EQ(4, fourth.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, fourth.getType());

	// Getting address of object is not a copy
	CopyCountTracker* fifth = &fourth;
	EXPECT_EQ(4, fifth->getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, fifth->getType());

	// Also, getting reference/alias to object is not a copy
	CopyCountTracker& sixth = *fifth;
	EXPECT_EQ(4, sixth.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, sixth.getType());

	// But de-referencing a pointer is an copy c'tor for initialization
	CopyCountTracker seventh = *fifth;
	EXPECT_EQ(5, seventh.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, seventh.getType());

	// And explicit assignment with existing variable
	seventh = *fifth;
	EXPECT_EQ(5, seventh.getCount());
	EXPECT_EQ(CopyType::ASSIGNMENT, seventh.getType());

	// Another copy c'tor (4+1 = 5)
	CopyCountTracker eighth = sixth;
	EXPECT_EQ(5, eighth.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, eighth.getType());

	// Detect self referencing in operator=, remains COPY_CTOR
	CopyCountTracker& altsixth = sixth;
	sixth = altsixth;
	EXPECT_EQ(4, sixth.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, sixth.getType());
	EXPECT_EQ(4, altsixth.getCount());
	EXPECT_EQ(CopyType::COPY_CTOR, altsixth.getType());

	// Verify the first didn't change
	EXPECT_EQ(0, first.getCount());
	EXPECT_EQ(CopyType::DEFAULT_CTOR, first.getType());

	EXPECT_EQ(1, destroyedCopies);

	// Wasteful function should create and destroy 5
	wastefulCopyCountTrackerFunction();
	EXPECT_EQ(6, destroyedCopies);
}
