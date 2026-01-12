#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ERRORMEMORY -2
#define MAX 100
#define MIN 10
struct node;
typedef struct node* Position;
struct node {
	int element;
	Position next;
};

int PushStack(Position, int);
int PushQueue(Position, int);
int Pop(Position);
int getRandom();
int Print(Position);
int deletAll(Position);

int main() {

	struct node headStack;
	struct node headQueue;
	int resualt = 0, choice = 0;
	headQueue.next = NULL;
	headStack.next = NULL;
	printf("Enter what you want to do:\n1.Push on the stack\n2.Pop from the stack\n3.Print stack\n4.Print Queue\n5.Push on the queue\n6.Pop from the queue\n");
	do {
		printf("Unesi 1,2,3,4,5 ili 6\n");
		scanf(" %d", &choice);
		if (choice < 1 || choice > 6) {
			printf(" Netocan unos!!!\n");
		}
		else
		{
			switch (choice) {
			case 1:
				resualt = PushStack(&headStack, getRandom());
				if (resualt == -2) {
					printf(" Greska.\n");
					deletAll(&headStack);
					deletAll(&headQueue);
					return ERRORMEMORY;
				}
				else {
					printf(" Sve je proslo u redu.\n");
				}
				break;
			case 2:
				resualt = Pop(&headStack);
				break;
			case 3:
				printf("Stack is:");
				Print(headStack.next);
				break;
			case 4:
				printf("Queue is:");
				Print(headQueue.next);
				break;
			case 5:
				resualt = PushQueue(&headQueue, getRandom());
				if (resualt == -2) {
					printf(" Greska.\n");
					deletAll(&headStack);
					deletAll(&headQueue);
					return ERRORMEMORY;
				}
				else {
					printf(" Sve je proslo u redu.\n");
				}
				break;
			case 6:
				resualt = Pop(&headQueue);
				break;
			}
		}
		printf("If you want to stop press -1, if you want to continue press 0!\n");
		scanf(" %d", &choice);
	} while (choice != -1);
	deletAll(&headStack);
	deletAll(&headQueue);
	return 0;
}
int getRandom() {
	int value = 0;
	//srand((unsigned)time(NULL));
	value = rand() % ((MAX - MIN + 1) + MIN);
	return value;
}
int PushStack(Position P, int value) {
	Position temp;
	temp = (Position)malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("Memory is not allocated!!!");
		return ERRORMEMORY;
	}
	temp->element = value;
	temp->next = P->next;
	P->next = temp;
	return 0;
}
int Pop(Position P) {
	Position temp = NULL;
	if (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		printf("Deleted value is %d\n", temp->element);
		free(temp);
	}
	return 0;
}
int Print(Position P) {
	if (P == NULL) {
		printf("Prazna lista\n");
		return 0;
	}
	while (P != NULL) {
		printf(" %d\t", P->element);
		P = P->next;
	}
	printf("\n");
	return 0;
}
int PushQueue(Position  P, int value) {
	static Position last = NULL;
	Position temp = NULL;
	if (last == NULL) {
		last = P;
	}
	temp = (Position)malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("Memory is not allocated!!!");
		return ERRORMEMORY;
	}
	temp->element = value;
	temp->next = last->next;
	last->next = temp;
	last = last->next;
	return 0;
}
int deletAll(Position P) {
	Position temp = NULL;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);

	}
	return 0;
}