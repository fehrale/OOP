cmake_minimum_required(VERSION 3.10)
project(lab7)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Указываем директории
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Находим все исходные файлы в директории и её поддиректориях
file(GLOB_RECURSE SRC_SOURCES LIST_DIRECTORIES false ${SRC_DIR}/*.cpp ${SRC_DIR}/*.tpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Добавляем исполняемый файл
add_executable(lab7 main.cpp ${SRC_SOURCES})
target_include_directories(lab7 PRIVATE ${INCLUDE_DIR})

# Добавляем исполняемый файл для тестов
add_executable(tests ${TEST_SOURCES} ${SRC_SOURCES})
target_include_directories(tests PRIVATE ${INCLUDE_DIR} ${SRC_DIR})
target_link_libraries(tests PRIVATE gtest gtest_main)

# Регистрация тестов
add_test(NAME MyProjectTests COMMAND tests)