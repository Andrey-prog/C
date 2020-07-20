#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Head.h"
#include<time.h>


void init_city(FILE* file, City* city, int n) {

	for (int i = 0; i < n; i++) {

		fscanf_s(file, "%d", &((city + i)->number));
		char s[20];
		fscanf_s(file, "%19s", s, _countof(s));

		int k = strlen(s);
		(city + i)->array = (char*)malloc(k * sizeof(char) + 1);
		strcpy((city + i)->array, s);
		(city + i)->array[k] = '\0';
	}
}

void free_path(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		free(g->city[i].path);
	}
	for (int i = 0; i < g->size; i++) {
		g->city[i].path = (int*)malloc(sizeof(int));
		g->city[i].lenght = 1;
		g->city[i].path[0] = i;
	}
};

void print_path(Graph* g) {

	for (int i = 0; i < g->size; i++) {
		printf_s("The route: ");
		for (int j = 0; j < g->city[i].lenght - 1; j++) {
			printf_s("%s->", g->city[g->city[i].path[j]].array);
		}
		printf_s("%s  Distance:", g->city[g->city[i].path[g->city[i].lenght - 1]].array);
		printf_s("%d\n", g->city[i].value);
	}
}

void print_matrix(Graph* g) {

	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size - 1; j++) {
			printf_s("%d ", g->matrix[i][j]);
		}
		printf_s("%d\n", g->matrix[i][g->size - 1]);
	}
}

void print_way(Graph* g, int i, int j) {
	
	printf_s("%s->", g->city[i - 1].array);
	printf_s("%s  Distance:", g->city[j - 1].array);
	printf_s("%d\n", g->matrix[i - 1][j - 1]);
}


int main() {
	FILE* file;
	fopen_s(&file, "list.txt", "r");

	int n;
	fscanf_s(file, "%d", &n);

	City* city;
	city = (City*)malloc(n * sizeof(City));
	Graph g;
	g.size = n;

	init_city(file, city, n);

	init_graph(file, &g, city);

	time_t t0 = time(0);
	
	dijkstra(1, &g);
	print_path(&g); 
	free_path(&g);
	
	time_t t1 = time(0);
	double time_in_seconds = difftime(t1, t0);
	printf_s("%f\n", time_in_seconds);

	free_path(&g);

	time_t t2 = time(0);

	floyd(&g);

	time_t t3 = time(0);
	time_in_seconds = difftime(t3, t2);
	printf_s("%f\n", time_in_seconds);

	printf_s("Floyd\n");
	for (int i = 1; i < g.size + 1; i++) {
		print_way(&g, 1, i);
	}
}