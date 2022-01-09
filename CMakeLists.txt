cmake_minimum_required(VERSION 3.17)
project(
  matcha-core VERSION 0.0
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

target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} Argxx)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
    src/bits_of_matcha/tensor/expr.cpp
    src/bits_of_matcha/tensor/utils.cpp
    src/bits_of_matcha/tensor/scope.cpp

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

    src/bits_of_matcha/tensor/device/global.cpp
    src/bits_of_matcha/tensor/device/default.cpp
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

target_link_libraries(main PUBLIC ${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/matcha-coreConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS ${PROJECT_NAME}
    EXPORT matcha-coreTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/matcha-coreConfig.cmake"
    "${PROJECT_BINARY_DIR}/matcha-coreConfig.cmake"
    INSTALL_DESTINATION lib/cmake/matcha-core
)

install(EXPORT matcha-coreTargets DESTINATION lib/cmake/matcha-core)
install(FILES "${PROJECT_BINARY_DIR}/matcha-coreConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/matcha-coreConfig.cmake"
        DESTINATION lib/cmake/matcha-core)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)