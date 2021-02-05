cmake_minimum_required(VERSION 3.0)

#项目信息
project(ormosia)
aux_source_directory(. DIR_TOOT_SRCS)
#C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -fno-omit-frame-pointer ")
#头文件
include_directories("${PROJECT_SOURCE_DIR}/include")
#子目录
ADD_SUBDIRECTORY(./src)   
ADD_SUBDIRECTORY(./test)   

add_executable(ormosia ${DIR_TOOT_SRCS})

target_link_libraries(ormosia Lexer Parser)