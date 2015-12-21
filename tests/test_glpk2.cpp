#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{
  glp_prob *lp;
  int ia[1+1000], ja[1+1000];
  double ar[1+1000], z, x1, x2, x3;
  lp = glp_create_prob();
  glp_set_prob_name(lp, "sample");
  glp_set_obj_dir(lp, GLP_MAX);
  glp_add_rows(lp, 3);
  glp_set_row_name(lp, 1, "p");
  glp_set_row_bnds(lp, 1, GLP_LO, 0.0, 0.0);
  glp_set_row_name(lp, 2, "q");
  glp_set_row_bnds(lp, 2, GLP_LO, 0.0, 0.0);
  glp_set_row_name(lp, 3, "r");
  glp_set_row_bnds(lp, 3, GLP_FX, 1.0, 1.0);
  glp_add_cols(lp, 3);
  glp_set_col_name(lp, 1, "x1");
  glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 1, 0.0);
  glp_set_col_name(lp, 2, "x2");
  glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 2, 0.0);
  glp_set_col_name(lp, 3, "v");
  glp_set_col_bnds(lp, 3, GLP_FR, 0.0, 0.0);
  glp_set_obj_coef(lp, 3, 1.0);
  ia[1] = 1, ja[1] = 1, ar[1] = -2.0; /* a[1,1] =  -2 */
  ia[2] = 1, ja[2] = 2, ar[2] =  3.0; /* a[1,2] =   3 */
  ia[3] = 1, ja[3] = 3, ar[3] = -1.0; /* a[1,3] =  -1 */
  ia[4] = 2, ja[4] = 1, ar[4] =  3.0; /* a[2,1] =   3 */
  ia[5] = 2, ja[5] = 2, ar[5] = -4.0; /* a[2,2] =  -4 */
  ia[6] = 2, ja[6] = 3, ar[6] = -1.0; /* a[2,3] =  -1 */
  ia[7] = 3, ja[7] = 1, ar[7] =  1.0; /* a[3,1] =   1 */
  ia[8] = 3, ja[8] = 2, ar[8] =  1.0; /* a[3,2] =   1 */
  ia[9] = 3, ja[9] = 3, ar[9] =  0.0; /* a[3,3] =   0 */
  glp_load_matrix(lp, 9, ia, ja, ar);
  glp_simplex(lp, NULL);
  z = glp_get_obj_val(lp);
  x1 = glp_get_col_prim(lp, 1);
  x2 = glp_get_col_prim(lp, 2);
  x3 = glp_get_col_prim(lp, 3);
  printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);
  glp_delete_prob(lp);
  return 0;
}
