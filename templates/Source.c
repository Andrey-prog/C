#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<sys/timeb.h>
#include<windows.h>


typedef struct {
	char* string;
	int long counter;
}Text;


typedef struct {
	char* template;
	int* arr;
	int size;
}Index;


Index init_template(Index* index, FILE* file) {

	index->arr = (int*)malloc(sizeof(int));
	index->template = "printf";
	index->size = 0;
	return *index;
}


Text add_to_text(Text* text, FILE* file){
	
	text->string = NULL;
	text->counter = 0;
	char str[4096];

	while (fgets(str, 4096, file) != NULL) {
		int k = strlen(str);
		text->string = (char*)realloc(text->string, sizeof(char)*(text->counter + k) + 1);

		for (int i = 0; i < k; i++) {
			text->string[text->counter + i] = str[i];
		}
		text->counter += k;
	}
	text->string[text->counter] = '\0';

	return *text;
}



void add_to_index(Index* index, int i) {

	index->arr = (int*)realloc(index->arr, (index->size + 1) * sizeof(int));
	index->arr[index->size] = i;
	index->size++;
}

Index func(Text* text, Index* index){

	int n = strlen(text->string) - 1;
	int len = strlen(index->template) - 1;

	for (int i = 0; i < (n - len); i++) {
		int j;
		for (j = len; j > -1; j--) {
			if (index->template[j] != text->string[i + j]) {
				break;
			}
		}
		if (j == -1) {

			add_to_index(index, i);
		}
	}
	return *index;
}



Index boyer_mur(Text* text, Index* index) {

	int n = strlen(text->string) - 1;
	int len = strlen(index->template) - 1;


	int shift[256];
	for (int i = 0; i < 256; i++) {
		shift[i] = len + 1;
	}
	for (int i = 0; i < len; i++) {
		shift[(unsigned)index->template[i]] = len - i;
	}

	for (int i = 0; i < (n - len); i++) {
		int j = len;
		for (j = len; j > -1; j--) {
			if (text->string[j + i] != index->template[j]) {
				if (j == len) {
					i += shift[(unsigned)text->string[j + i]] - 1;
					break;
				}
				else {
					i += shift[(unsigned)index->template[len]] - 1;
					break;
				}
			}
		}
		if (j == -1) {

			add_to_index(index, i);
		}
	}
	return *index;
}


void print_index(Index* index, Text* text) {

	int t = strlen(index->template);

	if (index->size != 0) {
		for (int i = 0; i < index->size; i++) {

			char* c = (char*)malloc(t * sizeof(char) + 1);
			printf_s("%d\n", index->arr[i]);

			for (int j = 0; j < t; j++) {
				c[j] = text->string[index->arr[i] + j];
			}

			c[t] = '\0';
			printf_s("%s\n", c);
			free(c);
		}
	} 
	else{
		printf_s("NO");
	}
	free(index->arr);

}



int main() {

	struct timeb start, end;
	FILE* file;
	fopen_s(&file, "list.txt", "r");

	Index index;
	Text text;
	text = add_to_text(&text, file);
	index = init_template(&index, file);


	ftime(&start);

	
	index = func(&text, &index);
	//index = boyer_mur(&text, &index);
	print_index(&index, &text);
	free(text.string);
	
	ftime(&end);


	print_index(&index, &text);
	int diff = (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
	printf_s("%u", diff);

	return 0;

}







