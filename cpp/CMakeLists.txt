project(robotics_v1_entry)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(robotics_v1_entry main.cpp Solution.cpp utils/Image.cpp)

target_link_libraries(robotics_v1_entry pthread)

