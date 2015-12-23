#pragma once

#include <Eigen/Core>

#include <vector>

/**
 * LIGame: Game with Lack of Information
 *
 * There is n games with payoffs matrix: A_1, ..., A_n
 * The distribution of probabilities of payoff matrices is: p_1, ..., p_n
 */

namespace stoch {

  class LIGame {
  private:
    std::vector<Eigen::MatrixXd> payoffs;//A_k
    Eigen::VectorXd probabilities;//p_k

  public:
    LIGame(const std::vector<Eigen::MatrixXd> & payoffs,
           const Eigen::VectorXd & distrib);

    void updateBelief(const Eigen::VectorXd & newBelief);

    void solve();
  };

}
