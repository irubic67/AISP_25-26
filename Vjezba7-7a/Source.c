#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct _Node;
typedef struct _Node* Position;

struct _Node
{
    int Element;
    Position Next;
};

int GetValueFromRange(int, int);
int Push(Position, int, int);
int Pop(Position, int);
void PrintList(Position, int);
void DeleteAll(Position);

int main(void)
{
    struct _Node S;
    char choice = 0;
    int n = 0;
    int max = 0;

    S.Next = NULL;
    S.Element = -1;

    while (max < 5)
    {
        printf("\r\nInput stack size <5-20> : ");
        scanf_s(" %d", &max);
        if (max < 5 || max > 20)
        {
            max = 0;
            printf("\r\nWrong input!");
        }
    }

    srand((unsigned)time(NULL));

    while (choice != 'K' && choice != 'k')
    {
        printf("\r\n\t\t********************");
        printf("\r\n\t\t***   MENU   ***");
        printf("\r\n\t\t********************");
        printf("\r\n");
        printf("\r\n\t\t1.\tStack push");
        printf("\r\n\t\t2.\tStack pop");
        printf("\r\n\t\tk.\tEnd of program");
        printf("\r\n\r\nChoice : ");
        scanf_s(" %c", &choice, 1);

        switch (choice)
        {
        case '1':
            if (n < max)
                n = Push(&S, GetValueFromRange(0, 10000), n);
            else
                printf("\r\nStack is full!\r\n");
            PrintList(S.Next, n);
            break;
        case '2':
            if (n > 0)
                n = Pop(&S, n);
            else
                printf("\r\nStack is empty!\r\n");
            PrintList(S.Next, n);
            break;
        case 'K':
        case 'k':
            printf("\r\nBye bye!\r\n");
            break;
        default:
            printf("\r\nWrong choice!\r\nTry again.\r\n\r\n\r\n");
        }
    }

    // Obriši listu na kraju programa
    DeleteAll(S.Next);
    return 0;
}

int GetValueFromRange(int min, int max)
{
    return rand() % (max - min + 1) + min; // uključuje max
}

int Push(Position P, int x, int n)
{
    Position q = (Position)malloc(sizeof(struct _Node));
    if (q == NULL)
    {
        printf("\r\nMemory allocation error!\r\n");
        DeleteAll(P); // briše listu
        exit(-1);     // prekid programa
    }

    q->Element = x;
    printf("\r\nSaving list %d.", x);

    q->Next = P->Next;
    P->Next = q;

    n++;
    return n;
}

int Pop(Position P, int n)
{
    Position tmp;

    if (P->Next != NULL)
    {
        tmp = P->Next;
        printf("\r\nDownloading from list %d.", tmp->Element);

        P->Next = tmp->Next;
        free(tmp);
        n--;
    }
    else
    {
        printf("\r\nList is empty.");
    }

    return n;
}

void PrintList(Position P, int n)
{
    printf("\r\n\r\nList contains %d elements:\r\n", n);
    while (n > 0 && P != NULL)
    {
        printf(" %d", P->Element);
        P = P->Next;
        n--;
    }
    printf("\n");
}

void DeleteAll(Position P)
{
    Position temp;
    while (P != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }
}
