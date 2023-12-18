#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
	int maze_size = 6;
	srand(time(NULL));
	int *maze_sets = calloc(maze_size, sizeof(int));
	char *r_walls = calloc(maze_size*maze_size, sizeof(char));
	char *d_walls = calloc(maze_size*maze_size, sizeof(char));
	memset(maze_sets, 0, maze_size);
	memset(r_walls, 0, (maze_size - 1) * maze_size);
	memset(d_walls, 0, maze_size * maze_size);
	for (int i = 0; i < maze_size; i++) {
		maze_sets[i] = i;
	}
	int num = maze_size;
	for (int i = 0; i < maze_size; i++) {
		for (int n = 0; n < maze_size - 1; n++) {
			if (maze_sets[n] == maze_sets[n + 1]) {
				r_walls[i * maze_size + n] = 1;
				continue;
			}
			r_walls[i * maze_size + n] = (char)(rand() % 2);
			if (r_walls[i * maze_size + n] == 0) {
				int maze_class = maze_sets[n+1];
				for (int k = 0; k < maze_size; k++) { 
					if (maze_sets[k] == maze_class) {
						maze_sets[k] = maze_sets[n];
					}
				}		
			}
		}
		for (int j = 0; j < maze_size; j++) {
			char fine = 0;
			for (int m = 0; m < maze_size; m++) {
				if (m == j) continue;
				if (maze_sets[m] == maze_sets[j] && d_walls[i * maze_size + m] == 0) {
					fine = 1;
					break;
				}
			}
			if (fine == 1) {
				d_walls[i * maze_size + j] = (char)(rand() % 2);
			}
		}
		if (i == maze_size - 1) continue;
		for (int j = 0; j < maze_size; j++) {
			if (d_walls[i * maze_size + j] == 1) {
				maze_sets[j] = num;
				num++;
			}
		}
	}
	for (int i = 0; i < maze_size - 1; i++) {
		if (maze_sets[i] != maze_sets[i + 1]) {
			r_walls[(maze_size - 1) * maze_size + i] = 0;
			int maze_class = maze_sets[i + 1];
			for (int j = 0; j < maze_size; j++) {
				if (maze_sets[j] == maze_class) maze_sets[j] = maze_sets[i];
			}
		}
	}
	char *maze_r = calloc(2 * maze_size + 2, sizeof(char));
	memset(maze_r, '#', 2 * maze_size + 1);
	maze_r[2 * maze_size + 1] = '\0';
	printf("%s\n", maze_r);
	for (int i = 0; i < maze_size; i++) {
		memset(maze_r, '#', 2 * maze_size + 1);
		for (int j = 1; j < maze_size; j++) {
			maze_r[2 * j - 1] = '.';
			if (r_walls[i * maze_size + j - 1] == 0) {
				maze_r[2 * j] = '.';
			}	
		}
		maze_r[2 * maze_size - 1] = '.';
		printf("%s\n", maze_r);
		memset(maze_r, '#', 2 * maze_size + 1);
		if (i == maze_size - 1) {
			printf("%s\n", maze_r);
			continue;
		}
		for (int j = 0; j < maze_size; j++) {
			if (d_walls[i * maze_size + j] == 0) {
				maze_r[2 * j + 1] = '.';
			}
		}
		printf("%s\n", maze_r);
	}
	free(maze_sets);
	free(r_walls);
	free(d_walls);	
	return 0;
}
