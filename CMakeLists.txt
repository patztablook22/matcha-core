cmake_minimum_required(VERSION 3.17)
project(
  matcha VERSION 0.0
  DESCRIPTION "Attachable Machine Learning"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads)
find_package(Argxx)

add_library(${PROJECT_NAME} SHARED)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE 
    include/
)

target_link_libraries(matcha pthread)
target_link_libraries(matcha Argxx)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
    src/bits_of_matcha/tensor/expr.cpp
    src/bits_of_matcha/tensor/utils.cpp

    src/bits_of_matcha/tensor/dtype.cpp
    src/bits_of_matcha/tensor/shape.cpp
    src/bits_of_matcha/tensor/tensorbuffer.cpp
    src/bits_of_matcha/tensor/tensor.cpp

    src/bits_of_matcha/tensor/iterators/flatiterator.cpp
    src/bits_of_matcha/tensor/iterators/axisiterator.cpp

    src/bits_of_matcha/tensor/iterations/flatiteration.cpp
    src/bits_of_matcha/tensor/iterations/axisiteration.cpp

    src/bits_of_matcha/tensor/fn/fn.cpp
    src/bits_of_matcha/tensor/fn/elementwise.cpp

    src/bits_of_matcha/tensor/fn/add.cpp
    src/bits_of_matcha/tensor/fn/multiply.cpp

    src/bits_of_matcha/tensor/device/abstract/add.cpp
    src/bits_of_matcha/tensor/device/abstract/multiply.cpp

    src/bits_of_matcha/tensor/device/cpu.cpp
    src/bits_of_matcha/tensor/device/cpu/add.cpp
    src/bits_of_matcha/tensor/device/cpu/multiply.cpp

    src/bits_of_matcha/tensor/device/threadpool.cpp
    src/bits_of_matcha/tensor/device/threadpool/add.cpp
)

add_executable(
  main
  src/main.cpp
)

target_include_directories(
  main
  PRIVATE
    include/
)

target_link_libraries(main PUBLIC matcha)