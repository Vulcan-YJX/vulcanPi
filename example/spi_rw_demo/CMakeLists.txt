
project(spi_rw_demo)

set(vulcanPiRootPath "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include_directories(${vulcanPiRootPath}/include)
list(APPEND vulcanSpiSourceFiles ${vulcanPiRootPath}/src/vulcanSpi.cpp)

add_executable(${PROJECT_NAME} main.cpp ${vulcanSpiSourceFiles})
target_link_libraries( ${PROJECT_NAME} pthread)

install(TARGETS spi_rw_demo RUNTIME DESTINATION bin)

