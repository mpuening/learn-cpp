#include <gtest/gtest.h>

#include <string>

TEST(PrimitivesTest, Chars) {

	// New school
	auto a { 'a' };
	EXPECT_EQ('a', a);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(1, size_of_a);

	// Old school
	char b = 'b';
	EXPECT_EQ('b', b);

	int size_of_b = sizeof b;
	EXPECT_EQ(1, size_of_b);

	b = a;
	EXPECT_EQ('a', b);

	const auto c = 'c';
	EXPECT_EQ('c', c);

	// Not allowed, const
	// c = a;

	unsigned char u = 'A';
	auto i = static_cast<int>(u);
	EXPECT_EQ(65, i);

	EXPECT_EQ(false, isupper(a));
	EXPECT_EQ(true, islower(a));
	EXPECT_EQ(true, isalpha(a));
	EXPECT_EQ(false, isdigit(a));
	EXPECT_EQ(true, isxdigit(a));
	EXPECT_EQ(true, isalnum(a));
	EXPECT_EQ(false, isspace(a));
	EXPECT_EQ(false, isblank(a));
	EXPECT_EQ(false, ispunct(a));
	EXPECT_EQ(true, isprint(a));
	EXPECT_EQ(false, iscntrl(a));
	EXPECT_EQ(true, isgraph(a));
}

TEST(PrimitivesTest, Shorts) {

	// New school
	short a { 1 };
	EXPECT_EQ(1, a);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(2, size_of_a);

	// Old school
	short b = 2;
	EXPECT_EQ(2, b);

	int size_of_b = sizeof b;
	EXPECT_EQ(2, size_of_b);

	b = a;
	EXPECT_EQ(1, b);
}

TEST(PrimitivesTest, Ints) {

	// New school
	int a { 1 };
	EXPECT_EQ(1, a);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(4, size_of_a);

	// Old school
	int b = 2;
	EXPECT_EQ(2, b);

	int size_of_b = sizeof b;
	EXPECT_EQ(4, size_of_b);

	b = a;
	EXPECT_EQ(1, b);
}

TEST(PrimitivesTest, Longs) {

	// New school
	long a { 1 };
	EXPECT_EQ(1, a);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(8, size_of_a);

	// Old school
	long b = 2;
	EXPECT_EQ(2, b);

	int size_of_b = sizeof b;
	EXPECT_EQ(8, size_of_b);

	b = a;
	EXPECT_EQ(1, b);
}

TEST(PrimitivesTest, Floats) {

	// New school
	float a { 1.01 };
	EXPECT_EQ(true, abs(1.01 - a) < 0.01);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(4, size_of_a);

	// Old school
	float b = 2.01e2;
	EXPECT_EQ(2.01e2, b);
	EXPECT_EQ(true, abs(2.01e2 - b) < 0.01);

	int size_of_b = sizeof b;
	EXPECT_EQ(4, size_of_b);

	b = a;
	EXPECT_EQ(true, abs(1.01 - b) < 0.01);
}

TEST(PrimitivesTest, Doubles) {

	// New school
	double a { 1.01 };
	EXPECT_EQ(true, abs(1.01 - a) < 0.01);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(8, size_of_a);

	// Old school
	double b = 2.01e2;
	EXPECT_EQ(2.01e2, b);
	EXPECT_EQ(true, abs(2.01e2 - b) < 0.01);

	int size_of_b = sizeof b;
	EXPECT_EQ(8, size_of_b);

	b = a;
	EXPECT_EQ(true, abs(1.01 - b) < 0.01);
}

TEST(PrimitivesTest, LongDoubles) {

	// New school
	long double a { 1.01 };
	EXPECT_EQ(true, abs(1.01 - a) < 0.01);

	auto size_of_a { sizeof(a) };
	EXPECT_EQ(16, size_of_a);

	// Old school
	long double b = 2.01e2;
	EXPECT_EQ(2.01e2, b);
	EXPECT_EQ(true, abs(2.01e2 - b) < 0.01);

	int size_of_b = sizeof b;
	EXPECT_EQ(16, size_of_b);

	b = a;
	EXPECT_EQ(true, abs(1.01 - b) < 0.01);
}

TEST(PrimitivesTest, Unicode) {

	char32_t utf32 { L'A' };
	EXPECT_EQ('A', static_cast<char>(utf32));

	auto size_of_utf32 { sizeof(utf32) };
	EXPECT_EQ(4, size_of_utf32);
}

int whatType(int i) {
	return 1;
}

int whatType(unsigned long l) {
	return 2;
}

int whatType(float f) {
	return 3;
}

int whatType(double d) {
	return 4;
}

TEST(PrimitivesTest, CarelessAuto) {

	// Don't always let the compiler guess your types
	auto a { 10 };
	EXPECT_EQ(1, whatType(a));

	auto b { 1UL };
	EXPECT_EQ(2, whatType(b));

	auto c { 1.0 };
	EXPECT_EQ(4, whatType(c));

	auto d { static_cast<float>(c) };
	EXPECT_EQ(3, whatType(d));
}
