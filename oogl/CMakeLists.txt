aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (oogl ${DIR_LIB_SRCS})
add_subdirectory(shape2d)
add_subdirectory(shape3d)

