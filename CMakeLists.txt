cmake_minimum_required (VERSION 2.6)
project (stochastic_games)
find_package (Threads)

#Enable C++11
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")

find_package(PkgConfig)
pkg_search_module(EIGEN REQUIRED eigen3)

set (DIRECTORIES 
    games
    )

if (TESTS)
  set (DIRECTORIES
    ${DIRECTORIES}
    tests)
endif (TESTS)

# Sub sources
foreach (DIRECTORY ${DIRECTORIES})
    message("-- stochastic_games: Adding ${DIRECTORY}/")
    set(SOURCES)
    set(GRAPHIC_SOURCES)
    include (${DIRECTORY}/Sources.cmake)

    set (PREFIXED_SOURCES)
    foreach (SOURCE ${SOURCES})
        set (PREFIXED_SOURCES ${PREFIXED_SOURCES} ${DIRECTORY}/${SOURCE})
    endforeach (SOURCE)

    set (ALL_SOURCES ${ALL_SOURCES} ${PREFIXED_SOURCES})
endforeach (DIRECTORY)

message(
  "EigenInc: ${EIGEN_INCLUDE_DIRS}")

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${EIGEN_INCLUDE_DIRS}"
)

add_library (stochastic_games ${ALL_SOURCES})

set (EXTRA_LIBS pthread)
set (EXTRA_LIBS ${EXTRA_LIBS} RhobanMath)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${BINARY_DIR})

if (TESTS)
    add_executable (test_zs_game tests/test_zs_game.cpp)
    target_link_libraries (test_zs_game ${EXTRA_LIBS})
endif (TESTS)
