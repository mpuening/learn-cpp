add_executable(
	learn_cpp_test

	primitives_test.cpp
	arrays_test.cpp
	math_test.cpp
	pointers_test.cpp
	string_test.cpp
	classes_test.cpp
	inheritence_test.cpp
	polymorphism_test.cpp
	exceptions_test.cpp
	templates_test.cpp
	move_test.cpp
	lambdas_test.cpp
	vector_test.cpp
	map_test.cpp
	concurrency_test.cpp
	regex_test.cpp
)

DiscoverTests(learn_cpp_test)
