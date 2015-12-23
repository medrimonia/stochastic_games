#include "LIGame.hpp"

#include "ZSGame.hpp"

#include <iostream>

namespace stoch {

  LIGame::LIGame(const std::vector<Eigen::MatrixXd> & payoffs_,
                 const Eigen::VectorXd & distrib)
    : payoffs(payoffs_), probabilities(distrib)
  {
    if (payoffs.size() != (size_t) distrib.rows()) {
      throw std::logic_error("LIGame: Payoff size does not match distrib size");
    }
    if (payoffs.size() == 0) {
      throw std::logic_error("LIGame: 0 payoff matrix provided");
    }

    auto matrixSize = payoffs[0].size();
    for (const auto & p : payoffs) {
      if (matrixSize != p.size()) {
        throw std::logic_error("LIGame: All payoff matrix must have the same dimensions");
      }
    }
  }

  void LIGame::updateBelief(const Eigen::VectorXd & newBelief)
  {
    if (newBelief.rows() != probabilities.rows()) {
        throw std::logic_error("LIGame: New distrib must have the same size as previous belief");
    }
    probabilities = newBelief;
  }

  void LIGame::solve()
  {
    Eigen::MatrixXd globalPayoff = Eigen::MatrixXd::Zero(payoffs[0].rows(), payoffs[0].cols());
    for (size_t i = 0; i < payoffs.size(); i++) {
      std::cout << "A_i:" << std::endl << payoffs[i] << std::endl;
      std::cout << "p_i: " << probabilities(i) << std::endl;
      globalPayoff +=  payoffs[i] * probabilities(i);
    }

    std::cout << "Solving game with the following payoff" << std::endl
              << globalPayoff << std::endl;
    ZSGame g(globalPayoff);
    g.solve();
  }

}
