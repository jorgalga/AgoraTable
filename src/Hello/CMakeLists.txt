### Example of how to add a subdir's source files into our executable.
### The add_sources macro is defined in the project root CMakeLists.txt file.
### Just pass the various source files and it should do the rest.
message(STATUS "Inside src/Hello subdirectory")
add_sources(Hello.cpp)
