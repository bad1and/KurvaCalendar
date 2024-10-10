cmake_minimum_required(VERSION 3.29)
project(KurvaCalendar C)
set(CMAKE_C_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(KurvaCalendar test.c)
#add_executable(KurvaCalendar main.c)

target_link_libraries(KurvaCalendar ${CURSES_LIBRARIES})