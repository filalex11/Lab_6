#include <stdio.h>
#include <stdlib.h>
/* Написать программу, которая создает линейный упорядоченный список из вводимых слов, после чего создает копию списка с элементами в обратном порядке */
typedef struct node {
	char value[128];
	struct node *next;
} node_t;

typedef struct {
	node_t *head;
	size_t size;
} list_t;

void init (list_t *l) {
	l->head = NULL;
	l->size = 0;
}

int is_letter (char str) {
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
	char trigger = 1;
	while (cur || trigger) {
		trigger = 0;
		tmp = cur->next;
		while (tmp) {
			if (strcomp(cur->value, tmp->value) > 0) {
				swap(cur->value, tmp->value);
				trigger = 1;
			}
			tmp = tmp->next;
		}
		cur = cur->next;
	}
}

void push_front (list_t *l, char *word) {
	node_t *n;
	int i = 0;
	n = (node_t*) malloc(sizeof(node_t));
	while (word[i] != 0) {
		n->value[i] = word[i];
		i++;
	}
	n->next = l->head;
	l->head = n;
	l->size++;
}

void print (list_t *l) {
	node_t *cur = l->head;
	while (cur) {
		printf("%s\n", cur->value);
		cur = cur->next;
	}
}

int main () {
	char a = 0, in_word = 0;
	int i = 0;
	list_t l1, l2;
	init(&l1);
	init(&l2);
	char *word = malloc(128 * sizeof(char));
	while ((a = getchar()) != '\n') {
		if (is_letter(a)) {
			word[i] = a;
			in_word = 1;
			i++;
		} else {
			if (in_word) {
				push_front(&l1, word);
				free(word);
				word = malloc(128 * sizeof(char));
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
	while (cur) {
		push_front(&l2, cur->value);
		cur = cur->next;
	}
	print(&l2);
	return 0;
}
