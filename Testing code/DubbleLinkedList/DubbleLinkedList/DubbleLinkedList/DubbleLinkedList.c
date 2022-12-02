//#include <stdlib.h>
//#include <stdio.h>
//
//struct date {
//    unsigned char day; // 5 bits 
//    unsigned char  month; // 4 bits
//    unsigned char year; // 7 bits
//
//}; // total 4 bytes
//
//struct time
//{
//    unsigned char seconds; // 6 bits
//    unsigned char minutes; // 6 bits
//    unsigned char hours;
//};
//
//
//struct DoubleLinkedList
//{
//
//	struct time *t;
//	struct date *d;
//	char temprature; 
//	struct DoubleLinkedList* nextNode;
//	struct DoubleLinkedList* previusNode;
//};
//
//struct DoubleLinkedList* createDoubleLinkedList(struct time* t, struct date* d, char temp) {
//
//	struct DoubleLinkedList* DoubleLinkedList; 
//	DoubleLinkedList = (struct DoubleLinkedList*)malloc(sizeof(struct DoubleLinkedList));
//
//	if (DoubleLinkedList == NULL) {
//		return NULL; //then check in add() if createDoubleLinkedList return Null, if so: remove FIFO
//	}
//
//	DoubleLinkedList->d = d;
//	DoubleLinkedList->t = t;
//	DoubleLinkedList->temprature = temp;
//	DoubleLinkedList->nextNode = NULL;
//	DoubleLinkedList->previusNode = NULL;
//}
//
//void printDoubleLinkedList(struct DoubleLinkedList* head) {
//	while (head != NULL)
//	{
//		printf("timestamp: %d/%d/20%d %d:%d:%d \ntemprature: %i\n", (head->d->day), (head->d->month), head->d->year, head->t->hours, (head->t->minutes), (head->t->seconds), head->temprature);
//		head = head->nextNode;
//	}
//}
//void insertDoubleLinkedList(struct DoubleLinkedList** head, struct DoubleLinkedList* newHead) {
//	
//	
//	if (newHead == NULL || *head == NULL)
//		return; 
//
//	if (isMember(head, newHead) == 1)
//		return; 
//
//	struct DoubleLinkedList* tempHead = *head;
//
//	// if list has ONLY one element: 
//	
//
//	// case 1: one element in list 
//	// the head = the tale. 
//
//
//	// case 2: two elemets in list
//
//	// generall case: more than 3 elements in list. 
//
//}
//
////int main() {
////
////	struct time t1 = { 1,2,3 };
////	struct time d1 = { 1,5,10 };
////
////	// 
////	struct DoubleLinkedList* head = createDoubleLinkedList(&t1, &d1, 22);
////	struct DoubleLinkedList* tale = head;
////	
////
////	/*if (head2 == NULL) {
////		removeLast(% head);
////	}*/
////
////	head->nextNode = head2;
////	printDoubleLinkedList(head);
////	printf("%d:%d:%d", t1.hours, t1.minutes, t1.seconds );
////
////
////
////}