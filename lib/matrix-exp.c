#include <stdio.h>

int
main()
{
    // Figure out fast way to shift cells in matrix built on 1D arr.
    // Lets say we have a 5x5 array, so 25 indices.
    // The first row (first 5 indices) remains unchanged.
    // For all other rows i, shift forward by (i * # cols inserted).
    // This could probably be accomplished by
    //     `current index + (i * num_cols)
    // But perhaps bit shifting would work too?
    int row, col;      // hold indices
    int row_shift;     // track how much to shift each cell in row
    int shift = 2;     // bit shifting, or # cols inserted
    int num_rows = 5;
    int num_cols = 5;

    for (row = 0; row < num_rows; row++) {
        row_shift = row * shift;
        printf("row %2d, shift by: %2d\n", row, row_shift);
        for (col = 0; col < num_cols; col++) {
            printf("index %2d becomes %2d\n", (row * num_cols) + col,
                ((row * num_cols) + col) + row_shift);
            // bit shifting approach (doesn't work):
            // printf("row %2d, col %2d\n", row, col);
            // printf("index %2d shifted by %i: %i\n", (row * num_cols) + col,
            //     shift, ((row * num_cols) + col) << shift);
        }
    }
}
