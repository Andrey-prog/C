#ifndef HEAD_H
#define HEAD_H

typedef struct City {
	int number;
	char* array;
	int value;
	int* path;
	int lenght;
}City;

typedef struct Graph {
	int size;
	int** matrix;
	City* city;
	int* visited;
}Graph;


void init_graph(FILE*, Graph*, City*);
void change_path(int, int, Graph*);
int minimum(Graph*);
void select(int, Graph*);
void dijkstra(int, Graph*);

void init_matrix(Graph*);
void floyd(Graph*);

#endif