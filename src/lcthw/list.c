#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
	LIST_FOREACH(list, first, next, cur) {
		if(cur->prev) {
			free(cur->prev);
		}
	}
	
	free(list->last);
	free(list);
}


void List_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}
}


void List_clear_destroy(List *list)
{
	List_clear(list);
	List_destroy(list);
}


void List_push(List *list, void *value)
{
	// insert new node in the end of list
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->last == NULL) {
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	
	list->count++;
	
error:
	return;
}

void *List_pop(List *list)
{
	// remove last node from list
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_shift(List *list, void *value)
{
	// insert node in front of list
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->first == NULL) {
		list->first = node;
		list->last = node;
	} else {
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}
	
	list->count++;

error:
	return;
}

void *List_unshift(List *list)
{
	// remove first node from list
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	// remove any node from list function
	void *result = NULL;
	
	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL");
	
	if(node == list->first && node == list->last) {
		// remove node which is only one in list
		list->first = NULL;
		list->last = NULL;
	} else if(node == list->first) {
		// remove node which is first in list
		list->first = node->next;
		check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
		list->first->prev = NULL;
	} else if(node == list->last) {
		// remove node which is last in list
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, somehow got a next is NULL.");
		list->last->next = NULL;
	} else {
		// remove node which is not first and not last and list has at least 2 nodes
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}
	
	list->count--;
	result = node->value;
	free(node);
	
error:
	return result;
}
