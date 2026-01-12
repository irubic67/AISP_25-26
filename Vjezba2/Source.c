#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define NAME_LENGTH 50
#define ERROR -1
#define WARNING 1

struct Person {
	char firstName[NAME_LENGTH];
	char lastName[NAME_LENGTH];
	int yearOfBirth;
	struct Person* next;
};
typedef struct Person* Position;

int pushFront(Position);
int printList(Position);
int pushBack(Position);
Position findElement(Position, char[]);
void deleteElement(Position);
Position findPrevious(Position, char[]);
int pushAfter(Position, char[]);
int pushBefore(Position, char[]);
int writeListToFile(Position, char[]);
int readFromFile(Position, char[]);
void sortList(Position);
int deleteAll(Position);

int main() {
	struct Person head;
	Position person_x = NULL;
	char lastName[NAME_LENGTH] = "";
	char fileName[NAME_LENGTH] = "";
	int choice = 0;
	int choice1 = 0;
	int check = 0;
	head.next = NULL;
	printf("1.Input at the beginning\n2.Input at the end\n3.Output of the list\n4.Finding the list element\n5.Removing the list element\n");
	printf("6.Add before\n7.Add after\n8.Input list in file\n9.Read list from file\n10.Sort list\n");
	do {

		printf("Input number 1-10\n");
		scanf(" %d", &choice);
		if (choice < 1 || choice > 10) {
			printf("Incorrect input\n");
			break;
		}
		else {
			switch (choice) {
			case 1:
				check = pushFront(&head);
				if (check == -1) {
					deleteAll(&head.next);
					printf(" Error.\n");
					return ERROR;
				}
				else {
					printf(" Everything is okay.\n");
				}
				break;
			case 2:
				check = pushBack(&head);
				if (check == -1) {
					deleteAll(&head.next);
					printf("Error.\n");
					return ERROR;
				}
				else {
					printf(" Everything is okay.\n");
				}
				break;
			case 3:
				printList(head.next);
				break;
			case 4:
				printf("Enter surname:\t");
				scanf(" %s", lastName);
				person_x = findElement(head.next, lastName);
				if (person_x == NULL) {
					printf("Surname not found!\n");
				}
				else {
					printf("Name, Surname and Year of birth of a person: %s %s %d found\n", person_x->firstName, person_x->lastName, person_x->yearOfBirth);
				}
				break;
			case 5:
				deleteElement(&head);
				printList(head.next);
				break;
			case 6:
				printf("Enter surnmae:\t");
				scanf(" %s", lastName);
				check = pushBefore(&head, lastName);
				if (check == -1) {
					deleteAll(&head.next);
					printf(" Error.\n");
					return ERROR;
				}
				else if (check == 1) {
					printf("WARNING! surname not found.\n");
				}
				else {
					printf(" Everything is okay.\n");
				}
				break;
			case 7:
				printf("Enter surname:\t");
				scanf(" %s", lastName);
				check = pushAfter(&head, lastName);
				if (check == -1) {
					deleteAll(&head.next);
					printf(" ERROR.\n");
					return ERROR;
				}
				else if (check == 1) {
					printf("WARNING! Surname not found.\n");
				}
				else {
					printf("Everything is okay.\n");
				}
				break;
			case 8:
				printf("Enter file name:\t");
				scanf(" %s", fileName);
				check = writeListToFile(&head, fileName);
				if (check == -1) {
					deleteAll(&head.next);
					printf(" Error.\n");
					return ERROR;
				}
				else {
					printf(" Everything is okay.\n");
				}
				break;
			case 9:
				printf("Enter file name:\t");
				scanf(" %s", fileName);
				check = readFromFile(&head, fileName);
				if (check == -1) {
					deleteAll(&head.next);
					printf(" Error.\n");
					return ERROR;
				}
				else {
					printf(" Everything is okay.\n");
				}
				break;
			case 10:
				sortList(&head);
				break;
			}
		}
		check = 0;
		printf("To stop press -1, to continue press 0!\n");
		scanf(" %d", &choice1);
	} while (choice1 != -1);
	deleteAll(&head);
	printList(head.next);
	return 0;
}

