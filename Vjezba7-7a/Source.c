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
	int Priority;
};

int GetValueFromRange(int, int);
int Push(Position, int, int);
int Pop(Position, int);
void PrintList(Position, int);
void DeleteAll(Position);
int PushPriorityQueue(Position, int, int);
int PopPriorityQueue(Position );
void PrintPriorityQueue(Position);




int main()
{
	struct _Node S;
	char choice = 0;
	int n = 0;
	int max = 0;

	struct _Node Q;
	Q.Next = NULL;

	S.Next = NULL;
	S.Element = -1;

	while (max < 5)
	{
		printf("\nInput stack size <5-20> : ");
		scanf_s(" %d", &max);
		if (max < 5 || max > 20)
		{
			max = 0;
			printf("\nWrong input!");
		}
	}

	S.Next = NULL;
	srand((unsigned)time(NULL));

	while (choice != 'K' && choice != 'k')
	{
		
		printf("\n\t\t1.\tStack push");
		printf("\n\t\t2.\tStack pop");
		printf("\n\t\t3.\tPriority queue push");
		printf("\n\t\t4.\tPriority queue pop");
		printf("\n\t\tk.\tEnd of program");
		printf("\nChoice : \n");
		scanf_s(" %c", &choice, 1);

		if (scanf_s(" %c", &choice, 1) != 1)
		{
			printf("\nInput error!\n");
			DeleteAll(&S);
			DeleteAll(&Q);   
			return -1;
		}


		switch (choice)
		{
		case '1':
    if (n < max)
    {
        int tmp = Push(&S, GetValueFromRange(0, 10000), n);
        if (tmp == -1)  
        {
            printf("\nMemory allocation error!\n");
            DeleteAll(&S);
            DeleteAll(&Q);
            return -1;   
        }
        n = tmp;
    }
    else
        printf("\nStack is full!\n");
    PrintList(S.Next, n);
    break;
		
		case '3':
		{
			int value = GetValueFromRange(10, 100);
			int priority = GetValueFromRange(1, 6);

			if (PushPriorityQueue(&Q, value, priority) == -1)
			{
				printf("\nMemory allocation error!\n");
				DeleteAll(&S);
				DeleteAll(&Q);
				return;
			}

			PrintPriorityQueue(Q.Next);
			break;
		}

		case '4':
			PopPriorityQueue(&Q);
			PrintPriorityQueue(Q.Next);
			break;

		case 'k':
			printf("\n");
			break;
		default:
			printf("\nTry again.\n");
		}
	}

DeleteAll(&S);
DeleteAll(&Q);   
return 0;
}

int GetValueFromRange(int min, int max)
{
	int x = 0;

	x = rand() % (max - min) + min;

	return x;
}

int Push(Position P, int x, int n)
{
	static Position last;
	Position q;

	q = (Position)malloc(sizeof(struct _Node));
	if (q)
	{
		if (P->Next == NULL)
			last = q;

		q->Element = x;

		printf("\nSaving list %d.", x);
		q->Next = P->Next;
		P->Next = q;

		last->Next = q;
		n++;
	}
	return n;
}

int Pop(Position P, int n)
{
	static Position last = NULL;
	Position tmp;

	if (P->Next != NULL)
	{

		tmp = P->Next;

		printf("\nDownloading from list %d.", tmp->Element);

		P->Next = tmp->Next;

		if (last == NULL && n > 1)
		{
			while (P->Next != tmp)
				P = P->Next;
			last = P;
		}

		last->Next = tmp->Next;

		free(tmp);
		n--;
		if (n == 0)
			last = NULL;
	}
	else
		printf("\nList is empty.");

	return n;
}

int PushPriorityQueue(Position P, int value, int priority)
{
	Position q = NULL;
	Position current = NULL;

	q = (Position)malloc(sizeof(struct _Node));
	if (q == NULL)
		return -1;   

	q->Element = value;
	q->Priority = priority;
	q->Next = NULL;

	
	if (P->Next == NULL || P->Next->Priority < priority)
	{
		q->Next = P->Next;
		P->Next = q;
		return 0;
	}

	current = P->Next;

	
	while (current->Next != NULL &&
		current->Next->Priority >= priority)
	{
		current = current->Next;
	}

	q->Next = current->Next;
	current->Next = q;

	return 0;
}


int PopPriorityQueue(Position P)
{
	Position tmp = NULL;

	if (P->Next == NULL)
	{
		printf("\nPriority queue is empty.\n");
		return 0;
	}

	tmp = P->Next;
	printf("\nRemoved: %d (priority %d)", tmp->Element, tmp->Priority);

	P->Next = tmp->Next;
	free(tmp);

	return 0;
}

void PrintPriorityQueue(Position P)
{
	if (P == NULL)
	{
		printf("\nQueue is empty.\n");
		return;
	}

	printf("\nPriority queue:\n");
	while (P != NULL)
	{
		printf(" %d(p=%d)", P->Element, P->Priority);
		P = P->Next;
	}
	printf("\n");
}


void PrintList(Position P, int n)
{
	printf("\nList contains %d elements:\n", n);
	while (n > 0)
	{
		printf(" %d", P->Element);
		P = P->Next;
		n--;
	}
}

void DeleteAll(Position P)
{
	Position tmp;
	while (P->Next != NULL)
	{
		tmp = P->Next;
		P->Next = tmp->Next;
		free(tmp);
	}
}