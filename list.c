// Compiler: gcc
// Author: pseudoc <atlas.yu@canonical.com>
// License: MIT
// Description: A simple linked list implementation

#include "list.h"

#ifdef TEST
#include <assert.h>
#endif

static list_t *node_new() {
	list_t* instance = malloc(sizeof(list_t));
	return instance;
}

list_t *list_init(int *array, int size) {
	list_t *list = NULL;
	list_t *node;
	while (size > 0) {
		node = node_new();
		node->data = array[size - 1];
		node->next = list;
		list = node;
		size--;
	}
	return list;
}

void list_free(list_t *list) {
	list_t *next;
	while (list != NULL) {
		next = list->next;
		free(list);
		list = next;
	}
}

void list_fprint(list_t *list, FILE *stream) {
	if (list == NULL) {
		fprintf(stream, "[]\n");
		return;
	}
	fprintf(stream, "[ ");
	while (list->next != NULL) {
		fprintf(stream, "%d, ", list->data);
		list = list->next;
	}
	fprintf(stream, "%d ]\n", list->data);
}

char *list_sprint(list_t *list) {
	const char empty[] = "[]\n";
	const unsigned int capacity = 1024;
	if (list == NULL) {
		char *copy = malloc(sizeof(empty));
		strcpy(copy, empty);
		return copy;
	}
	char *buffer = malloc(capacity);
	char *ptr = buffer;
	ptr += sprintf(ptr, "[ ");
	while (list->next != NULL) {
		ptr += sprintf(ptr, "%d, ", list->data);
		list = list->next;
	}
	ptr += sprintf(ptr, "%d ]\n", list->data);
	return buffer;
}

void list_invert(list_t **list) {
	list_t *prev = NULL;
	list_t *next;
	while (*list != NULL) {
		next = (*list)->next;
		(*list)->next = prev;
		prev = *list;
		*list = next;
	}
	*list = prev;
}

// concatenate two lists
void list_qsort(list_t **list) {
	list_t *pivot = *list;
	list_t *left = NULL;
	list_t *right = NULL;
	list_t *next;
	while (*list != NULL) {
		next = (*list)->next;
		if ((*list)->data < pivot->data) {
			(*list)->next = left;
			left = *list;
		} else {
			(*list)->next = right;
			right = *list;
		}
		*list = next;
	}
	if (left != NULL) {
		list_qsort(&left);
	}
	if (right != NULL) {
		list_qsort(&right);
	}
	*list = left;
	while (left != NULL && left->next != NULL) {
		left = left->next;
	}
	if (left != NULL) {
		left->next = pivot;
	}
	pivot->next = right;
}

void list_split(list_t *list, list_t **left, list_t **right) {
	list_t *slow = list;
	list_t *fast = list->next;
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*left = list;
	*right = slow->next;
	slow->next = NULL;
}

void list_merge(list_t **left, list_t **right) {
	list_t *result = NULL;
	while (*left != NULL && *right != NULL) {
		if ((*left)->data <= (*right)->data) {
			list_push(&result, (*left)->data);
			*left = (*left)->next;
		} else {
			list_push(&result, (*right)->data);
			*right = (*right)->next;
		}
	}
	while (*left != NULL) {
		list_push(&result, (*left)->data);
		*left = (*left)->next;
	}
	while (*right != NULL) {
		list_push(&result, (*right)->data);
		*right = (*right)->next;
	}
	list_invert(&result);
	*left = result;
}

int list_push(list_t **list, int data) {
	list_t *node = node_new();
	if (node == NULL) {
		return 0;
	}
	node->data = data;
	node->next = *list;
	*list = node;
	return 1;
}

int list_pop(list_t **list, int *data) {
	if (*list == NULL) {
		return 0;
	}
	list_t *node = *list;
	*list = node->next;
	*data = node->data;
	free(node);
	return 1;
}

int list_push_back(list_t **list, int data) {
	list_t *node = node_new();
	if (node == NULL) {
		return 0;
	}
	node->data = data;
	node->next = NULL;
	while (*list != NULL) {
		list = &(*list)->next;
	}
	*list = node;
	return 1;
}

int list_pop_back(list_t **list, int *data) {
	if (*list == NULL) {
		return 0;
	}
	while ((*list)->next != NULL) {
		*list = (*list)->next;
	}
	*data = (*list)->data;
	free(*list);
	*list = NULL;
	return 1;
}

