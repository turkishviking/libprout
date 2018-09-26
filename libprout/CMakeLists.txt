cmake_minimum_required(VERSION 3.9)
set (CMAKE_CXX_STANDARD 11)
project(libprout)
set(CPACK_PACKAGE_NAME "libprout")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")

set(VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
# Only print these messages once, even if libprout is added multiple times via add_subdirectory()
if (NOT TARGET libprout)
   message(STATUS "Using CMake version: ${CMAKE_VERSION}")
   message(STATUS "Compiling libprout version: ${VERSION}")
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR/utils})

include(GNUInstallDirs)

#add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER libprout.h)


#install(TARGETS libprout DESTINATION lib)
install(FILES libprout.h DESTINATION include)



#target_link_libraries(${PROJECT_NAME})
