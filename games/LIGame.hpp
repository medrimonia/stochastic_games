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

    int p1NbActions() const;

    double solve();

    /**
     * - One result by distribution
     * - For each result:
     *   - [0]: game value for the distribution
     *   - [1:k]: p_k
     */
    std::vector<Eigen::VectorXd> discretizedSolver(double discretizeStep);
  };

}
