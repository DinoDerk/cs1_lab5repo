#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int i = 0;

	// node called current that is equal to the start of the linked list
	node *current = head;

	// loops current till end of list
	while (current != NULL)
	{
		i++;

		// points current to the next node
		current = current->next;
	}

    // returns length
	return (i);
}

// passes the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// function call to get length of list
	int len = length(head);

	// allocates memory for the entire string
	char *c = malloc((len + 1) * sizeof(char));

	int i = 0;

	// loops until list is at end
	while(head != NULL)
	{
		// sets each spot in string equal to the letter associated at the node
		c[i] = head->letter;

		// points head to next node
		head = head->next;

		i++;
	}

	//sets the last index in string to be the null terminator
	c[len] = '\0';

	// returns our created string
	return (c);
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// creates a new node with allocated memory
	node *newNode = (node *) malloc(sizeof(node));

	// has our new node to have the letters from string c
	newNode->letter = c;

	// points our new node to null
	newNode->next = NULL;

	//if head is null, make head equal to our new node
	if (*pHead == NULL)
	{
        // sets phead to equal the new node
	    *pHead = newNode;
	}
	else
	{
		//create a node for our temp storage of phead
		node *temp = (node *) malloc(sizeof(node));
		temp = *pHead;

		// when linked list is longer than two nodes, this while occurs
		while(temp->next != NULL)
		{
			// goes till end of list
			temp = temp->next;
		}
		
		// links temps end to our newly created node
		temp->next = newNode;
	}



}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	// creates a current node to traverse list
	struct node *current = *pHead;

	// creates a next node to store temp information
	struct node *next;

	// loops until end of list
	while (current->next != NULL)
	{
		// sets next to current next
		next = current->next;

		// frees current node
		free(current);

		// sets current to current next from node next
		current = next;
	}

	// sets original linked list to null
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}