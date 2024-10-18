cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление библиотеки с реализацией классов фигур
add_library(${CMAKE_PROJECT_NAME}_lib
    src/Square.cpp
    src/Rectangle.cpp
    src/Trapezoid.cpp
    src/Figure.cpp
    src/ShapeArray.cpp
)

# Главный исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

# Линковка библиотеки с фигурами к главному файлу
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

# Создание исполняемого файла для тестов
add_executable(tests test/FigureTest.cpp)

# Линковка библиотеки с фигурами и Google Test
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)

# Инструкции для сборки:
# 1. mkdir build && cd build
# 2. cmake ..
# 3. make
# 4. make test
