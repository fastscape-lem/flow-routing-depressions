cmake_minimum_required(VERSION 3.1)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(fastscapelib-benchmarks)

    find_package(xtensor REQUIRED CONFIG)
    set(XTENSOR_INCLUDE_DIR ${xtensor_INCLUDE_DIR})
    find_package(fastscapelib REQUIRED CONFIG)
    set(FASTSCAPELIB_INCLUDE_DIR ${fastscapelib_INCLUDE_DIRS})
endif ()


include(CheckCXXCompilerFlag)


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wunused-parameter -Wextra -Wreorder -Wconversion")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -D_GLIBCXX_DEBUG")

    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)

    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- fastscapelib requires C++14 support!")
    endif()
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
	SET(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG /fp:fast")
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
	add_definitions(-D_USE_MATH_DEFINES)
endif()


set(FASTSCAPELIB_BENCHMARK_SRC
  main.cpp
  benchmark.cpp
  benchmark.hpp
  dbg_output.hpp
  random_benchmark.cpp
  random_benchmark.hpp
  fastscape_benchmark.cpp
  fastscape_benchmark.hpp
  benchmark_sinks.cpp
  benchmark_basin_graph.cpp
  examples.hpp
  voronoi.cpp
  jail.cpp
  mountain.cpp
  bm_types.hpp
)

set(FASTSCAPELIB_BENCH_TARGET benchmarks_fastscapelib)

add_executable(${FASTSCAPELIB_BENCH_TARGET}
  EXCLUDE_FROM_ALL ${FASTSCAPELIB_BENCHMARK_SRC})

target_link_libraries(${FASTSCAPELIB_BENCH_TARGET} fastscapelib)

add_custom_target(run_benchmarks
    COMMAND benchmarks_fastscapelib
    DEPENDS ${FASTSCAPELIB_BENCHMARK_TARGET})
