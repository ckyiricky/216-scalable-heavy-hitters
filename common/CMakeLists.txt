include_directories(${PROJECT_SOURCE_DIR}/glog)
aux_source_directory(. DIR_LIB_SRCS)
add_library(common ${DIR_LIB_SRCS})
target_link_libraries(common glog)
