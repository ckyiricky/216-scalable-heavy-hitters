include_directories ("${PROJECT_SOURCE_DIR}/glog")
include_directories ("${PROJECT_SOURCE_DIR}/common")
aux_source_directory(. DIR_LIB_SRCS)

add_library(processor ${DIR_LIB_SRCS})
target_link_libraries(processor glog)
target_link_libraries(processor common)
