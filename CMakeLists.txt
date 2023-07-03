cmake_minimum_required(VERSION 3.11)

project(roguelike)

cmake_policy(SET CMP0054 NEW)
set(CMAKE_CXX_STANDARD 17)

if(NOT RAYLIB_INCLUDE_DIR)
  set(RAYLIB_INCLUDE_DIR "./external/raylib/include")
endif()

if(NOT RAYLIB_LIB_DIR)
  set(RAYLIB_LIB_DIR "./external/raylib/lib")
endif()

set(game_sources)
foreach(dir ./src)
    file(GLOB sources ${dir}/*.cpp)
    list(APPEND game_sources ${sources})
endforeach()

set(game_resources)
file(GLOB resources "./src/res/*")
list(APPEND game_resources ${resources})


if(RAYLIB_INCLUDE_DIR)
  include_directories(BEFORE SYSTEM ${RAYLIB_INCLUDE_DIR})
else()
  message(STATUS "RAYLIB_INCLUDE_DIR is not defined!")
endif()

if (RAYLIB_LIB_DIR)
    link_directories(${RAYLIB_LIB_DIR})
else()
    message(STATUS "RAYLIB_LIB_DIR is not defined!")
endif()

add_executable(${PROJECT_NAME} ${game_sources})

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        raylib
        winmm
    )
else()
    target_link_libraries(${PROJECT_NAME}
        raylib
    )
endif()

file(COPY ${game_resources} DESTINATION "res/")