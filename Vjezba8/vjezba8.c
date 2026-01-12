#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define ERRORFILE -1
#define ERRORMEMORY -2

struct node;
typedef struct node* Position;
struct node {
    int element;
    Position next;
};

int PushStack(Position, int);
int Pop(Position, int*);
int calculate(Position);
int Print(Position);
int deleteAll(Position);
int Count(Positon);

int main() {
    struct node Head;
    Head.next = NULL;

    if (calculate(&Head) == 0) {
        printf("The result is: ");
        Print(Head.next);
    }

    deleteAll(&Head);
    return 0;
}

int PushStack(Position P, int value) {
    Position temp = (Position)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory not allocated!\n");
        return ERRORMEMORY;
    }
    temp->element = value;
    temp->next = P->next;
    P->next = temp;
    return 0;
}

int Pop(Position P, int* value) {
    Position temp = NULL;
    if (P->next == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    temp = P->next;
    *value = temp->element;
    P->next = temp->next;
    free(temp);
    return 0;
}

int calculate(Position P) {
    FILE* fp;
    char buffer[128];
    int operand1, operand2, result;

    fp = fopen("postfix.txt", "r");
    if (fp == NULL) {
        printf("File not opened!\n");
        return ERRORFILE;
    }

    while (fscanf(fp, "%s", buffer) == 1) {
        if (PushStack(P, atoi(buffer)) != 0)
        {
            printf("Memory allocation error!\n");
            deleteAll(P);
            fclose(fp);
            return ERRORMEMORY;
        }

        else if (strlen(buffer) == 1 && strchr("+-*/", buffer[0])) { 
            if (Pop(P, &operand2) != 0 || Pop(P, &operand1) != 0) {
                printf("Postfix is not correct!\n");
                fclose(fp);
                return -1;
            }

            switch (buffer[0]) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    printf("Cannot divide 0!\n");
                    fclose(fp);
                    return -1;
                }
                result = operand1 / operand2;
                break;
            default:
                printf("Unknown operator: %c\n", buffer[0]);
                fclose(fp);
                return -1;
            }
            if (PushStack(P, result) != 0)
            {
                printf("Memory allocation error!\n");
                deleteAll(P);
                fclose(fp);
                return ERRORMEMORY;
            }

        }
        else {
            printf("Unknown symbol: %s\n", buffer);
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

int Print(Position P) {
    if (P == NULL) {
        printf("Empty stack\n");
        return 0;
    }
    while (P != NULL) {
        printf("%d ", P->element);
        P = P->next;
    }
    printf("\n");
    return 0;
}

int Count(Position P)
{
    int count = 0;
    while (P != NULL)
    {
        count++;
        P = P->next;
    }
    return count;
}


int deleteAll(Position P) {
    Position temp = NULL;
    while (P->next != NULL) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }
    return 0;
}
