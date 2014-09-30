#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "matrix.h"
#include "log.h"
#include "unittest.h"


int
main(int argc, char *argv[])
{
    int row, col, tmp, tmp2;
    int cnt;
    Matrix *mat;    // our test subject
    Matrix *clone;  // and another

    if (argc == 2 && strcmp(argv[1], "-v") == 0) {
        set_verbosity(1);  // set logging
    }

    /////////////////////////////////////////////////////////////////
    // CALC_INDEX macro
    //
    assert_eq(CALC_INDEX(2,2,4), 10, "[CALC_INDEX]: (2,2,4) == 10?");
    assert_eq(CALC_INDEX(10,0,5), 50, "[CALC_INDEX]: (10,0,5)== 50?");
    assert_eq(CALC_INDEX(0,0,3), 0, "[CALC_INDEX]: (0,0,3 == 3?");

    /////////////////////////////////////////////////////////////////
    // void matrix_init(Matrix *matrix);
    //
    mat = matrix_init();
    assert_eq(mat->num_rows, 0, "[matrix_init]: num_rows should be set to 0");
    assert_eq(mat->num_cols, 0, "[matrix_init]: num_cols should be set to 0");
    assert_eq(mat->row_cap, INIT_NUM_MAT_ROWS,
        "[matrix_init]: row_cap should be set to %2d", INIT_NUM_MAT_ROWS);
    assert_eq(mat->col_cap, INIT_NUM_MAT_COLS,
        "[matrix_init]: col_cap should be set to %2d", INIT_NUM_MAT_COLS);

    /////////////////////////////////////////////////////////////////
    // void matrix_add_row(Matrix *matrix);
    // void matrix_alloc_row(Matrix *matrix);
    //
    matrix_alloc_row(mat);
    assert_eq(mat->row_cap, INIT_NUM_MAT_ROWS,
        "[matrix_alloc_row]: should make no changes when cap not exceeded");

    cnt = 0;  // looking for 6 reallocs: 10, 12, 14, 16, 18, 20
    tmp2 = INIT_NUM_MAT_ROWS;
    for (row = 0; row <= 20; row++) {
        tmp = mat->num_rows;
        if (row == tmp2) {
            log_msg("[matrix_alloc_row]: current row_cap: %3d\n", mat->row_cap);
            cnt++;
            tmp2 = mat->row_cap;
            matrix_add_row(mat);
            // should add 2 to row cap at each realloc
            assert_eq(mat->row_cap, tmp2 + 2,
                "[matrix_alloc_row]: should increase row_cap from %3d to %3d",
                tmp2, tmp2 + 2);
            tmp2 = tmp2 + 2;
        } else {
            matrix_add_row(mat);
        }
        assert_eq(mat->num_rows, tmp + 1,
            "[matrix_add_row]: should inc num_rows from %3d to %3d...",
            tmp, tmp+1);
    }
    assert_eq(cnt, 6,
        "[matrix_alloc_row]: should have reallocated %3d times...", 6);

    /////////////////////////////////////////////////////////////////
    // void matrix_add_col(Matrix *matrix);
    // void matrix_alloc_col(Matrix *matrix);
    //
    matrix_alloc_col(mat);
    assert_eq(mat->col_cap, INIT_NUM_MAT_COLS,
        "[matrix_alloc_col]: should make no changes when cap not exceeded");

    cnt = 0; // should reallocate 4 times
    tmp2 = INIT_NUM_MAT_COLS;
    for (col = 0; col <= (INIT_NUM_MAT_COLS * 8); col++) {
        tmp = mat->num_cols;
        if (col == tmp2) {
            log_msg("[matrix_alloc_col]: current col_cap: %3d\n", mat->col_cap);
            cnt++;
            tmp2 = mat->col_cap;
            matrix_add_col(mat);
            // should double col cap at each realloc
            assert_eq(mat->col_cap, tmp2 * 2,
                "[matrix_alloc_col]: should double col_cap from %3d to %3d...",
                tmp2, tmp2 * 2);
            tmp2 = tmp2 * 2;
        } else {
            matrix_add_col(mat);
        }
        // should increment num_cols each time
        assert_eq(mat->num_cols, tmp + 1,
            "[matrix_add_col]: should inc num_cols from %3d to %3d...",
            tmp, tmp+1);
    }
    // check # reallocs
    assert_eq(cnt, 4,
        "[matrix_alloc_col]: should have reallocated %3d times...", 4);

    /////////////////////////////////////////////////////////////////
    // cell_t matrix_get(Matrix *matrix, int row, int col);
    // void matrix_set(Matrix *matrix, int row, int col, cell_t val);
    //
    tmp2 = 0;
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 5; col++) {
            tmp = row - col * tmp2++ >> 1;  // some arbitrary value
            tmp2 = tmp2 * 5 % 1024;         // more arbitrary stuff
            matrix_set(mat, row, col, tmp);

            assert_eq(mat->cells[CALC_INDEX(row, col, mat->num_cols)], tmp,
                "[matrix_set]: should set (%3d,%3d) to %i...",
                row, col, tmp);
            assert_eq(matrix_get(mat, row, col), tmp,
                "[matrix_get]: should get %i from (%3d,%3d)...",
                tmp, row, col);
        }
    }

    /////////////////////////////////////////////////////////////////
    // void matrix_rem_row(Matrix *matrix, int row);
    //

    /////////////////////////////////////////////////////////////////
    // void matrix_rem_col(Matrix *matrix, int col);
    //

    /////////////////////////////////////////////////////////////////
    // void matrix_fill_row(Matrix *matrix, int row, cell_t val);
    //
    tmp = 0xdeadbeef;

    /* case 1 */
    row = 0;
    log_msg("[matrix_fill_row]: should fill all cells in row %i with 0x%08x...\n",
        row, tmp);
    matrix_fill_row(mat, row, tmp);
    for (col = 0; col < mat->num_cols; col++) {
        tmp2 = matrix_get(mat, row, col);
        assert_eq(tmp2, tmp,
            "[matrix_fill_row]: cell (%3d,%3d) = 0x%08x",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_row] ...SUCCESS.\n");

    /* case 2 */
    row = mat->num_rows-1;
    log_msg("[matrix_fill_row]: should fill all cells in row %i with 0x%08x...\n",
        row, tmp);
    matrix_fill_row(mat, row, tmp);
    for (col = 0; col < mat->num_cols; col++) {
        tmp2 = matrix_get(mat, row, col);
        assert_eq(tmp2, tmp,
            "[matrix_fill_row]: cell (%3d,%3d) = 0x%08x",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_row] ...SUCCESS.\n");

    /* case 3 */
    row = mat->num_rows/2;
    log_msg("[matrix_fill_row]: should fill all cells in row %i with 0x%08x...\n",
        row, tmp);
    matrix_fill_row(mat, row, tmp);
    for (col = 0; col < mat->num_cols; col++) {
        tmp2 = matrix_get(mat, row, col);
        assert_eq(tmp2, tmp,
            "[matrix_fill_row]: cell (%3d,%3d) = 0x%08x",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_row] ...SUCCESS.\n");

    /////////////////////////////////////////////////////////////////
    // void matrix_fill_col(Matrix *matrix, int col, cell_t val);
    //
    tmp = 0x1ceb00da;

    /* case 1 */
    col = 0;
    log_msg("[matrix_fill_col]: should fill all cells in col %i with 0x%08x...\n",
        col, tmp);
    matrix_fill_col(mat, col, tmp);
    for (row = 0; row < mat->num_rows; row++) {
        tmp2 = matrix_get(mat, row, col);
        assert_eq(tmp2, tmp,
            "[matrix_fill_col]: cell (%3d,%3d) = 0x%08i",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_col] ...SUCCESS.\n");

    /* case 2 */
    col = mat->num_cols-1;
    log_msg("[matrix_fill_col]: should fill all cells in col %i with 0x%08x...\n",
        col, tmp);
    matrix_fill_col(mat, col, tmp);
    for (row = 0; row < mat->num_rows; row++) {
        tmp2 = matrix_get(mat, row, col);
        assert_eq(tmp2, tmp,
            "[matrix_fill_col]: cell (%3d,%3d) = 0x%08i",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_col] ...SUCCESS.\n");

    /* case 3 */
    col = mat->num_cols/2;
    log_msg("[matrix_fill_col]: should fill all cells in col %i with 0x%08x...\n",
        col, tmp);
    matrix_fill_col(mat, col, tmp);
    for (row = 0; row < mat->num_rows; row++) {
        tmp2 = matrix_get(mat, row, col);
        //printf("tmp2: 0x%08x, tmp1: 0x%08x\n", tmp2, tmp);
        assert_eq(tmp2, tmp,
            "[matrix_fill_col]: cell (%3d,%3d) = 0x%08x",
            row, col, tmp2);
    }
    log_msg("[matrix_fill_col] ...SUCCESS.\n");

    /////////////////////////////////////////////////////////////////
    // void matrix_fill(Matrix *matrix, cell_t val);
    //
    matrix_reinit(mat);
    for (tmp = 0; tmp < 5; tmp ++) matrix_add_col(mat);
    for (tmp = 0; tmp < 5; tmp ++) matrix_add_row(mat);

    tmp = 0;  // fill value
    log_msg("[matrix_fill]: should fill all cells with value %d...\n", tmp);
    matrix_fill(mat, tmp);
    for (row = 0; row < mat->num_rows; row++) {
        for (col = 0; col < mat->num_cols; col++) {
            tmp2 = mat->cells[CALC_INDEX(row, col, mat->num_cols)];
            assert_eq(tmp2, tmp,
                "[matrix_fill]: cell (%d, %d): %d == %d?",
                row, col, tmp2, tmp);
        }
    }
    log_msg("[matrix_fill] ...SUCCESS.\n");

    /////////////////////////////////////////////////////////////////
    // void matrix_clone(Matrix *matrix, Matrix *clone);
    //
    clone = matrix_clone(mat);
    tmp = clone->num_rows; tmp2 = mat->num_rows;
    assert_eq(tmp, tmp2,
        "[matrix_clone]: should copy num_rows: old (%i) == new (%i)?",
        tmp, tmp2);
    tmp = clone->num_cols; tmp2 = mat->num_cols;
    assert_eq(tmp, tmp2,
        "[matrix_clone]: should copy num_cols: old (%i) == new (%i)?",
        tmp, tmp2);
    tmp = clone->row_cap; tmp2 = mat->row_cap;
    assert_eq(tmp, tmp2,
        "[matrix_clone]: should copy row_cap:  old (%i) == new (%i)?",
        tmp, tmp2);
    tmp = clone->col_cap; tmp2 = mat->col_cap;
    assert_eq(tmp, tmp2,
        "[matrix_clone]: should copy col_cap:  old (%i) == new (%i)?",
        tmp, tmp2);
    assert_eq(matrix_cmp(mat, clone), 1,
        "[matrix_clone]: should copy all cell values to new matrix");

    /////////////////////////////////////////////////////////////////
    // void matrix_free(Matrix *matrix);
    //
    matrix_free(mat);
    matrix_free(clone);

    printf("TESTS RUN: %d\n", num_tests_run());
    printf("ALL TESTS PASS!\n");
    return 0;
}
