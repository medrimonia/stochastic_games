#include "games/LIGame.hpp"

#include <iostream>

using stoch::LIGame;

int main()
{
  Eigen::MatrixXd a(2,3);
  a(0,0) =  4;
  a(1,0) =  4;
  a(0,1) =  0;
  a(1,1) =  0;
  a(0,2) =  2;
  a(1,2) = -2;
  Eigen::MatrixXd b(2,3);
  b(0,0) =  0;
  b(1,0) =  0;
  b(0,1) =  4;
  b(1,1) =  4;
  b(0,2) = -2;
  b(1,2) =  2;
  Eigen::MatrixXd c(2,3);
  b(0,0) =  3;
  b(1,0) =  -3;
  b(0,1) =  0;
  b(1,1) =  2;
  b(0,2) = -4;
  b(1,2) =  0;

  Eigen::Vector3d distrib;
  distrib(0) = 1.0 / 3;
  distrib(1) = 1.0 / 3;
  distrib(2) = 1.0 / 3;

  std::vector<Eigen::MatrixXd> payoffs = {a,b,c};

  LIGame g(payoffs, distrib);
  auto entries = g.discretizedSolver(0.01);

  std::cerr << "val" << ",";
  for (int row = 1; row < entries[0].rows() - 1; row ++){
    std::cerr << "p" << row << ",";
  }
  std::cerr << "p" << (entries[0].rows() - 1) << std::endl;

  for (const auto &e : entries) {
    for (int row = 0; row < e.rows() - 1; row ++){
      std::cerr << e(row) << ",";
    }
    std::cerr << e(e.rows() - 1) << std::endl;
  }
}
