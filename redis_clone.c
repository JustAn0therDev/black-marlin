#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCOMMANDSIZE 3
#define MAXKEYSIZE 100
#define MAXVALUESIZE 10000
#define MAXPAIRS 100

typedef struct {
    char* key;
    char* value;
} Pair;

int pairsLength = 0;

// Prototypes
Pair GetValue(char* key);
void SetValue(char* key, char* value);
void DeleteValue(char* key);

Pair pairs[MAXPAIRS];

int main(void) {
    char* command = (char*)malloc(sizeof(MAXCOMMANDSIZE));

    if (command == NULL) {
        printf("ERROR: Could not allocate memory\n");
        exit(1);
    }

    // main loop waiting for user command.
    while (1) {
        scanf("%s", command); 

        if (strcmp(command, "GET") == 0) {
            char key[MAXKEYSIZE];
            printf("Insert a key: ");
            scanf("%s", key);
            Pair pair; 

            pair = GetValue(key);

            if (strcmp(pair.key, key) != 0) {
                printf("Could not get value.");
            } else {
                printf("Key: %s, Value: %s\n", pair.key, pair.value);
            }

        } else if (strcmp(command, "SET") == 0) {
            char key[MAXKEYSIZE];
            char value[MAXVALUESIZE];

            printf("Insert a key: ");
            scanf("%s", key);

            printf("Insert a value: ");
            scanf("%s", value);

            SetValue(key, value);
        } else if (strcmp(command, "DEL") == 0) {
            char key[MAXKEYSIZE];
            printf("Insert a key: ");
            scanf("%s", key);

            DeleteValue(key);
        } else {
            printf("Unknown command.\n");
        }

        // command = (char*)realloc(command, sizeof(MAXCOMMANDSIZE));
    }

    free(command);

    return 0;
}

Pair GetValue(char* key) {
    Pair emptyPair;

    for (int i = 0; i < pairsLength; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            return pairs[i];
        } 
    }

    return emptyPair;
}

void SetValue(char* key, char* value) {
    int foundKey = 0;

    for (int i = 0; i < pairsLength; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            strcpy(pairs[i].value, value);
            foundKey = 1;
            break;
        }
    }

    if (foundKey == 0) {
        if (pairsLength > 0) {
            strcpy(pairs[pairsLength - 1].key, key);
            strcpy(pairs[pairsLength - 1].value, value);
        } else {
            pairs[0].key = (char*)malloc(sizeof(char) * MAXKEYSIZE);
            strcpy(pairs[0].key, key);
            
            pairs[0].value = (char*)malloc(sizeof(char) * MAXVALUESIZE);
            strcpy(pairs[0].value, value);
        }
        pairsLength++;
    }
}

void DeleteValue(char* key) {
    for (int i = 0; i < pairsLength; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            strcpy(pairs[i].key, " ");
            strcpy(pairs[i].value, " ");
            pairsLength--;
            break;
        }
    }
}
