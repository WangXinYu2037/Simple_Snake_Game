cmake_minimum_required(VERSION 3.22)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

# 下面三条命令的根目录是cmake-build-debug

# 静态库文件目录
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
# 动态库文件目录
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
# 可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# 生成动态库
add_library(Game SHARED src/Game.cpp src/GamePlayer.cpp)

# 编译生成可执行文件
add_executable(Snake main.cpp)

# 与库文件link
target_link_libraries(Snake Game)
