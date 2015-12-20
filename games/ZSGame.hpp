#pragma once

#include <glpk.h>
#include <Eigen/Core>

namespace stoch {

  class ZSGame {
  private:
    glp_prob * lp;
    int rows;
    int cols;

  public:
    ZSGame(const Eigen::MatrixXd & payoff);
    ~ZSGame();

    void solve();

  };
}
