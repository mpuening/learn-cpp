#include <gtest/gtest.h>

#include <array>

/*

 A unique_ptr has exclusive ownership of an object. No one else maintains a
 pointer to the object. The unique_ptr disallows making a copy of itself.
 When the unique_ptr goes out of scope, the object is freed,

 A shared_ptr maintains a reference count of pointers to an object. When
 the count goes to zero, the object is freed.

 A weak_ptr is linked to shared_ptrs. They do not participate in the reference
 counting, but at the expense of not allowing access to the object. To access
 the object, one must create a shared_ptr from the weak_ptr, thus increasing
 the reference count.

 */
TEST(PointersTest, ConstPointers) {

	int a { 1 };
	int b { 2 };
	int c { 3 };
	int d { 4 };

	// Pointers are constants
	const int *values[] = { &a, &b, &c, &d };
	EXPECT_EQ(4, std::size(values));

	values[0] = &b;
	EXPECT_EQ(2, *values[0]);

	const int const *constants[] = { &a, &b, &c, &d };
	EXPECT_EQ(4, std::size(constants));

	// This is illegal, what is referred to pointer is const
	//constants[0] = &b;
}

// ==============================================

static int pointerClassesCreated { };
static int pointerClassesDeleted { };

void resetPointerClassMetrics() {
	pointerClassesCreated = 0;
	pointerClassesDeleted = 0;
}

class PointerClass {
public:
	PointerClass();
	~PointerClass();

	PointerClass(const PointerClass&) = delete;
	PointerClass& operator=(const PointerClass&) = delete;

	std::string getName();
};

PointerClass::PointerClass() {
	pointerClassesCreated++;
}

PointerClass::~PointerClass() {
	pointerClassesDeleted++;
}

std::string PointerClass::getName() {
	return "PointerClass";
}

void testUniquePointer() {
	auto ptr { std::make_unique<PointerClass>() };
	EXPECT_EQ("PointerClass", ptr->getName());

	// Alternatively
	EXPECT_EQ("PointerClass", ptr.get()->getName());

	// Illegal to make copy
	//std::unique_ptr copy = ptr;

	// delete old, get new
	//ptr.reset(new PointerClass());

	// forces called to manage the delete call (better get hold of ptr first!)
	//ptr.release();
}

void testSharedPointer(std::shared_ptr<PointerClass> ptr) {
	// Still only one object
	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(0, pointerClassesDeleted);

	EXPECT_EQ("PointerClass", ptr->getName());

	// Alternatively
	EXPECT_EQ("PointerClass", ptr.get()->getName());
}

void testSharedPointer() {
	auto ptr = std::make_shared<PointerClass>();

	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(0, pointerClassesDeleted);

	std::shared_ptr<PointerClass> copy1 = ptr;
	std::shared_ptr<PointerClass> copy2 = copy1;
	testSharedPointer(copy2);

	// Still one object hanging around
	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(0, pointerClassesDeleted);
}

// ==============================================

TEST(PointersTest, UniquePtr) {
	resetPointerClassMetrics();

	testUniquePointer();

	// Objects should be cleaned up now
	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(1, pointerClassesDeleted);
}

TEST(PointersTest, SharedPtr) {
	resetPointerClassMetrics();

	testSharedPointer();

	// Object is out of scope now, freed
	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(1, pointerClassesDeleted);
}

TEST(PointersTest, WeakPtr) {
	resetPointerClassMetrics();

	// TODO
}

TEST(PointersTest, Reference) {

	int a { 1 };

	// reference or alias
	int& ref { a };
	ref++;

	EXPECT_EQ(2, a);
	EXPECT_EQ(2, ref);
}

TEST(PointersTest, OldSchoolNew) {

	resetPointerClassMetrics();

	PointerClass *ptr { };

	EXPECT_EQ(nullptr, ptr);

	ptr = new PointerClass();
	EXPECT_NE(nullptr, ptr);

	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(0, pointerClassesDeleted);

	delete ptr;

	EXPECT_EQ(1, pointerClassesCreated);
	EXPECT_EQ(1, pointerClassesDeleted);
}

TEST(PointersTest, OldSchoolNewArray) {

	resetPointerClassMetrics();

	PointerClass *ptr { };

	EXPECT_EQ(nullptr, ptr);

	int numberToCreate = 5;

	ptr = new PointerClass[numberToCreate] { };
	EXPECT_NE(nullptr, ptr);

	EXPECT_EQ(numberToCreate, pointerClassesCreated);
	EXPECT_EQ(0, pointerClassesDeleted);

	delete[] ptr;

	EXPECT_EQ(numberToCreate, pointerClassesCreated);
	EXPECT_EQ(numberToCreate, pointerClassesDeleted);
}

TEST(PointersTest, BeCarefulWhatYouAllocate) {

	// This is allocating just one integer, whose value is 10
	int *onlyOneInteger { new int { 10 } };
	EXPECT_EQ(10, *onlyOneInteger);

	delete onlyOneInteger;

	// This is allocating aonly_one_integer
	int *arrayOfIntegers { new int[10] };

	delete[] arrayOfIntegers;
}
