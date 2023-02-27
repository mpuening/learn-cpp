#include <gtest/gtest.h>

#include <array>

TEST(ArraysTest, ClassicArray) {

	int dimensions[3] { 1, 2, 3 };

	// New school iteration, no need to access array, refs are good
	for (auto &i : dimensions) {
		EXPECT_EQ(true, i >= 1 && i <= 3);
	}

	// Old school iteration
	int sum { };
	for (size_t i { }; i < std::size(dimensions); i++) {
		EXPECT_EQ(i + 1, dimensions[i]);
		sum += dimensions[i];
	}
	EXPECT_EQ(6, sum);
}

TEST(ArraysTest, Matrix) {

	int matrix[3][3] {

	{ 1, 2, 3 },

	{ 4, 5, 6 },

	{ 7, 8, 9 }

	};

	// Nested Iteration
	int sum { };
	for (auto &row : matrix) {
		for (auto &value : row) {
			sum += value;
		}
	}
	EXPECT_EQ(45, sum);
}

TEST(ArraysTest, StandardArray) {

	std::array<int, 3> dimensions = { 1, 2, 3 };

	EXPECT_EQ(1, dimensions[0]);
	EXPECT_EQ(2, dimensions[1]);
	EXPECT_EQ(3, dimensions[2]);

	int sum { };
	for (auto &i : dimensions) {
		sum += i;
	}
	EXPECT_EQ(6, sum);
}
