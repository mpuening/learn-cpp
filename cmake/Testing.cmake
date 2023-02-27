#
# Add GoogleTest to project
#
include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.0
)

# For Windows, prevent overriding the parent project's ompiler/linker settings??
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(INSTALL_GMOCK "Install GMock" OFF)
option(INSTALL_GTEST "Install GTest" OFF)

FetchContent_MakeAvailable(googletest)

enable_testing()

include(googletest)
include(Memcheck)

macro(DiscoverTests target)
	target_link_libraries(${target} PRIVATE gtest_main gmock)
	gtest_discover_tests(${target})
	DoMemcheck(${target})
endmacro()
