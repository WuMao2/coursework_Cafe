cmake_minimum_required(VERSION 3.10)

project(CafeManagement)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp"
                  "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})
