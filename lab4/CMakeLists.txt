cmake_minimum_required(VERSION 3.10)
project(lab4)

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
# Для Windows: предотвращение переопределения настроек компилятора/линковщика родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Главный исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

# # Источники для библиотеки с фигурами
# set(FIGURES_HEADERS
#     include/Square.h
#     include/Rectangle.h
#     include/Trapezoid.h
#     include/Array.h
#     include/Figure.h
#     include/Point.h
# )

# Линковка библиотеки с фигурами к главному файлу
target_sources(${CMAKE_PROJECT_NAME}_exe PRIVATE ${FIGURES_HEADERS})

# Добавление тестов
enable_testing()

# Создание исполняемого файла для тестов
add_executable(tests test/FigureTest.cpp)

# Линковка библиотеки с фигурами и Google Test
target_sources(tests PRIVATE ${FIGURES_HEADERS})
target_link_libraries(tests PRIVATE gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)

# Инструкции для сборки:
# 1. mkdir build && cd build
# 2. cmake ..
# 3. make
# 4. make test