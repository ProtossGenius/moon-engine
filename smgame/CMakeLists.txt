aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (smgame ${DIR_LIB_SRCS})
add_subdirectory(sample)
add_subdirectory(space)

