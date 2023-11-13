cmake_minimum_required(VERSION 3.5)
project(octomap_ros)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
find_package(OCTOMAP REQUIRED)

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/conversions.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${OCTOMAP_INCLUDE_DIRS}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_${PROJECT_NAME}
    test/test_conversions.cpp
  )
  target_link_libraries(test_${PROJECT_NAME}
    gtest_main
    octomap
    octomap_ros
  )
endif()

ament_auto_package()
