#include "games/ZSGame.hpp"

int main()
{
  Eigen::MatrixXd payoff(2,2);
  payoff(0,0) = -2;
  payoff(0,1) = 3;
  payoff(1,0) = 3;
  payoff(1,1) = -4;

  ZSGame g(payoff);
  g.solve();
}
