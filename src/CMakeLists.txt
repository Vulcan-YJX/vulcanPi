
cmake_minimum_required(VERSION 3.0)

file(GLOB vulcanPi_SRC "*.cpp")

message(STATUS "vulcanPiRootPath lib : ${CMAKE_CURRENT_SOURCE_DIR}/../include/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

option(SERIAL_BUILD_SHARED_LIBS "Build vulcanPi_HEADERS shared library" ON)

if (SERIAL_BUILD_SHARED_LIBS)
  set(LibType SHARED)
else()
  set(LibType STATIC)
endif()

add_library(vulcanPi ${LibType} ${vulcanPi_SRC} )

target_include_directories(vulcanPi PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")  

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/bin
install(TARGETS vulcanPi DESTINATION lib)

# On Linux, "sudo make install" will typically copy the
# folder into /usr/local/include
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include DESTINATION include)
