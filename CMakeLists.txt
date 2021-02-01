cmake_minimum_required(VERSION 3.0)

#项目信息
project(ormosia)
#将当前目录所有源文件的文件名赋值给变量 DIR_SRCS
aux_source_directory(. DIR_TOOT_SRCS)
#C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer ")
#头文件
include_directories("${PROJECT_SOURCE_DIR}/include")
#子目录
ADD_SUBDIRECTORY(./src)   
ADD_SUBDIRECTORY(./test)  
#将名为 DIR_TOOT_SRCS的源文件编译成一个名称为 Demo 的可执行文件。
add_executable(ormosia ${DIR_TOOT_SRCS})

target_link_libraries(ormosia Lexer Parser)