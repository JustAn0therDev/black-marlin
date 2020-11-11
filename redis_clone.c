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

// Prototypes
Pair GetValue(char* key);
void GetAll();
void SetValue(char* key, char* value);
void DeleteValue(char* key);

Pair pairs[MAXPAIRS - 1];

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

            if (pair.value == NULL) {
                printf("Value not found.\n");
            } else {
                printf("%s\n", pair.value);
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
            printf("OK\n");
        } else if (strcmp(command, "ALL") == 0) {
            GetAll();
        } else {
            printf("Unknown command.\n");
        }

        command = (char*)realloc(command, sizeof(MAXCOMMANDSIZE));

        if (command == NULL) {
            printf("Could not realocate memory.\n");
            exit(1);
        }
    }

    free(command);

    return 0;
}

Pair GetValue(char* key) {
    Pair emptyPair;

    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key != NULL && strcmp(pairs[i].key, key) == 0) {
            return pairs[i];
        } 
    }

    return emptyPair;
}

void GetAll() {
    for (int i = 0; i < MAXPAIRS; i++) { 
        printf("%i [%s]: Value: %s\n", i + 1, pairs[i].key, pairs[i].value);
    }
}

void SetValue(char* key, char* value) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key != NULL && strcmp(pairs[i].key, key) == 0) {
            strcpy(pairs[i].value, value);
            break;
        }

        // Writes to the first spot available in the array.
        if (pairs[i].value == NULL) {
            pairs[i].key = (char*)malloc(sizeof(char) * MAXKEYSIZE);

            if (pairs[i].key == NULL) {
                printf("Could not allocate memory.\n");
                exit(1);
            }

            pairs[i].value = (char*)malloc(sizeof(char) * MAXVALUESIZE);

            if (pairs[i].value == NULL) {
                printf("Could not allocate memory.\n");
                exit(1);
            }

            strcpy(pairs[i].key, key);
            strcpy(pairs[i].value, value);
            break;
        }
    }
}

void DeleteValue(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key != NULL && strcmp(pairs[i].key, key) == 0) {
            // Makes the deleted space available for another item
            // Only freeing the memory in the desired space does not work because of
            // how strings work in C.
            // TODO: Use a cache file and delete a line in it, e.g.: "key|value". In-memory array 
            // is a bad idea because of lost access in a char* (like just losing access to some 
            // allocated memory but not really freeing it).

            memset(pairs[i].key, 0, sizeof(char) * MAXKEYSIZE);
            memset(pairs[i].value, 0, sizeof(char) * MAXVALUESIZE);
            free(pairs[i].key);
            free(pairs[i].value);

            break;
        }
    }
}
