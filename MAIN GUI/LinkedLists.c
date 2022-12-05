#include <stdlib.h>
#include <stdio.h>
#include "calendar.h"



void removeList(struct LinkedList** first, struct LinkedList* el);
void printList(struct LinkedList* first);


struct LinkedList {
	struct time t; // time hh:mm:ss
	struct date d; // date yymmdd
	double temprature;
	struct LinkedList* next;
};
int isMember(struct LinkedList** first, struct LinkedList* el);

struct LinkedList* createElement(struct time t, struct date * d, double temprature) {

	struct LinkedList* newElement;

	// Allocate a place in memory
	newElement = (struct LinkedList*)malloc(sizeof(struct LinkedList));

	if (newElement == NULL) {
		printf("Out of memory exception!\n"); // make blinking led
		return NULL;
	}

	newElement->t = t;
	newElement->d = *d;
	newElement->temprature = temprature;
	newElement->next = NULL;

	return newElement;
}



void insertFirst(struct LinkedList** first, struct LinkedList* el) {


	// you can't add NULL to list
	if (el == NULL)
		return;

	// if given list (first) is empty;
	if (*first == NULL)
	{
		*first = el;
		return;
	}


	// you can't add list to it self
	if (isMember(first, el))
		return;

	// inserting the newElement at the beginning.
	el->next = *first;

	// changing the first element
	*first = el;
}

int isMember(struct LinkedList** first, struct LinkedList* el) {


	// if list is empty, or element is null
	if (first == NULL || el == NULL)
		return 0;
	struct LinkedList* temp = *first;


	while (temp != NULL) {
		if (temp == el)
			return 1;

		temp = temp->next;
	}


	// after traversing the entire list and not finding any thing
	return 0;
}

void printList(struct LinkedList* first) {
	while (first != NULL)
	{
		printf("timestamp: %d/%d/20%d %d:%d:%d \ntemprature: %g\n",
			(first->d.day), (first->d.month), first->d.year,
			first->t.hours, (first->t.minutes), (first->t.seconds),
			first->temprature);
		first = first->next;
	}
}

void removeList(struct LinkedList** first, struct LinkedList* el) {


	// if list is empty or element is nothing 
	if (first == NULL || el == NULL)
		return;



	struct LinkedList* temp = *first;


	// if list has one el; 
	if (temp == el)
	{
		*first = temp->next;
		return;
	}

	while (temp->next != NULL) {
		if (temp->next == el) {
			temp->next = temp->next->next;
			// every LinkedList element can exist once in another linkedlist
			return;
		}
		temp = temp->next;
	}

}

void removeLast(struct LinkedList** first) {

	struct LinkedList* temp = *first;
	struct LinkedList* temp1 = *first;

	while (temp->next != NULL) {
		temp1 = temp;
		temp = temp->next;
	}
	temp1->next = NULL;
	free(temp);
}

//struct LinkedList* getLast(struct LinkedList* first){
//	// gets the last element of the linkedlist
//	while (first->next != NULL) {
//		first = first->next;
//	}
//	return first; 
//}

int lengthList(struct LinkedList* first) {
	int n = 0;
	while (first != NULL) {
		first = first->next;
		n++;
	}
	return n;
}