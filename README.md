Stochastic Games
================

#Introduction
This repository aims to provide tools for solving formal games such as Zero-Sum
games or games with lack of information. It is currently in development and is
not stable at all.

#Dependencies
This repository uses cmake system, it requires a c++11 compatible compiler.
The following libraries are needed:
- eigen3
- glpk (Gnu linear programming kit)

#Tests
The library built by the cmake provide some functional tests, they are compiled
when setting the "TESTS" option to "ON" in the CMakeCache

##test_glpk
A basic test provided by the glpk documentation.

##test_glpk2
This test solves a basic Zero-Sum game using glpk interface

##test_zs_game
This test solves a basic Zero-Sum game (the same as in glpk2) using our custom
interface

##test_li_game
This test solves a basic game with lack of information on both sides, the
distribution might be controlled by choosing an appropriate p-value

##test_li_discretize
This test solves a game with lack of information on both side with a
discretization of the possible distributions. It produces information on the
solving on stdout, the value of the game depending on the distribution used is
written as a csv file on stderr.