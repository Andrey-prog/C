#define INFINITY 100000000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Head.h"


void init_matrix(Graph* g) {

	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			if (g->matrix[i][j] == -1) {
				g->matrix[i][j] = INFINITY;
			}
		}
	}
}


void floyd(Graph* g) {

	init_matrix(g);

	for (int k = 0; k < g->size; k++) {
		for (int i = 0; i < g->size; i++) {
			for (int j = 0; j < g->size; j++) {
				g->matrix[i][j] = min(g->matrix[i][j], g->matrix[i][k] + g->matrix[k][j]);
			}
		}
	}
}