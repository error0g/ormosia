# 生成链接库
aux_source_directory(. LIB_RUNTIME)
add_library (runtime STATIC ${LIB_RUNTIME})
