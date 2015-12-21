#pragma once

#include <glpk.h>
#include <Eigen/Core>

#include <vector>

namespace stoch {

  class ZSGame {
  private:
    glp_prob * lp;
    int rows;
    int cols;

    std::vector<std::string> colNames, rowNames;

  public:
    ZSGame(const Eigen::MatrixXd & payoff);
    ~ZSGame();

    void solve();

  };
}
