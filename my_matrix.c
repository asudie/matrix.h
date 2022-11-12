#include "my_matrix.h"

int my_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)malloc(sizeof(double *) * rows);
    if (result->matrix == NULL) {
      err = 3;
    }
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        err = 3;
      }
    }

  } else {
    err = 1;
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
  }
  return err;
}

void my_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

void fill_matrix(matrix_t *A) {
  int index = 1;
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      A->matrix[i][j] = index++;
    }
  }
}

void fill_matrix_zero(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      A->matrix[i][j] = 0;
    }
  }
}
void fill_matrix_num(matrix_t *A, double num) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      A->matrix[i][j] = num;
    }
  }
}

// void print_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; ++i) {
//     for (int j = 0; j < A->columns; ++j) {
//       printf("[%lf]", A->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (check_equality(A->rows, B->rows, A->columns, B->columns)) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) < EPS) {
          continue;
        } else {
          result = FAILURE;
        }
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (check_equality(A->rows, B->rows, A->columns, B->columns)) {
    err = my_create_matrix(A->rows, A->columns, result);
    if (!err) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    err = 2;
  }
  if (err) my_create_matrix(0, 0, result);
  return err;
}

int check_equality(int r1, int r2, int c1, int c2) {
  return (r1 == r2 && c1 == c2) ? 1 : 0;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err;
  err = my_create_matrix(A->rows, A->columns, result);
  if (!err) {
    err = 0;
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return err;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err;
  if (check_equality(A->rows, B->rows, A->columns, B->columns)) {
    matrix_t reversed_B;
    my_mult_number(B, -1, &reversed_B);
    err = my_sum_matrix(A, &reversed_B, result);
    my_remove_matrix(&reversed_B);
  } else {
    err = 2;
  }

  if (err) my_create_matrix(0, 0, result);
  return err;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err;
  if (A->columns == B->rows) {
    err = my_create_matrix(A->rows, B->columns, result);
    if (!err) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  } else {
    err = 2;
  }

  if (err) my_create_matrix(0, 0, result);

  return err;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  int err = my_create_matrix(A->columns, A->rows, result);
  if (!err) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return err;
}

int minor_matrix(matrix_t *A, int i, int j, matrix_t *minor_m) {
  my_create_matrix((A->rows - 1), (A->columns - 1), minor_m);
  if (i < A->rows && j < A->columns) {
    for (int a = 0, k = 0; a < A->rows && k < (A->rows - 1); a++, k++) {
      for (int b = 0, y = 0; b < A->columns && y < (A->columns - 1); b++, y++) {
        if (a == i) {
          a++;
        }
        if (b == j) {
          b++;
        }
        minor_m->matrix[k][y] = A->matrix[a][b];
      }
    }
  }
  return 0;
}

int my_determinant(matrix_t *A, double *result) {
  int err = 0;
  *result = 0.0;
  if (A->rows <= 0 || A->columns <= 0) {
    err = 1;
  } else if (A->rows == A->columns) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int j = 0; j < A->columns; ++j) {
        double temp_result = 0;
        matrix_t minor_m;
        minor_matrix(A, 0, j, &minor_m);
        my_determinant(&minor_m, &temp_result);
        my_remove_matrix(&minor_m);
        int sign = (j & 1) ? -1 : 1;
        *result += A->matrix[0][j] * temp_result * sign;
      }
    }
  } else {
    err = 2;
  }
  return err;
}

int my_calc_complements(matrix_t *A, matrix_t *result) {
  int err;
  err = my_create_matrix(A->rows, A->columns, result);
  if (!err) {
    if (A->rows == A->columns) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          double temp_result = 0;
          matrix_t minor_m;
          minor_matrix(A, i, j, &minor_m);
          my_determinant(&minor_m, &temp_result);
          my_remove_matrix(&minor_m);
          int sign = ((i + j) & 1) ? -1 : 1;
          result->matrix[i][j] = temp_result * sign;
        }
      }
    } else {
      err = 2;
    }
  }
  return err;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det_result = 0;
  int err = my_determinant(A, &det_result);
  if (!err) {
    if (!det_result) {
      err = 2;
    } else {
      matrix_t comp_result;
      my_calc_complements(A, &comp_result);
      matrix_t trans_result;
      my_transpose(&comp_result, &trans_result);
      my_mult_number(&trans_result, 1 / det_result, result);
      my_remove_matrix(&comp_result);
      my_remove_matrix(&trans_result);
    }
  }
  if (err) my_create_matrix(0, 0, result);

  return err;
}
