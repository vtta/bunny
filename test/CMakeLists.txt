file (GLOB_RECURSE TEST_SOURCES "*.cpp")
add_library (test_static STATIC ${TEST_SOURCES})
