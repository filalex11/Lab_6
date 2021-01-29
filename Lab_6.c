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

int strcomp (char *s1, char *s2) {
	while ((*s1 != 0) && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

void swap (char *s1, char *s2) {
	char *tmp = s2;
	*s2 = *s1;
	s1 = tmp;
}

void push_back (list_t *l, char* word) {
	node_t *n, *cur;
	int i = 0;
	n = (node_t*) malloc(sizeof(node_t));
	while (word[i] != 0) {
		n->value[i] = word[i];
		i++;
	}
	n->next = NULL;
	if (l->head == NULL) {
		l->head = n;
	} else {
		cur = l->head;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = n;
	}
	l->size++;
}

void print (list_t *l) {
	node_t *cur = l->head;
	while (cur != NULL) {
		printf("%s\n", cur->value);
		cur = cur->next;
	}
}

int is_letter (char str) {
	if (((str >= 'A') && (str <= 'Z')) || ((str >= 'a') && (str <= 'z'))) {
		return 1;
	} else {
		return 0;
	}
}

int main () {
	char a = 0;
	int i = 0, in_word = 0, word_count = 0;
	list_t l1, l2;
	init(&l1);
	char *word = calloc(128, sizeof(char));
	while ((a = getchar()) != '\n') {
		if (is_letter(a)) {
			word[i] = a;
			in_word = 1;
			i++;
		} else {
			if (in_word) {
				push_back(&l1, word);
				word = calloc(128, sizeof(char));
				word_count++;
				i = 0;
				in_word = 0;
			}
		}
	}
	if (in_word) {
		word[i] = 0;
		push_back(&l1, word);
		word_count++;
	}
	/*i = 0;
	char *min = malloc(128 * sizeof(char));
	node_t *cur = l1.head;
	while (i < l1.size) {
		min = cur->value;
		while (cur != NULL) {
			if (cur->next->value < min) {
				min = cur->next->value;
			}
		}
		i++;
	}*/
	print(&l1);
	return 0;
}
