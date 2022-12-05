#include <stdio.h>
#include <stdlib.h>


struct date {
	unsigned char dd:5;
	unsigned char mm:4;
	unsigned char mm1 : 4;

	unsigned short yyyy;

};


int main() {
	printf("%d", sizeof(struct date));
	return 0; 
}