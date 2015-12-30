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

  int LIGame::p1NbActions() const
  {
    return payoffs[0].rows();
  }

  double LIGame::solve()
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
    return g.solve();
  }

  std::vector<Eigen::VectorXd> getBins(int nbBins, double stepSize, double remaining)
  {
    std::vector<Eigen::VectorXd> results;
    // If there is still several bins
    if (nbBins > 1) {
      // Adding all the possibilities where binValue is smaller than remaining
      for (double binValue = 0; binValue < remaining; binValue += stepSize) {
        std::vector<Eigen::VectorXd> childs;
        childs = getBins(nbBins - 1, stepSize, remaining - binValue);
        for (const auto & c : childs) {
          Eigen::VectorXd entry(nbBins);
          entry(0) = binValue;
          entry.segment(1,nbBins - 1) = c;
          results.push_back(entry);
        }
      }
    }
    // Adding a solution with all the binValue = remaining
    Eigen::VectorXd tmp = Eigen::VectorXd::Zero(nbBins);
    tmp(0) = remaining;
    results.push_back(tmp);
    return results;
  }

  std::vector<Eigen::VectorXd> LIGame::discretizedSolver(double discretizeStep)
  {
    // backuping old distrib
    auto oldDistrib = probabilities;
    // Computing results
    std::vector<Eigen::VectorXd> result, distributions;
    int nbGames = payoffs.size();
    // Possible arrangements by recursion
    distributions = getBins(nbGames, discretizeStep, 1.0);
    //TODO: solve games
    for (const auto & d : distributions) {
      updateBelief(d);
      Eigen::VectorXd entry = Eigen::VectorXd::Zero(nbGames + 1);
      entry(0) = solve();
      entry.segment(1, nbGames) = d;
      result.push_back(entry);
    }
    // Restore old distrib
    updateBelief(oldDistrib);
    return result;
  }

}
