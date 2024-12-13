cmake_minimum_required(VERSION 3.16)

project(sparse_benchmark)

#random link

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Abseil requires C++14
set(CMAKE_CXX_STANDARD 20)

# Process Abseil's CMake build system
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/abseil-cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hopscotch-map)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unordered_dense)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hopscotch-map)

add_executable(benchmark benchmark.cc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -g")

target_include_directories(benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hopscotch-map/include ${CMAKE_CURRENT_SOURCE_DIR}/abseil-cpp/absl ${CMAKE_CURRENT_SOURCE_DIR}/unordered-dense/include)

# Declare dependency on the absl::strings library
target_link_libraries(benchmark unordered_dense::unordered_dense absl::container_memory absl::hash_container_defaults absl::raw_hash_set absl::algorithm_container absl::core_headers absl::memory absl::type_traits)
