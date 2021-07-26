cmake_minimum_required(VERSION 3.0)
project(ormosia)
#C++
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -fno-omit-frame-pointer ")

#编译器
SET(COMPILER src/compiler/compiler.cpp)
SET(OVM src/runtime/OVM.cpp)
#头文件
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src/include")
#子目录
ADD_SUBDIRECTORY(src/parser)   
# ADD_SUBDIRECTORY(runtime vm)  
# 生成文件
ADD_EXECUTABLE(ormosiac ${COMPILER})
ADD_EXECUTABLE(ovm ${OVM})
TARGET_LINK_LIBRARIES(ormosiac parser)