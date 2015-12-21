cmake_minimum_required (VERSION 2.6)
project (stochastic_games)
find_package (Threads)

option (TESTS
    "Compile tests" OFF)

#Enable C++11
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")

find_package(PkgConfig)
pkg_search_module(EIGEN REQUIRED eigen3)

set (DIRECTORIES 
    games
    )

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

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${EIGEN_INCLUDE_DIRS}"
)

add_library (stochastic_games ${ALL_SOURCES})

set (EXTRA_LIBS pthread)
set (EXTRA_LIBS ${EXTRA_LIBS} m stochastic_games glpk)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${BINARY_DIR})

if (TESTS)
    add_executable (test_zs_game tests/test_zs_game.cpp)
    target_link_libraries (test_zs_game ${EXTRA_LIBS})

    add_executable (test_glpk tests/test_glpk.cpp)
    target_link_libraries (test_glpk ${EXTRA_LIBS})

    add_executable (test_glpk2 tests/test_glpk2.cpp)
    target_link_libraries (test_glpk2 ${EXTRA_LIBS})
endif (TESTS)
