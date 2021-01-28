aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (Lexer ${DIR_LIB_SRCS})
add_library (Parser ${DIR_LIB_SRCS})