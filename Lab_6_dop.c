#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	char *value;
	struct node *left;
	struct node *right;
} node;

char is_letter (char str) {
	if (((str >= 'A') && (str <= 'Z')) || ((str >= 'a') && (str <= 'z'))) {
		return 1;
	} else {
		return 0;
	}
}

int strcomp (char *s1, char *s2) {
	while ((*s1 != 0) && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

void add_node (node **root, char *word) {
	int i = 0, len = 10;
	if (!*root) {
		*root = (node*)malloc(sizeof(**root));
		(*root)->value = (char*) malloc(len * sizeof(char));
		while (word[i]) {
			if (i == len) {
				len *= 2;
				(*root)->value = realloc((*root)->value, len * sizeof(char));
			}
			(*root)->value[i] = word[i];
			i++;
		}
		(*root)->value[i] = 0;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}
	if (strcomp(word, (*root)->value) < 0) {
		add_node(&(*root)->left, word);
	} else {
		add_node(&(*root)->right, word);
	}
}

void print_tree(node *root) {
	if (root) {
		print_tree(root->left);
		printf("%s\n", root->value);
		print_tree(root->right);
	} else {
		return;
	}
}

int main () {
	node *root = NULL;
	int a = 0, len = 10, i = 0;
	char in_word = 0;
	char *word = (char*) malloc(len * sizeof(char));
	while ((a = getchar()) != '\n') {
		if (is_letter(a)) {
			if (i == len) {
				len *= 2;
				char *tmp = word;
				word = realloc(word, len * sizeof(char));
				if (word == NULL) {
					free(tmp);
					printf("Not enough memory!");
					return 1;
				}
			}
			word[i] = a;
			in_word = 1;
			i++;
		} else {
			if (in_word) {
				word[i] = 0;
				add_node(&root, word);
				free(word);
				word = (char*)malloc(len * sizeof(char));
				if (word == NULL) {
					printf("Not enough memory!");
					return 1;
				}
				i = 0;
				in_word = 0;
			}
		}
	}
	if (in_word) {
		add_node(&root, word);
		free(word);
	}
	print_tree(root);
	return 0;
}
