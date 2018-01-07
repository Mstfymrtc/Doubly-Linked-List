/* This source has been formatted by an unregistered SourceFormatX */
/* If you want to remove this info, please register this shareware */
/* Please visit http://www.textrush.com to get more information    */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define STRLENGTH 20
typedef struct doubly_list
{

	int info;
	char message[STRLENGTH];
	struct doubly_list *previous;
	struct doubly_list *next;

} DLIST;

DLIST *first = NULL;
DLIST *last = NULL;
int count = 0;
void insert(char toAdd[])
{
	DLIST *newNode = (DLIST*)malloc(sizeof(DLIST));
	int j;
	for (j = 0; j < STRLENGTH; j++)
		newNode->message[j] = toAdd[j];
	if (first == NULL)
		// if the list is empty
	{
		first = newNode;
		last = newNode;
		first->previous = NULL;
		last->next = NULL;
		newNode->info = count;

	}
	else
		//sona ekleme
	{
		last->next = newNode;
		newNode->previous = last;
		newNode->next = NULL;
		last = newNode;
		count++;
		last->info = count;
	}
}


int display()
{
	DLIST *iter;
	iter = first;
	if (iter == NULL || first->next == NULL)
	{
		printf("List is empty\n");
		return  -1;
	}
	else
	{

		printf("INDEX    DATA\n");
		printf("============================\n");

		while (iter)

		{
			printf("%d        %s\n", iter->info, iter->message);

			printf("============================\n");
			iter = iter->next;

		}

		return 0;
	}
}


DLIST *search(int key)
{

	DLIST *iter;
	iter = first;
	while (iter)
	{
		if (iter->info == key)
		{
			printf("Found at %d", iter->info);
			return iter;
		}
		iter = iter->next;
	}

	return NULL;
}

void deleteAll()
{
	DLIST *deleteIter = first;
	DLIST *deleteNext;
	while (deleteIter)
	{

		deleteNext = deleteIter->next;
		free(deleteIter);

		deleteIter = deleteNext;
	}
}

void deleteSingle(int key)
{
	DLIST *nodeToBeDeleted;

	nodeToBeDeleted = search(key);



	if (nodeToBeDeleted != NULL)
	{


		if (nodeToBeDeleted == first)
			//Ýlk eleman ise
		{
			if (nodeToBeDeleted->next == NULL)
				//liste tek elemanlýysa
			{
				nodeToBeDeleted = NULL;
				first = NULL;
				last = NULL;
			}
			else
			{
				//liste tek elemanlý deðilse
				first = nodeToBeDeleted->next;
				first->previous = NULL;

			}
		}

		else

		{

			if (nodeToBeDeleted == last && nodeToBeDeleted->previous != NULL)
				//son eleman ise
			{
				last = nodeToBeDeleted->previous;
				last->next = NULL;


			}
			else
			{
				//middle ise
				nodeToBeDeleted->previous->next = nodeToBeDeleted->next;
				nodeToBeDeleted->next->previous = nodeToBeDeleted->previous;
			}
		}
		free(nodeToBeDeleted);
		//return nodeToBeDeleted;




	}
	printf("Couldn't find node to be deleted\n");
	//return nodeToBeDeleted;
}

void store()
{


	FILE *fp = NULL;
	DLIST *iter;
	fp = fopen("list.txt", "w");
	iter = first;

	while (iter)
	{
		//fwrite(iter, sizeof(DLIST) - 2 * sizeof(iter), 1, fp);
		fprintf(fp, "%d %s\n", iter->info, iter->message);
		iter = iter->next;
	}

	fclose(fp);
	printf("List was stored successfully.\n");

}

int main(void)
{
	char dataInput[STRLENGTH];
	while (1)
	{
		system("cls");
		int choice, key;


		printf(
			"Make your choose\n----------------\n1:INSERT\n2:DISPLAY\n3:SEARCH\n4:DELETE\n5:CLEAR LIST\n6:WRITE TO FILE\n7:EXIT\n");
		scanf("%d", &choice);
		system("cls");

		switch (choice)
		{
		case 1:
			printf("Enter your message:\n");
			//  scanf("%s", dataInput);
			getchar();
			gets(dataInput);


			insert(dataInput);

			break;

		case 2:


			display();

			system("PAUSE");
			break;

		case 3:
			printf("Enter index of the data that you want to find\n");
			scanf("%d", &key);
			DLIST *found = search(key);

			printf("%s", found->message);
			system("PAUSE");
		case 4:
			printf("Enter index of the data that you want to delete\n");
			scanf("%d", &key);
			deleteSingle(key);
			break;
		case 5:

			deleteAll();

			break;

		case 6:
			store();
			system("PAUSE");
			break;


		case 7:
			exit(0);

		}

	}


}