#include <stdio.h>
#include <stdlib.h>
/* Написать программу, которая создает линейный упорядоченный список из вводимых слов, после чего создает копию списка с элементами в обратном порядке Доп: то же самое, но с помощью двоичного дерева поиска */
typedef struct node {
	char *value;
	struct node *next;
} node_t;

typedef struct {
	node_t *head;
} list_t;

void init (list_t *l) {
	l->head = NULL;
}

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

void swap (char **s1, char **s2) {
	char *tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void bubble_sort (list_t *l) {
	node_t *cur = l->head;
	node_t *tmp = NULL;
	char flag = 1;
	while (cur || flag) {
		flag = 0;
		tmp = cur->next;
		while (tmp) {
			if (strcomp(cur->value, tmp->value) > 0) {
				swap(cur->value, tmp->value);
				flag = 1;
			}
			tmp = tmp->next;
		}
		cur = cur->next;
	}
}

void push_front (list_t *l, char *word) {
	node_t *n;
	int i = 0;
	int vol = 10;
	n = (node_t*) malloc(sizeof(node_t));
	if (n == NULL) {
		printf("Not enough memory!");
		return;
	}
	n->value = malloc(vol * sizeof(char));
	if (n->value == NULL) {
		printf("Not enough memory!");
		return;
	}
	while (word[i] != 0) {
		if (i == vol) {
			vol *= 2;
			char *tmp = realloc(n->value, vol * sizeof(char));
			if (tmp == NULL) {
				free(n->value);
				printf("Not enough memory!");
				return;
			} else {
				n->value = tmp;
			}
		}
		n->value[i] = word[i];
		i++;
	}
	n->next = l->head;
	l->head = n;
}

void print (list_t *l) {
	node_t *cur = l->head;
	while (cur) {
		printf("%s\n", cur->value);
		cur = cur->next;
	}
}

void destroy (list_t *l) {
	node_t *cur = l->head;
	node_t *next_t = cur->next;
	while (next_t) {
		free(cur);
		cur = next_t;
		next_t = cur->next;
	}
}

int main () {
	char in_word = 0;
	int i = 0, a = 0, len = 10;
	list_t l1, l2;
	init(&l1);
	char *word = malloc(len * sizeof(char));
	if (word == NULL) {
		printf("Not enough memory!");
		return 1;
	}
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
				push_front(&l1, word);
				free(word);
				word = malloc(len * sizeof(char));
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
		word[i] = 0;
		push_front(&l1, word);
	}
	bubble_sort(&l1);
	node_t *cur = l1.head;
	init(&l2);
	while (cur) {
		push_front(&l2, cur->value);
		cur = cur->next;
	}
	destroy(&l1);
	print(&l2);
	destroy(&l2);
	return 0;
}
