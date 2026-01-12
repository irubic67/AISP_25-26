#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ERRORFILE -1;
#define ERRORMEMORY -2;
struct node;
typedef struct node* Position;
struct node {
	int Element;
	Position Next;
};
int readFromFile(Position);
int Intersection(Position, Position, Position);
int printList(Position);
int Union(Position, Position, Position);
int freeAll(Position);
int main() {

	struct node head1;
	struct node head2;
	struct node headPresjek;
	struct node headUnija;
	int result = 0;
	head1.Next = NULL;
	head2.Next = NULL;
	headPresjek.Next = NULL;
	headUnija.Next = NULL;
	result = readFromFile(&head1);
	if (result == -1) {
		printf("Error! File not open!\n");
		return 0;
	}
	else if (result == -2) {
		printf("Error! Memory is not allocated!\n");
		freeAll(&head1);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printf("List 1:\t");
	printList(head1.Next);
	result = readFromFile(&head2);
	if (result == -1) {
		printf("Error! File not open!\n");
		freeAll(&head1);
		return 0;
	}
	else if (result == -2) {
		printf("Error! Memory is not allocated!\n");
		freeAll(&head1);
		freeAll(&head2);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printf("Lista2:\t");
	printList(head2.Next);
	result = Intersection(head1.Next, head2.Next, &headPresjek);
	if (result == -2) {
		printf("Error! Memory is not allocated!\n");
		freeAll(&head1);
		freeAll(&head1);
		freeAll(&headPresjek);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printf("Presjek:");
	printList(headPresjek.Next);
	result = Union(head1.Next, head2.Next, &headUnija);
	if (result == -2) {
		printf("Error! Memory is not allocated!\n");
		freeAll(&head1);
		freeAll(&head1);
		freeAll(&headUnija);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printf("Union:\t");
	printList(headUnija.Next);
	freeAll(&head1);
	freeAll(&head2);
	freeAll(&headPresjek);
	freeAll(&headUnija);
	printList(headPresjek.Next);
	printList(headUnija.Next);
	printList(head1.Next);
	printList(head2.Next);
	return 0;
}
int readFromFile(Position P) {
	FILE* fp = NULL;
	char fileName[128] = "\0";
	Position q = NULL;
	printf("Type in the name of file:\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File is not opened!!!\n");
		return ERRORFILE;
	}
	while (!feof(fp)) {
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Allocation failed!!!\n");
			fclose(fp);
			return ERRORMEMORY;
		}

		while (P->Next != NULL) {
			P = P->Next;
		}
		fscanf(fp, "%d", &q->Element);
		q->Next = P->Next;
		P->Next = q;
	}
	fclose(fp);
	return 0;
}
int Intersection(Position L1, Position L2, Position P) {
	Position q = NULL;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1->Element == L2->Element) {
			q = (Position)malloc(sizeof(struct node));
			if (q == NULL) {
				printf("Allocation failed!!!\n");
				return ERRORMEMORY;
			}
			q->Element = L1->Element;
			q->Next = P->Next;
			P->Next = q;
			P = P->Next;
			L1 = L1->Next;
			L2 = L2->Next;
		}
		else if (L1->Element > L2->Element) {
			L2 = L2->Next;
		}
		else if (L1->Element < L2->Element) {
			L1 = L1->Next;
		}
	}
	return 0;
}
int printList(Position P) {
	if (P == NULL) {
		printf("Empty list\n");
		return 0;
	}
	while (P != NULL) {
		printf(" %d\t", P->Element);
		P = P->Next;
	}
	printf("\n");
	return 0;
}
int Union(Position L1, Position L2, Position U) {
	Position q = NULL;
	while (L1 != NULL || L2 != NULL)
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Allocation failed!!!\n");
			return ERRORMEMORY;
		}
		if (L1 == NULL) {
			q->Element = L2->Element;
			L2 = L2->Next;
		}
		else if (L2 == NULL) {
			q->Element = L1->Element;
			L1 = L1->Next;
		}
		else
		{
			if (L1->Element > L2->Element) {
				q->Element = L2->Element;
				L2 = L2->Next;
			}
			else if (L1->Element < L2->Element) {
				q->Element = L1->Element;
				L1 = L1->Next;
			}
			else{
				q->Element = L1->Element;
				L1 = L1->Next;
				L2 = L2->Next;
			}
		}
		q->Next = U->Next;
		U->Next = q;
		U = U->Next;
	}
	return 0;
}
int freeAll(Position P) {
	Position temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
		
	}
	return 0;
}