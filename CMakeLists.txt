cmake_minimum_required (VERSION 3.17)

# projectname is the same as the main-executable
project(heavy_hitters)

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-std=c++17')

include_directories("${PROJECT_SOURCE_DIR}/processor")
include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories ("${PROJECT_SOURCE_DIR}/glog")
add_subdirectory(processor)
add_subdirectory(common)
add_subdirectory(glog)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} processor)
target_link_libraries(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} glog)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
