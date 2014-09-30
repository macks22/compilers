// matrix.h
//
// This variant of the Matrix is built to support adding rows/cols. It is for
// this reason that a 1D array is used rather than a 2D. If an array of arrays
// were used, extending the 2nd dimension would require extending every array by
// one, which would be quite costly for larger tables. With a 1D array, both
// dimensions will bear similar costs of resizing. The primary loss with this
// approach comes from the shifting of values after resizing. If we limit the
// insertion of rows to only be at the end of the array, this is not a problem
// for rows. There is no avoiding the issue for columns though; each new column
// will expand every row by 1.
//
// However, it is possible to offset this cost. Inserting 1 new column has the
// same effect as inserting any other number greater than 1: all other values
// (except those in the first row) must be shifted some number of places. The
// values in the row 0 never need to move. The values in the row 1 need to shift
// forward by the # of cols being inserted. The values in the row 2 shift
// forward by (2 * # of cols being inserted). In general, for row i, shift
// values forward by (i * # of cols being inserted). 

#include <stdint.h>

#define INIT_NUM_MAT_ROWS 10  /* conservative start point in favor of mem */
#define INIT_NUM_MAT_COLS 20  /* start higher to offset early col adds */

#define CALC_INDEX(row, col, rowlen) (row * rowlen + col)


typedef uint32_t cell_t;

typedef struct {
    int num_rows;     // # of rows used
    int num_cols;     // # of cols used
    int row_cap;      // # of rows available (allocated)
    int col_cap;      // # of cols available (allocated)
    cell_t *cells;    // dynamic array for data
} Matrix;


int matrix_cap(Matrix *matrix);

Matrix * matrix_init();

Matrix * matrix_clone(Matrix *matrix);

void matrix_free(Matrix *matrix);

Matrix * matrix_reinit(Matrix *matrix);

cell_t matrix_get(Matrix *matrix, int row, int col);

void matrix_set(Matrix *matrix, int row, int col, cell_t val);

void matrix_alloc_row(Matrix *matrix);

void matrix_alloc_col(Matrix *matrix);

void matrix_add_row(Matrix *matrix);

void matrix_add_col(Matrix *matrix);

void matrix_fill_row(Matrix *matrix, int row, cell_t val);

void matrix_fill_col(Matrix *matrix, int col, cell_t val);

void matrix_fill(Matrix *matrix, cell_t val);

void matrix_rem_row(Matrix *matrix, int row);

void matrix_rem_col(Matrix *matrix, int col);

int matrix_cmp(Matrix *m1, Matrix *m2);
