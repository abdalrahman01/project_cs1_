
#ifndef __LINKED_LISTS
#include "calendar.h"

struct LinkedList {
	struct time t; // time hh:mm:ss
	struct date d; // date yymmdd
	double temprature;
	struct LinkedList* next;
};
void removeList(struct LinkedList** first, struct LinkedList* el);
void printList(struct LinkedList* first);
int isMember(struct LinkedList** first, struct LinkedList* el);
struct LinkedList* createElement(struct time t, struct date * d, double temprature);
void insertFirst(struct LinkedList** first, struct LinkedList* el);
void removeLast(struct LinkedList** first);



#endif