int pushFront(Position P) {
	Position Q = NULL;

	Q = (Position)malloc(sizeof(struct Person));
	if (Q == NULL) {
		printf("Memory not allocated");
		return ERROR;
	}
	printf("Enter name, surname and date of birth:\t");
	scanf(" %s %s %d", Q->firstName, Q->lastName, &(Q->yearOfBirth));
	Q->next = P->next;
	P->next = Q;
	return 0;
}

int printList(Position P) {
	if (P == NULL) {
		printf("Empty list\n");
		return 0;
	}
	while (P != NULL) {
		printf(" %s %s %d\n", P->firstName, P->lastName, P->yearOfBirth);
		P = P->next;
	}
	return 0;
}
int pushBack(Position P) {

	while (P->next != NULL) {

		P = P->next;
	}
	return pushFront(P);
}
Position findElement(Position P, char lastName[]) {

	while (P != NULL) {
		if (strcmp(P->lastName, lastName) == 0) {
			return P;
		}
		P = P->next;
	}
	printf("Surname not foung\n");
	return NULL;
}

void deleteElement(Position P) {
	Position tmp = NULL;
	char lastName[128] = "\0";
	printf("Enter surname:\n ");
	scanf(" %s", lastName);
	while (P->next != NULL && strcmp(P->next->lastName, lastName) != 0) {
		P = P->next;
	}
	if (P->next != NULL)
	{
		tmp = P->next;
		P->next = tmp->next;
		printf("Delete element: %s %s %d\n", tmp->firstName, tmp->lastName, tmp->yearOfBirth);
		free(tmp);
	}
}

Position findPrevious(Position P, char lasteName[]) {

	while (P->next != NULL && strcmp(P->next->lastName, lasteName) != 0) {
		P = P->next;
	}
	if (P->next != NULL) {
		return P;
	}
	else
	{
		return NULL;
	}
}
int pushAfter(Position P, char lasteName[]) {
	P = findPrevious(P, lasteName);
	if (P == NULL) {
		return WARNING;
	}
	P = P->next;
	return pushFront(P);
}

int pushBefore(Position P, char lastName[]) {
	P = findPrevious(P, lastName);
	if (P == NULL) {
		return WARNING;
	}
	return pushFront(P);
}

int writeListToFile(Position P, char filename[]) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	P = P->next;
	if (fp == NULL) {
		printf("File not opened!!!");
		return ERROR;
	}
	while (!feof(fp) && P != NULL) {
		fprintf(fp, " %s %s %d\n", P->firstName, P->lastName, P->yearOfBirth);
		P = P->next;
	}
	fclose(fp);
	return 0;
}
int readFromFile(Position P, char fileName[]) {
	FILE* fp = NULL;
	Position Q = NULL;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File not opened!!!");
		return ERROR;
	}
	while (!feof(fp)) {
		Q = (Position)malloc(sizeof(struct Person));
		if (Q == NULL) {
			printf("Memory not allocated");
			fclose(fp);
			return ERROR;
		}
		if (fscanf(fp, "%s %s %d", Q->firstName, Q->lastName, &Q->yearOfBirth) == 3) {
			Q->next = P->next;
			P->next = Q;
			printf("%s %s %d\n", Q->firstName, Q->lastName, Q->yearOfBirth);
		}

	}
	fclose(fp);
	return 0;
}
void sortList(Position P) {
	Position end = NULL, start = NULL, j = NULL, prev_j = NULL;

	while (P->next != end)
	{
		start = P;
		prev_j = start->next;
		j = prev_j->next;

		while (j != end)
		{
			if (_strcmpi(prev_j->lastName, j->lastName) > 0)
			{
				prev_j->next = j->next;
				start->next = j;
				j->next = prev_j;
			}
			else
				start = prev_j;
			prev_j = j;
			j = j->next;
		}
		end = prev_j;
	}
}
int deleteAll(Position P) {
	Position temp = NULL, start = P;

	while (P->next != NULL)
	{
		while (P->next->next != NULL)
			P = P->next;

		temp = P->next;
		P->next = temp->next;
		free(temp);
		P = start;
	}

	return 0;
}