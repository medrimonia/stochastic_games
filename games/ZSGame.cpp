#include "ZSGame.hpp"

#include <iostream>
#include <sstream>

namespace stoch {

  ZSGame::ZSGame(const Eigen::MatrixXd & payoff)
  {
    rows = payoff.cols() + 1;
    cols = payoff.rows() + 1;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "tmp");
    glp_set_obj_dir(lp, GLP_MAX);
    // LINES
    glp_add_rows(lp, rows);
    // v is the min over j of sum p_i a_{i,j} 
    // Declare lines: q_j = sum p_i a_{i,j} - v >= 0
    for (int row = 1; row <= payoff.cols(); row++) {
      std::ostringstream oss;
      oss << "q_" << row;
      rowNames.push_back(oss.str());
      glp_set_row_name(lp, row, rowNames[row -1].c_str());
      glp_set_row_bnds(lp, row, GLP_LO, 0.0, 0.0);
    }
    // Sum of probabilites = 1
    glp_set_row_name(lp, rows, "pSum");
    glp_set_row_bnds(lp, rows, GLP_FX, 1.0, 1.0);
    // COLUMNS
    glp_add_cols(lp, cols);// last col is v
    for (int col = 1; col <= payoff.rows(); col++) {
      std::ostringstream oss;
      oss << "p_" << col;
      colNames.push_back(oss.str());
      glp_set_col_name(lp, col, colNames[col -1].c_str());
      glp_set_col_bnds(lp, col, GLP_LO, 0.0, 0.0);// all probabilites are >= 0
      glp_set_obj_coef(lp, col, 0.0);
    }
    // v column
    glp_set_col_name(lp, cols, "v");
    glp_set_col_bnds(lp, cols, GLP_FR, 0.0, 0.0);
    glp_set_obj_coef(lp, cols, 1.0);
    // ARRAYS
    int * ia = new int[rows * cols + 1];
    int * ja = new int[rows * cols + 1];
    double * ar = new double[rows * cols + 1];
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        int idx = row * cols + col + 1;
        ia[idx] = row + 1;
        ja[idx] = col + 1;
        // Last line: sum of p_i
        if (row == rows - 1) {
          if (col != cols -1) {
            ar[idx] = 1;
          }
          else {
            ar[idx] = 0;
          }
        }
        // other lines: q_j = sum p_i a_{i,j} - v
        else {
          if (col != cols -1) {
            ar[idx] = payoff(col,row);
          }
          else {
            ar[idx] = -1;
          }
        }
      }
    }
    // load arrays
    glp_load_matrix(lp, rows * cols, ia, ja, ar);
    delete(ia);
    delete(ja);
    delete(ar);
  }

  ZSGame::~ZSGame()
  {
    if (lp != NULL) {
      glp_delete_prob(lp);
      lp = NULL;
    }
  }

  double ZSGame::solve()
  {
    int n = glp_simplex(lp, NULL);
    if (n != 0) {
      std::cout << "Non-zero result to glp_simplex" << std::endl;
    }
    Eigen::VectorXd solution(cols - 1);
    double result;
    result = glp_get_obj_val(lp);
    for (int i = 0; i < cols -1; i++) {
      solution(i) = glp_get_col_prim(lp, i + 1);
    }
    std::cout << "Value of the game: " << result << std::endl;
    std::cout << "Strategy: " << solution.transpose() << std::endl;
    return result;
  }

}
