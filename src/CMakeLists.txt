include (${CMAKE_MODULE_PATH}/OF_include_dirs.cmake)
include (${CMAKE_MODULE_PATH}/OF_libs.cmake)
include (${CMAKE_MODULE_PATH}/OF_srcs_addons.cmake)
include (${CMAKE_MODULE_PATH}/OF_include_addons.cmake)
include (${CMAKE_MODULE_PATH}/OF_libs_addons.cmake)

message(STATUS "Inside src directory")

### Our include directories
include_directories (${includeOF} ${addonsInclude} ${CMAKE_CURRENT_SOURCE_DIR})

### Add here src subdirectories
add_subdirectory(Hello)
add_subdirectory(DataManager)
add_subdirectory(GUI)

### There is a catch with GLOB and that is that if you add a file in one of these directories
### you will have to manually re-build the project i.e  make createDebugConfig  or make createReleaseConfig
### in order for the new files to be added on the generated Makefiles
### Since this is used here for addons its not expected to add new files on those dirs so it should be ok , but
### keep it in mind as a general CMAKE rule
### Best CMAKE practice suggests to specify every single file individually and this is what should be done
### for application source code of course but for libs and addons this would be an overkill and would cause
### loss of some flexibility 

foreach(item ${addonSrcs})
	file(GLOB_RECURSE currentSrc RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${item}/*.cpp ${item}/*.c)
	list(APPEND addonSrcList ${currentSrc})
endforeach(item ${addonSrcs})


#message(STATUS "CURRENT INCLUDES: ${addonsInclude}")
#message(STATUS "CURRENT SOURCES: ${addonSrcList}")

### The source_files variables is shared amongst the various src subdirs and 
### soure files can be add using the add_sources macro defined on the root CMakeLists.txt
### independetely of the directory.
### Check ./Hello/CMakeLists.txt for more info.
list(APPEND source_files main.cpp testApp.cpp testApp.h ${addonSrcList} )


### A list with required core libraries
list(APPEND required_libraries ${libsOF})

###Now append the required addon libraries
list(APPEND required_libraries ${addonLibs})

### Target name
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(exeNameMode testAppDebug)
else()
	set(exeNameMode testAppRelease)
endif()

### Add the sources to our executable
add_executable(${exeNameMode} ${source_files})


### Find various libraries and add them to our libraries list
find_package (Glib REQUIRED)
if (GLIB_FOUND)
	include_directories (${GLIB_INCLUDE_DIRS})
	list(APPEND required_libraries ${GLIB_LIBRARIES})
endif (GLIB_FOUND)		

find_package(GStreamer REQUIRED)
if (GSTREAMER_FOUND)
	include_directories (${GSTREAMER_INCLUDE_DIR} ${GSTREAMER_BASE_INCLUDE_DIRS} ${GSTREAMER_APP_INCLUDE_DIRS} ${GSTREAMER_VIDEO_INCLUDE_DIRS})
	list(APPEND required_libraries ${GSTREAMER_LIBRARIES} ${GSTREAMER_BASE_LIBRARIES} ${GSTREAMER_APP_LIBRARIES} ${GSTREAMER_VIDEO_LIBRARIES})
endif (GSTREAMER_FOUND)

find_package(Cairo REQUIRED)
if (CAIRO_FOUND)
	include_directories(${CAIRO_INCLUDE_DIR})
	list(APPEND required_libraries ${CAIRO_LIBRARIES})
endif (CAIRO_FOUND)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRECTORIES})
    list(APPEND required_libraries ${OPENSSL_LIBRARIES})
endif (OPENSSL_FOUND)

### Finally link with the specified libraries
target_link_libraries(${exeNameMode} ${required_libraries})


