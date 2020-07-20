#define INFINITY 100000000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Head.h"


void init_graph(FILE* file, Graph* g, City* city) {

	g->matrix = (int**)malloc(g->size * sizeof(int*));
	for (int i = 0; i < g->size; i++) {
		g->matrix[i] = (int*)malloc(g->size * sizeof(int));
	}

	g->city = city;

	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			g->matrix[i][j] = -1;
		}
	}

	for (int i = 0; i < g->size; i++) {
		g->matrix[i][i] = 0;
	}

	int m;
	fscanf_s(file, "%d", &m);

	int u;
	int v;
	int t;
	for (int i = 0; i < m; i++) {
		fscanf_s(file, "%d", &u);
		fscanf_s(file, "%d", &v);
		fscanf_s(file, "%d", &t);
		g->matrix[u - 1][v - 1] = t;
	}

	g->visited = (int*)malloc(g->size * sizeof(int));
	for (int i = 0; i < g->size; i++) {
		g->visited[i] = 0;
	}

	for (int i = 0; i < g->size; i++) {
		g->city[i].path = (int*)malloc(sizeof(int));
		g->city[i].lenght = 1;
		g->city[i].path[0] = i;
	}
}


void change_path(int point, int i, Graph* g) {

	int k = g->city[point].lenght;
	int* temp = (int*)malloc((k + 1) * sizeof(int));

	memcpy(temp, g->city[point].path, k * sizeof(int));
	free(g->city[i].path);
	g->city[i].path = temp;
	g->city[i].path[k] = i;

	g->city[i].lenght = k + 1;
}


int minimum(Graph* g){

	int c = INFINITY;
	int y = 0;
	for (int i = 0; i < g->size; i++) {
		if (g->visited[i] != 1) {
			if (c > g->city[i].value) {
				c = g->city[i].value;
				y = i;
			}
		}
	}
	if (c < INFINITY) {
		return y;
	}
	else {
		return -1;
	}
}

void select(int point, Graph* g) {
	
	for (int i = 0; i < g->size; i++) {
		if (i != point){
			if (g->matrix[point][i] != -1) {
				if (g->visited[i] == 0) {
					if (g->city[i].value > g->city[point].value + g->matrix[point][i]) {
						g->city[i].value = g->city[point].value + g->matrix[point][i];	
						change_path(point, i, g);
					}
				}
			}
		}
	}
}


void dijkstra(int a, Graph* g) {

	for (int i = 0; i < g->size; i++) {
		g->city[i].value = INFINITY;
	}

	int point = a - 1;
	g->city[point].value = 0;

	while (point != -1) {
		select(point, g);
		g->visited[point] = 1;
		point = minimum(g);	
	}
}