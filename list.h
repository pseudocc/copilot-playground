// generate content according to list.c

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _node list_t;

struct _node {
	int data;
	struct _node *next;
};

/**
 * @brief Initialize a list from an array
 * @param array The array to initialize the list from
 * @param size The size of the array
 * @return The initialized list
 * @note The returned list must be freed
 *
 * @code
 * list_t *list = list_init(array, size);
 * // do something with the list
 * list_free(list);
 * @endcode
 *
 * @see list_free
**/
list_t *list_init(int *array, int size);

/**
 * @brief Free a list
 * @param list The list to free
 * @return void
 * @note This function frees the list and all nodes
 *
 * @see list_init
**/
void list_free(list_t *list);

/**
 * @brief Print a list to a stream
 * @param list The list to print
 * @param stream The stream to print to
 * @return void
 *
 * @code
 * list_fprint(list, stdout);
 * @endcode
 *
 * @see list_sprint
**/
void list_fprint(list_t *list, FILE *stream);

/**
 * @brief Print a list to a string
 * @param list The list to print
 * @return The string representation of the list
 * @note The returned string must be freed
 *
 * @code
 * char *str = list_sprint(list);
 * printf("%s", str);
 * free(str);
 * @endcode
 *
 * @see list_fprint
**/
char *list_sprint(list_t *list);

/**
 * @brief Invert a list
 * @param list The list to invert
 * @return void
 * @note This function inverts the list in place
 *
 * @see list_qsort
**/
void list_invert(list_t **list);

/**
 * @brief Quick sort a list
 * @param list The list to sort
 * @return void
 * @note This function sorts the list in place
 *
 * @see list_invert
**/
void list_qsort(list_t **list);

/**
 * @brief Split a list into two lists
 * @param list The list to split
 * @param left The left list
 * @param right The right list
 * @return void
 * @note This function splits the list in place
 *
 * @see list_qsort, list_merge
**/
void list_split(list_t *list, list_t **left, list_t **right);

/**
 * @brief Merge two lists
 * @param left The left list
 * @param right The right list
 * @return The merged list
 * @note This function merges the two lists in place
 * @note The returned list must be freed
 *
 * @see list_qsort, list_split
**/
void list_merge(list_t **left, list_t **right);

/**
 * @brief Push an element to the front of a list
 * @param list The list to push to
 * @param data The data to push
 * @return 0 on success, -1 on failure
 * @note This function pushes the data to the front of the list
 *
 * @see list_pop, list_push_back, list_pop_back
**/
int list_push(list_t **list, int data);

/**
 * @brief Pop an element from the front of a list
 * @param list The list to pop from
 * @param data The data to pop
 * @return 0 on success, -1 on failure
 * @note This function pops the data from the front of the list
 *
 * @see list_push, list_push_back, list_pop_back
**/
int list_pop(list_t **list, int *data);

/**
 * @brief Push an element to the back of a list
 * @param list The list to push to
 * @param data The data to push
 * @return 0 on success, -1 on failure
 * @note This function pushes the data to the back of the list
 *
 * @see list_pop, list_push, list_pop_back
**/
int list_push_back(list_t **list, int data);

/**
 * @brief Pop an element from the back of a list
 * @param list The list to pop from
 * @param data The data to pop
 * @return 0 on success, -1 on failure
 * @note This function pops the data from the back of the list
 *
 * @see list_pop, list_push, list_push_back
**/
int list_pop_back(list_t **list, int *data);

/**
 * @brief Check if two lists are identical
 * @param left The left list
 * @param right The right list
 * @return 1 if the lists are equal, 0 otherwise
 * @note This function checks if the lists are equal
**/
int list_equal(list_t *left, list_t *right);

/**
 * @brief Remove the first N-th matching element from a list
 * @param list The list to remove from
 * @param data The data to remove
 * @param n The first N-th element to remove
 * @return the number of elements removed
**/
int list_remove(list_t **list, int data, int n);

/**
 * @brief Remove all matching elements from a list
 * @param list The list to remove from
 * @param data The data to remove
 * @return the number of elements removed
**/
int list_remove_all(list_t **list, int data);

/**
 * @brief Remove the first matching element from a list
 * @param list The list to remove from
 * @param data The data to remove
 * @return the number of elements removed
**/
int list_remove_first(list_t **list, int data);

#endif // LIST_H
