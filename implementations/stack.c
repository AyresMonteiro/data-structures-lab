#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_STRING 30

typedef struct node {
	char * message;
	struct node * previousNode;
} node;

char * readString(int size, char * messageToBePrinted) {
	char * newString = (char *) malloc(sizeof(char) * (size + 1));
	newString[size] = '\0';

	if(messageToBePrinted != NULL) printf(messageToBePrinted);

	fgets(newString, size, stdin);

	return newString;
}

node * generateNewNode () {
	node * newNode = (node *) malloc(sizeof(node));

	newNode->message = readString(SIZE_OF_STRING, "Enter node's message\n");
	newNode->previousNode = NULL;

	return newNode;
}

node * insertNodeOnStack (node * tail) {
	node * newNode = generateNewNode();

	newNode->previousNode = tail;

	return newNode;
}

void freeNode(node * nodeToBeFreed) {
	free(nodeToBeFreed->message);
	free(nodeToBeFreed);
}

void freeAllNodes (node * tail) {
	node * previous = tail->previousNode;

	freeNode(tail);

	if(previous != NULL) {
		freeAllNodes(previous);
	}
}

node * removeNodeFromStack (node * tail) {
	node * newTail = tail->previousNode;

	freeNode(tail);

	return newTail;
}

void printAllMessages (node * tail) {
	printf("%s", tail->message);

	if(tail->previousNode != NULL) {
		printAllMessages(tail->previousNode);
	}
}

int main () {
	node * stack = generateNewNode();

	printf("Before insert:\n");
	printAllMessages(stack);
	putchar('\n');

	stack = insertNodeOnStack(stack);

	printf("After insert:\n");
	printAllMessages(stack);
	putchar('\n');

	stack = removeNodeFromStack(stack);

	printf("After remove:\n");
	printAllMessages(stack);
	putchar('\n');

	freeAllNodes(stack);

	return 0;
}

