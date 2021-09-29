#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_STRING 30
#define NUMBER_OF_PLAYERS 3

typedef struct player {
	char * name;
	int points;
} player;

void printArray(
	const void * baseOfArray,
	size_t sizeOfItem,
	size_t length,
	void (*printFunction)(const void * arrayItem)
) {
	for (size_t i = 0; i < length; i++) {
		(*printFunction)(baseOfArray + (sizeOfItem * i));
	}
}

void parseSlashN(char * string) {
	int length = strlen(string);

	for (int i = 0; i < length; i++) {
		if(string[i] == '\n') string[i] = '\0';
	}
}

player generateNewPlayer () {
	player newPlayer;
	
	newPlayer.name = (char *) malloc(sizeof(char) * SIZE_OF_STRING);

	printf("Insert player's name:\n");

	fgets(newPlayer.name, SIZE_OF_STRING - 1, stdin);	

	parseSlashN(newPlayer.name);

	printf("Insert player's points:\n");

	scanf("%d", &(newPlayer.points));

	getchar();

	return newPlayer;
}

void printPlayer(const void * data) {
	player * playerData = (player *) data;

	printf("Player's name: %s\n", playerData->name);	
	printf("Player's points: %d\n", playerData->points);
}

void freeAllPlayersMemory(player * players, int numberOfPlayers) {
	for (int i = 0; i < numberOfPlayers; i++) {
		free(players[i].name);
	}

	free(players);
}

int main () {
	player * players = (player *) malloc(sizeof(player) * NUMBER_OF_PLAYERS);

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		players[i] = generateNewPlayer();
	}

	printf("\n");

	printArray((void *) players, sizeof(player), NUMBER_OF_PLAYERS, printPlayer);

	freeAllPlayersMemory(players, NUMBER_OF_PLAYERS);

	return 0;
}