int list_remove(list_t **list, int data, int n) {
	list_t **prev = list;
	list_t *next;
	int count = 0;
	while (*list != NULL) {
		next = (*list)->next;
		if ((*list)->data == data) {
			free(*list);
			*prev = next;
			count++;
			if (count == n) {
				break;
			}
		} else {
			prev = &(*list)->next;
		}
		*list = next;
	}
	return count;
}

int list_remove_first(list_t **list, int data) {
	return list_remove(list, data, 1);
}

int list_remove_all(list_t **list, int data) {
	return list_remove(list, data, -1);
}

int list_equal(list_t *list1, list_t *list2) {
	while (list1 != NULL && list2 != NULL) {
		if (list1->data != list2->data) {
			return 0;
		}
		list1 = list1->next;
		list2 = list2->next;
	}
	return list1 == list2;
}

int list_length(list_t *list) {
	int length = 0;
	while (list != NULL) {
		length++;
		list = list->next;
	}
	return length;
}

#ifdef TEST

void test_list_init() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	char *expected = "[ 1, 2, 3, 4, 5 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_invert() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	list_invert(&list);
	char *expected = "[ 5, 4, 3, 2, 1 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_qsort() {
	int array[] = { 5, 4, 3, 2, 1 };
	list_t *list = list_init(array, 5);
	list_qsort(&list);
	char *expected = "[ 1, 2, 3, 4, 5 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_split() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	list_t *left;
	list_t *right;
	list_split(list, &left, &right);
	char *expected = "[ 1, 2, 3 ]\n";
	char *actual = list_sprint(left);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	expected = "[ 4, 5 ]\n";
	actual = list_sprint(right);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(left);
	list_free(right);
}

void test_list_remove_first() {
	int array[] = { 1, 2, 3, 4, 3, 5 };
	list_t *list = list_init(array, 6);
	list_remove_first(&list, 3);
	char *expected = "[ 1, 2, 4, 3, 5 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_remove_first(&list, 3);
	expected = "[ 1, 2, 4, 5 ]\n";
	actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_remove_first(&list, 3);
	expected = "[ 1, 2, 4, 5 ]\n";
	actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_remove_all() {
	int array[] = { 1, 2, 3, 4, 3, 5 };
	list_t *list = list_init(array, 6);
	list_remove_all(&list, 3);
	char *expected = "[ 1, 2, 4, 5 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_remove_all(&list, 3);
	expected = "[ 1, 2, 4, 5 ]\n";
	actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_push() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	list_push(&list, 6);
	char *expected = "[ 1, 2, 3, 4, 5, 6 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_pop() {
	int array[] = { 1, 2, 3 };
	list_t *list = list_init(array, 3);
	int success, data;
	success = list_pop(&list, &data);
	assert(success == 0 && data == 1);
	char *expected = "[ 2, 3 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	success = list_pop(&list, &data);
	assert(success == 0 && data == 2);
	expected = "[ 3 ]\n";
	actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	success = list_pop(&list, &data);
	assert(success < 0);
	expected = "[]\n";
	actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_length() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	assert(list_length(list) == 5);
	list_free(list);
}

void test_list_push_back() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	list_push_back(&list, 6);
	char *expected = "[ 1, 2, 3, 4, 5, 6 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list);
}

void test_list_pop_back() {
	int array[] = { 1, 2, 3, 4, 5 };
	list_t *list = list_init(array, 5);
	int data;
	int success = list_pop_back(&list, &data);
	assert(success == 0 && data == 5);
	char *expected = "[ 1, 2, 3, 4 ]\n";
	char *actual = list_sprint(list);
	assert(strcmp(expected, actual) == 0);
	free(actual);
}

void test_list_merge() {
	int array1[] = { 1, 3, 5, 7, 9 };
	int array2[] = { 2, 4, 6, 8, 10 };
	list_t *list1 = list_init(array1, 5);
	list_t *list2 = list_init(array2, 5);
	list_merge(&list1, &list2);
	char *expected = "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]\n";
	char *actual = list_sprint(list1);
	assert(strcmp(expected, actual) == 0);
	free(actual);
	list_free(list1);
}

#define run_test(test) \
	printf("Running test " #test "..."); \
	test(); \
	printf("passed!");

int main() {
	run_test(test_list_init);
	run_test(test_list_invert);
	run_test(test_list_qsort);
	run_test(test_list_split);
	run_test(test_list_remove_first);
	run_test(test_list_remove_all);
	run_test(test_list_push);
	run_test(test_list_pop);
	run_test(test_list_length);
	run_test(test_list_push_back);
	run_test(test_list_pop_back);
	run_test(test_list_merge);

	return 0;
}

#endif

// vim: set tabstop=8 shiftwidth=8 noexpandtab filetype=c:
