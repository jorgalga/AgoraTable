
### ROOT PROJECT CMakeLists.txt ###

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

### Project name.
PROJECT(testAppOF)

set (CMAKE_COLOR_MAKEFILE ON)
#set (CMAKE_VERBOSE_MAKEFILE ON)

### The variables that are being set here propagate along the source tree and are available to subdir CMakeLists.txt files. ###

### Convenient macro to add srcs from child directories directly
### Found : http://stackoverflow.com/questions/7046956/populating-srcs-from-cmakelists-txt-in-subdirectories
set ( SOURCE_CODE_DIRECTORY "${CMAKE_SOURCE_DIR}/src" )
macro (add_sources)
	file (RELATIVE_PATH _relPath "${SOURCE_CODE_DIRECTORY}" "${CMAKE_CURRENT_SOURCE_DIR}")
	message(STATUS "${CMAKE_SOURCE_DIR}")
	foreach (_src ${ARGN})
		if (_relPath)
		   list(APPEND source_files "${_relPath}/${_src}")
		else ()
		   list(APPEND source_files "${_src}")
		endif ()
	endforeach()
	if (_relPath)
		#propagate source_files to parent directory
		set (source_files ${source_files} PARENT_SCOPE)
	endif()
endmacro()

### Check to see if the environment is set. 
### The path to the openFrameworks root dir is a prerequisite
set (OF_DIR $ENV{OF_ROOT})
if ( "${OF_DIR}" STREQUAL "" )
	message(FATAL_ERROR "
	**** 
	You must export the env variable OF_ROOT pointing to your openFrameworks root directory in order to proceed.. 
	Example: export OF_ROOT=/some/dir 
	Or you can add it permantly by modifying your .bashrc file 	
	NOTE: Always use absolute path to point to your openFrameworks installation
	****" )
endif()

### Where to find the various .cmake custom scripts like FindLib.cmake etc.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/aes_cmake_modules)

### The directory where your executable will be installed when running : make install 
set(CMAKE_INSTALL_PREFIX "/home/petroska/Desktop/${PROJECT_NAME}")

### Where we want our executable to be placed during the build phase
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

### Triggered by : make install . This will copy the binary
### folder and all subfolders in the directory specified by CMAKE_INSTALL_PREFIX
### If the dir doesnt exist it will be created automatically .
install ( DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	  DESTINATION "${CMAKE_INSTALL_PREFIX}"
	  PATTERN ".svn" EXCLUDE
	  PATTERN ".git" EXCLUDE
	)

set (dataDirectory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")
file(MAKE_DIRECTORY ${dataDirectory})

### This command here copies the contents of the root data folder to the build target data folder so it can be used from the application.
### This command is executed whenever you run make TARGET for the first time or when you run make releaseConfig / make debugConfig.
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data ${dataDirectory})

if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Debug CACHE STRING 
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel. " FORCE )
endif()

### Set various compiler flags depending on the target
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -Winvalid-pch -Wnon-virtual-dtor -Wsign-promo -Wshadow -Winit-self -Wno-unknown-pragmas -Wno-unused-parameter -Wno-write-strings")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wuninitialized")
endif(CMAKE_COMPILER_IS_GNUCXX)

### Add source subdirectory so that cmake propagates through the source tree and can find the various CMakeLists.txt files included in the src subdirs.
add_subdirectory (
		 src
		 )


