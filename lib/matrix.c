#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"


int
matrix_cap(Matrix *matrix)
{   /* Actual number of cell allocations, rather than rows/cols being used.
     */
    return matrix->row_cap * matrix->col_cap;
}

Matrix *
matrix_init()
{   /* Fully initialize a Matrix, then return a pointer to it.
     * This allocates memory for the struct as well as the actual data cells.
     */
    Matrix *matrix = malloc(sizeof(*matrix));

    // set matrix metadata
    matrix->num_rows = 0;
    matrix->num_cols = 0;
    matrix->row_cap  = INIT_NUM_MAT_ROWS;
    matrix->col_cap  = INIT_NUM_MAT_COLS;

    // allocate space for data cells
    matrix->cells = calloc(matrix->row_cap * matrix->col_cap, sizeof(cell_t));
    return matrix;
}

Matrix *
matrix_clone(Matrix *matrix)
{   /* Take an already initialized matrix and clone it into a new matrix.
     * Then point the return a pointer to the clone.
     */
    int row, col;
    Matrix *clone = malloc(sizeof(*clone));

    // allocate enough cells to fit contents of existing matrix
    clone->cells = calloc(matrix->row_cap * matrix->col_cap, sizeof(cell_t));

    // copy contents of cells over
    memcpy(clone->cells, matrix->cells, matrix_cap(matrix));

    // copy over remaining metadata
    clone->num_rows = matrix->num_rows;
    clone->num_cols = matrix->num_cols;
    clone->row_cap  = matrix->row_cap;
    clone->col_cap  = matrix->col_cap;

    return clone;
}

void
matrix_free(Matrix *matrix)
{   /* Free the cells of the matrix, then the Matrix struct itself.
     */
    free(matrix->cells);
    free(matrix);
    matrix = NULL;
}

cell_t
matrix_get(Matrix *matrix, int row, int col)
{   /* Get the value of a cell in the matrix.
     */
    assert(row < matrix->num_rows);
    assert(col < matrix->num_cols);
    return matrix->cells[CALC_INDEX(row, col, matrix->num_cols)];
}

void
matrix_set(Matrix *matrix, int row, int col, cell_t val)
{   /* Set the value of a cell in the matrix.
     */
    matrix->cells[CALC_INDEX(row, col, matrix->num_cols)] = val;
}

void
matrix_alloc_row(Matrix *matrix)
{   /* Allocate a new row in the matrix. Since no cells need to be shifted around
     * to accommodate a new row, only two are added at a time (realloc still
     * costs some cycles -- there's always tradeoffs).
     */
    if (matrix->num_rows < matrix->row_cap) return;
    matrix->cells = realloc(
        matrix->cells,
        sizeof(cell_t) * matrix->col_cap * matrix->row_cap+2);
    matrix->row_cap = matrix->row_cap+2;
}

void
matrix_add_row(Matrix *matrix)
{   /* Add a single row to the matrix.
     */
    matrix_alloc_row(matrix);
    matrix->num_rows++;
}


void
matrix_alloc_col(Matrix *matrix)
{   /* Double the number of cols in the matrix. This is done to amortize the
     * high cost of column allocation [O(R*C)]. This function is called whenever
     * `matrix_add_col` is called and no column capacity remains. The effect is
     * to tradeoff on memory efficiency in order to gain performance. This
     * strategy reduces the cost to an average of O(\sqrt{R*C}), which is a
     * sizeable gain. At worst, the amount of unused space will be roughly the
     * same as the amount of used space.
     */
    if (matrix->num_cols < matrix->col_cap) return;
    int numcols, row, col, idx, row_shift, numcells;

    numcols = matrix->col_cap * 2;
    numcells = matrix->col_cap * matrix->row_cap;
    matrix->cells = realloc(matrix->cells, sizeof(cell_t) * numcells);

    // shift values to accommodate new columns start from the end of the array
    // and work back to avoid overwriting needed vals
    for (row = matrix->num_rows-1; row > 0; row--) {
        row_shift = row * numcols;
        for (col = matrix->num_cols-1; col >= 0; col--) {
            idx = CALC_INDEX(row, col, matrix->num_cols);
            if (idx + row_shift <= numcells) {
                matrix->cells[idx + row_shift] = matrix->cells[idx];
            }
        }
    }
    matrix->col_cap = numcols;
}

void
matrix_add_col(Matrix *matrix)
{   /* Add a single column to the matrix.
     */
    matrix_alloc_col(matrix);
    matrix->num_cols++;
}

void
matrix_fill_row(Matrix *matrix, int row, cell_t val)
{   /* Fill all cells in a row with a particular value. This overwrites whatever
     * values are currently in the row.
     */
    int col;
    assert(row < matrix->num_rows);
    for (col = 0; col < matrix->num_cols; col++) {
        matrix_set(matrix, row, col, val);
    }
}

void
matrix_fill_col(Matrix *matrix, int col, cell_t val)
{   /* Fill all cells in a column with a particular value. This overwrites
     * whatever values are currently in the column.
     */
    int row;
    assert(col < matrix->num_cols);
    for (row = 0; row < matrix->num_rows; row++) {
        matrix_set(matrix, row, col, val);
    }
}

void
matrix_fill(Matrix *matrix, cell_t val)
{   /* Fill all cells in the matrix with a particular value. This overwrites
     * whatever values are currently in the cells.
     */
    int row, col;

    // this could also be done using matrix_fill_row, but this is likely faster
    for (row = 0; row < matrix->num_rows; row++) {
        for (col = 0; col < matrix->num_cols; col++) {
            matrix->cells[CALC_INDEX(row, col, matrix->num_cols)] = val;
        }
    }
}

void
matrix_rem_row(Matrix *matrix, int row)
{   /* Remove a single row from the matrix. Note that this will result in the
     * remaining rows after this one to be shifted back by the number of cols.
     * Therefore this operation costs (num_cols * (num_rows - row + 1))
     * subtractions => O(R*C) => o(0). In other words, removing a row from the
     * end is the least expensive, and the cost increases proportional to how
     * far from the end the row is. The space vacated by the row will not be
     * freed. Instead, it will be kept around to offset costs of memory
     * allocation.
     */

}

void
matrix_rem_col(Matrix *matrix, int col)
{   /* Remove a single column from the matrix. If this is not the last column,
     * this operation will involve a matrix-wide shifting of values in order
     * to preserve the order of columns. This costs ((num_rows - 1) * num_cols)
     * subtractions => O(R*C).
     */

}

int
matrix_cmp(Matrix *m1, Matrix *m2)
{   /* Compare two matrices. Return 1 if the same, else 0.
     * This is mostly useful for testing purposes. It is not very often that two
     * matrices will have exactly the same values in all cells.
     */
    int col, row, idx;

    if (m1->num_rows != m2->num_rows || m1->num_cols != m2->num_cols) {
        return 0;
    }
    for (row = 0; row < m1->num_rows; row++) {
        for (col = 0; col < m1->num_cols; col++) {
            idx = CALC_INDEX(row, col, m1->num_cols);
            if (m1->cells[idx] != m2->cells[idx]) {
                return 0;
            }
        }
    }
    return 1;
}
