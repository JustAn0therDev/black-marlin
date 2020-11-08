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

void SetValue(char* key, char* value) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key != NULL && strcmp(pairs[i].key, key) == 0) {
            strcpy(pairs[i].value, value);
            break;
        }

        // Writes to the first spot available in the memory array.
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
        }
    }
}

void DeleteValue(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key != NULL && strcmp(pairs[i].key, key) == 0) {
            // Makes the deleted space available for another item again
            pairs[i].key = (char*)realloc(pairs[i].key, sizeof(char) * MAXKEYSIZE);
            pairs[i].value = (char*)realloc(pairs[i].value, sizeof(char) * MAXVALUESIZE);
            break;
        }
    }
}
