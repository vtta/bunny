file (GLOB_RECURSE LIB_SOURCES "*.cpp")
add_library (test_static STATIC ${LIB_SOURCES})
