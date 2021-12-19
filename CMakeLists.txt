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

# dependencies
SET(Boost_USE_STATIC_LIBS   ON)


#set(Boost_ROOT "C:/Program Files/boost_1_75_0")
list(APPEND Boost_INCLUDE_DIRS "/home/patz/.config/vcpkg/inistalled/x64-linux/include")
set(Boost_DEBUG 1)
find_package(
  Boost 1.75
  REQUIRED COMPONENTS
  serialization
  container
  compute
  #parameter
)


add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME}
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_sources(matcha
  PRIVATE
    src/matcha/model.cpp
)


target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Boost::serialization
    # Boost::Parameter
    # Boost::Compute
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

#add_executable(main main.cpp)