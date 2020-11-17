#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCOMMANDSIZE 6
#define MAXKEYSIZE 100
#define MAXVALUESIZE 10000
#define MAXPAIRS 1000

typedef struct {
    char key[MAXKEYSIZE];
    char value[MAXVALUESIZE];
} Pair;

const char* OK = "OK\n";
const char* NOK = "NOK\n";

// Prototypes
void InitializeEveryFirstByteToZero();
Pair GetValue(char* key);
void SetValue(char* key, char* value);
void DeleteValue(char* key);
void GetAll();
void Exists(char* key);
void Count();
void FlushDB();

Pair pairs[MAXPAIRS - 1];

int main(void) {
    char* command = (char*)malloc(sizeof(MAXCOMMANDSIZE));

    if (command == NULL) {
        printf("ERROR: Could not allocate memory\n");
        exit(1);
    }

    InitializeEveryFirstByteToZero();

    // main loop waiting for user command.
    while (1) {
        printf("Insert a command: ");
        scanf("%s", command); 

        if (strcmp(command, "GET") == 0) {
            char key[MAXKEYSIZE];
            printf("Insert a key: ");
            scanf("%s", key);
            Pair pair; 

            pair = GetValue(key);

            if (pair.value[0] == 0) {
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
        } else if (strcmp(command, "DELETE") == 0) {
            char key[MAXKEYSIZE];
            printf("Insert a key: ");
            scanf("%s", key);

            DeleteValue(key);
        } else if (strcmp(command, "GETALL") == 0) {
            GetAll();
        } else if (strcmp(command, "COUNT") == 0) {
            Count();
        } else if (strcmp(command, "EXISTS") == 0) {
            char key[MAXKEYSIZE];
            printf("Insert a key: ");
            scanf("%s", key);
            Exists(key);
        } else if (strcmp(command, "FLUSH") == 0) {
            Flush();
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

void InitializeEveryFirstByteToZero() {
    for (int i = 0; i < MAXPAIRS; i++) {
        pairs[i].key[0] = 0;
        pairs[i].value[0] = 0;
    }
}

Pair GetValue(char* key) {
    Pair emptyPair;
    for (int i = 0; i < MAXPAIRS; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            return pairs[i];
        } 
    }
    return emptyPair;
}

void SetValue(char* key, char* value) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            strcpy(pairs[i].value, value);
            break;
        }

        // Writes to the first spot available in the array.
        if (pairs[i].value[0] == 0) {
            strcpy(pairs[i].key, key);
            strcpy(pairs[i].value, value);
            break;
        }
    }
}

void DeleteValue(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            memset(pairs[i].key, 0, sizeof(char) * MAXKEYSIZE);
            memset(pairs[i].value, 0, sizeof(char) * MAXVALUESIZE);
            printf("%s", OK);
            return;
        }
    }

    printf("No key found.\n");
}

void GetAll() {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key[0] != 0) {
            printf("[%s]: %s\n", pairs[i].key, pairs[i].value);
        }
    }
}

void Exists(char *key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            printf("%s", OK);
            return;
        }
    }
    printf("%s", NOK);
}

void Count() {
    int counter = 0;
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key[0] != 0) {
            counter++;
        }
    }
    printf("%i\n", counter);
}

void Flush() {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i].key[0] != 0) {
            memset(pairs[i].key, 0, sizeof(char) * MAXKEYSIZE);
            memset(pairs[i].value, 0, sizeof(char) * MAXVALUESIZE);
        }
    }
}