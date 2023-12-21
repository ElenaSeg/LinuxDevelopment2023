#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void form_fences(char *grid, int enclosure_size);
void show_maze(char *grid, int enclosure_size);
void insert_fence(char *grid, int magnitude);
int calculate_enclosure_size(int magnitude);
void initialize_grid(char *grid, int enclosure_size);

int main() {
    int magnitude = 6;
    int enclosure_size = calculate_enclosure_size(magnitude);

    char *grid = (char *)malloc(sizeof(char) * enclosure_size * enclosure_size);

    initialize_grid(grid, enclosure_size);
    form_fences(grid, enclosure_size);
    insert_fence(grid, magnitude);
    show_maze(grid, enclosure_size);

    free(grid);
    return 0;
}

void form_fences(char *grid, int enclosure_size) {
    for (int row = 0; row < enclosure_size; row++) {
        for (int col = 0; col < enclosure_size; col++) {
            const int pos = row * enclosure_size + col;
            if (row == 0 || row == enclosure_size - 1 || col == 0 || col == enclosure_size - 1) {
                grid[pos] = '#';
            }
            else if ((row + 1) % 2 == 0 || (col + 1) % 2 == 0) {
                grid[pos] = '.';
            }
            else {
                grid[pos] = '#';
            }
        }
    }
}

void show_maze(char *grid, int enclosure_size) {
    for (int row = 0; row < enclosure_size; row++) {
        for (int col = 0; col < enclosure_size; col++) {
            printf("%c", grid[row * enclosure_size + col]);
        }
        printf("\n");
    }
}

void insert_fence(char *grid, int magnitude) {
    const bool vertical_fence = rand() % 2;
    const int fence_row = (1 + (rand() % (magnitude - 1))) * 2 - 1;
    const int fence_col = (1 + (rand() % (magnitude - 1))) * 2;

    if (vertical_fence) {
        grid[fence_row * (magnitude * 2 + 1) + fence_col] = '#';
    }
    else {
        grid[fence_col * (magnitude * 2 + 1) + fence_row] = '#';
    }
}

int calculate_enclosure_size(int magnitude) {
    return magnitude * 2 + 1;
}

void initialize_grid(char *grid, int enclosure_size) {
    for (int i = 0; i < enclosure_size * enclosure_size; i++) {
        grid[i] = ' ';
    }
}