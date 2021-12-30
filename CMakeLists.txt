cmake_minimum_required(VERSION 3.17)
project(
  matcha VERSION 0.0
  DESCRIPTION "Attachable Machine Learning"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE /home/patz/.config/vcpkg/scripts/buildsystems/vcpkg.cmake)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)
set(CMAKE_INSTALL_PREFIX /home/patz/Heap/matcha/install)

add_library(${PROJECT_NAME} SHARED)
add_executable(main src/main.cpp)

# dependencies
# reeeeeeeeeeEEEEEEEEEEEEEEEEEEE

find_package(Boost COMPONENTS REQUIRED serialization)

target_include_directories(${PROJECT_NAME}
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(matcha
  PRIVATE
    src/matcha/tensor.cpp
    src/matcha/tio.cpp

    src/matcha/iterations/flatiteration.cpp
    src/matcha/iterations/axisiteration.cpp
    src/matcha/iterators/flatiterator.cpp
    src/matcha/iterators/axisiterator.cpp

    src/matcha/fn/fn.cpp
    src/matcha/fn/elementwiseunary.cpp
    src/matcha/fn/elementwisebinary.cpp

    src/matcha/fn/add.cpp
    src/matcha/fn/subtract.cpp
    src/matcha/fn/multiply.cpp
    src/matcha/fn/divide.cpp

    src/matcha/fn/matmul.cpp

    src/matcha/fn/square.cpp
    src/matcha/fn/pow.cpp
    src/matcha/fn/exp.cpp

    src/matcha/fn/sum.cpp
    src/matcha/fn/max.cpp

    src/matcha/fn/softmax.cpp
    src/matcha/fn/relu.cpp

    src/matcha/fn/accuracy.cpp

    src/matcha/data/batch.cpp
    src/matcha/data/batches.cpp
    src/matcha/data/instance.cpp

    src/matcha/dataset/csv.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    Boost::serialization
)

target_link_libraries(
  main
  ${PROJECT_NAME}
)

target_include_directories(
  main
  PRIVATE
  include/
)

include(GNUInstallDirs)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Config"
  # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY include
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/.."
)

install(
  EXPORT "${PROJECT_NAME}Config"
  FILE "${PROJECT_NAME}Config.cmake"
  # NAMESPACE "matcha::"
  DESTINATION cmake
)
