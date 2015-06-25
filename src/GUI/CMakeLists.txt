### Example of how to add a subdir's source files into our executable.
### The add_sources macro is defined in the project root CMakeLists.txt file.
### Just pass the various source files and it should do the rest.
message(STATUS "Inside src/GUI subdirectory")
add_sources(Wall.cpp Infogui.cpp Htmlstring.cpp TranspButt.cpp TuioManager.cpp)
