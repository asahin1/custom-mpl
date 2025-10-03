cmake_minimum_required(VERSION 3.16)
project(custom_mpl VERSION 1.0.0)

# Library target
add_library(custom_mpl INTERFACE)
target_include_directories(custom_mpl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(custom_mpl INTERFACE cxx_std_17)
add_library(custom_mpl::custom_mpl ALIAS custom_mpl)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS custom_mpl
  EXPORT custom_mplTargets
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/custom_mplConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  EXPORT custom_mplTargets
  NAMESPACE custom_mpl::
  DESTINATION lib/cmake/custom_mpl
)

configure_package_config_file(
  cmake/custom_mplConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/custom_mplConfig.cmake"
  INSTALL_DESTINATION lib/cmake/custom_mpl
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/custom_mplConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/custom_mplConfigVersion.cmake"
  DESTINATION lib/cmake/custom_mpl
)

option(CUSTOM_MPL_BUILD_EXAMPLES "Build examples" OFF)
option(CUSTOM_MPL_BUILD_TESTS "Build tests" OFF)
if(CUSTOM_MPL_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
if(CUSTOM_MPL_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
