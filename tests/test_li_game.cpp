#include "games/LIGame.hpp"

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

  double p = 3.0 / 4;
  
  Eigen::Vector2d distrib;
  distrib(0) = p;
  distrib(1) = 1 - p;

  std::vector<Eigen::MatrixXd> payoffs = {a,b};

  LIGame g(payoffs, distrib);
  g.solve();
}
