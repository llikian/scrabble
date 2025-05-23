# Global Project Configuration
cmake_minimum_required(VERSION 3.26)
project(Scrabble)

# Compiler options
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ffast-math")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Set sources and includes
set(SOURCES
        src/Application.cpp
        src/Bag.cpp
        src/Board.cpp
        src/Dictionary.cpp
        src/Hand.cpp
        src/Move.cpp
        src/Player.cpp
        src/Position.cpp
        src/Spot.cpp
        src/State.cpp
)

set(INCLUDES
        include
)

set(LIBRARIES

)

# Executable
add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

# Include Directories & Libraries
if(WIN32)
    set(SDL2_PATH "C:/Libs/SDL2")

    target_link_directories(${PROJECT_NAME} PUBLIC ${SDL2_PATH}/lib/x64/)

    set(INCLUDES ${INCLUDES} ${SDL2_PATH}/include ${SDL2_TTF_PATH}/include)
    set(LIBRARIES ${LIBRARIES} SDL2main SDL2 SDL2_ttf)
else()
    find_package(SDL2 REQUIRED)

    set(INCLUDES ${INCLUDES} ${SDL2_INCLUDE_DIRS})
    set(LIBRARIES ${LIBRARIES} SDL2 SDL2_ttf)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

# Tests Executable
add_executable(tests src/test.cpp ${SOURCES})
target_include_directories(tests PUBLIC ${INCLUDES})
target_link_libraries(tests PUBLIC ${LIBRARIES})

# Board Tests Executable
add_executable(board_tests src/board_tests.cpp ${SOURCES})
target_include_directories(board_tests PUBLIC ${INCLUDES})
target_link_libraries(board_tests PUBLIC ${LIBRARIES})

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
