#include <stdio.h>
#include <assert.h>
#include "matrix.h"


int
main()
{
    int row, col, tmp, tmp2;
    int cnt;
    Matrix *mat;    // our test subject
    Matrix *clone;  // and another

    // void matrix_init(Matrix *matrix);
    //
    mat = matrix_init();
    assert(mat->num_rows == 0);
    assert(mat->num_cols == 0);
    assert(mat->row_cap  == INIT_NUM_MAT_ROWS);
    assert(mat->col_cap  == INIT_NUM_MAT_COLS);

    // void matrix_add_row(Matrix *matrix);
    // void matrix_alloc_row(Matrix *matrix);
    //
    printf("[matrix_alloc_row]: should make no changes when cap not exceeded...");
    matrix_alloc_row(mat);
    assert(mat->row_cap == INIT_NUM_MAT_ROWS);
    printf(" SUCCESS.\n");

    cnt = 0;  // looking for 6 reallocs: 10, 12, 14, 16, 18, 20
    tmp2 = INIT_NUM_MAT_ROWS;
    for (row = 0; row <= 20; row++) {
        tmp = mat->num_rows;
        if (row == tmp2) {
            printf("[matrix_alloc_row]: current row_cap: %3d\n", mat->row_cap);
            cnt++;
            tmp2 = mat->row_cap;
            matrix_add_row(mat);
            // should add 2 to row cap at each realloc
            printf("[matrix_alloc_row]: should increase row_cap from %3d to %3d...",
                tmp2, tmp2 + 2);
            assert(mat->row_cap == tmp2 + 2);
            printf(" SUCCESS.\n");
            tmp2 = tmp2 + 2;
        } else {
            matrix_add_row(mat);
        }
        printf("[matrix_add_row]: should inc num_rows from %3d to %3d...",
            tmp, tmp+1);
        assert(mat->num_rows == tmp + 1);
        printf(" SUCCESS.\n");
    }
    printf("[matrix_alloc_row]: should have reallocated %3d times...", 6);
    assert(cnt == 6);
    printf(" SUCCESS.\n");

    // void matrix_add_col(Matrix *matrix);
    // void matrix_alloc_col(Matrix *matrix);
    //
    printf("[matrix_alloc_col]: should make no changes when cap not exceeded...");
    matrix_alloc_col(mat);
    assert(mat->col_cap == INIT_NUM_MAT_COLS);
    printf(" SUCCESS.\n");

    cnt = 0; // should reallocate 4 times
    tmp2 = INIT_NUM_MAT_COLS;
    for (col = 0; col <= (INIT_NUM_MAT_COLS * 8); col++) {
        tmp = mat->num_cols;
        if (col == tmp2) {
            printf("[matrix_alloc_col]: current col_cap: %3d\n", mat->col_cap);
            cnt++;
            tmp2 = mat->col_cap;
            matrix_add_col(mat);
            // should double col cap at each realloc
            printf("[matrix_alloc_col]: should double col_cap from %3d to %3d...",
                tmp2, tmp2 * 2);
            assert(mat->col_cap == tmp2 * 2);
            printf(" SUCCESS.\n");
            tmp2 = tmp2 * 2;
        } else {
            matrix_add_col(mat);
        }
        // should increment num_cols each time
        printf("[matrix_add_col]: should inc num_cols from %3d to %3d...",
            tmp, tmp+1);
        assert(mat->num_cols == tmp + 1);
        printf(" SUCCESS.\n");
    }
    printf("[matrix_alloc_col]: should have reallocated %3d times...", 4);
    assert(cnt == 4);  // check # reallocs
    printf(" SUCCESS.\n");

    // cell_t matrix_get(Matrix *matrix, int row, int col);
    //

    // void matrix_set(Matrix *matrix, int row, int col, cell_t val);
    //

    // void matrix_fill_row(Matrix *matrix, int row, cell_t val);
    //

    // void matrix_fill_col(Matrix *matrix, int col, cell_t val);
    //

    // void matrix_fill(Matrix *matrix, cell_t val);
    //
    tmp = 0;  // fill value
    printf("[matrix_fill]: should fill all cells with value %3d...", tmp);
    matrix_fill(mat, tmp);
    for (row = 0; row < mat->num_rows; row++) {
        for (col = 0; col < mat->num_cols; col++) {
            assert(mat->cells[CALC_INDEX(row, col, mat->num_cols)] == tmp);
        }
    }
    printf(" SUCCESS.\n");

    // void matrix_clone(Matrix *matrix, Matrix *clone);
    //
    printf("[matrix_clone]: should copy all values to new matrix...");
    clone = matrix_clone(mat);
    assert(clone->num_rows == mat->num_rows);
    assert(clone->num_cols == mat->num_cols);
    assert(clone->row_cap  == mat->row_cap);
    assert(clone->col_cap  == mat->col_cap);
    assert(matrix_cmp(mat, clone) == 1);
    printf(" SUCCESS.\n");

    // void matrix_rem_row(Matrix *matrix, int row);
    //

    // void matrix_rem_col(Matrix *matrix, int col);
    //

    // void matrix_free(Matrix *matrix);
    //
    matrix_free(mat);
    matrix_free(clone);

    printf("ALL TESTS PASS!\n");
    return 0;
}
