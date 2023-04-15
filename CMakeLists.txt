cmake_minimum_required(VERSION 3.22)
project(parkour)

set(CMAKE_C_STANDARD 99)

set(SDL2_DIR D:/CLion 2022.1.3/bin/mingw/x86_64-w64-mingw32)

include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/bin)

add_executable(parkour main.c Rect_Queue.c Rect_Queue.h parameter.h Player_Action.c Player_Action.h Monster_Model.c Monster_Model.h collision.c collision.h score.c score.h record.c record.h)

target_link_libraries(parkour mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)

