#ifndef SRC_MATRIX_MY_MATRIX_H_
#define SRC_MATRIX_MY_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define my_NAN 0.0 / 0.0
#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7  //  2.220446 ???

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int my_create_matrix(int rows, int columns, matrix_t *result);
void my_remove_matrix(matrix_t *A);
void fill_matrix(matrix_t *A);
void fill_matrix_zero(matrix_t *A);
void print_matrix(matrix_t *A);
int my_eq_matrix(matrix_t *A, matrix_t *B);
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int check_equality(int r1, int r2, int c1, int c2);
void fill_matrix_num(matrix_t *A, double num);
int my_mult_number(matrix_t *A, double number, matrix_t *result);
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_transpose(matrix_t *A, matrix_t *result);
int my_determinant(matrix_t *A, double *result);
int minor_matrix(matrix_t *A, int i, int j, matrix_t *minor);
int my_calc_complements(matrix_t *A, matrix_t *result);
int my_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_MATRIX_S_21_MATRIX_H_
