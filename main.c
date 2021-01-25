#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"
#include "operations.h"

Pair* pairs[MAXPAIRS];

void main(void) {
    char* command;
    char* key;

    while (1) {
        command = malloc(sizeof(char) * MAXCOMMANDSIZE); 
        key = malloc(sizeof(char) * MAXKEYSIZE);

        printf("Insert a command: ");
        scanf("%s", command); 

        if (strcmp(command, "GET") == 0) {
            printf("Insert a key: ");
            scanf("%s", key);
            GetValue(key);
        } else if (strcmp(command, "SET") == 0) {
            printf("Insert a key: ");
            scanf("%s", key);

            printf("Insert a value: ");
            char* value = malloc(sizeof(char) * MAXVALUESIZE);
            scanf("%s", value);

            SetValue(key, value);
            free(value);
        } else if (strcmp(command, "DELETE") == 0) {
            printf("Insert a key: ");
            scanf("%s", key);
            DeleteValue(key);
        } else if (strcmp(command, "GETALL") == 0) {
            GetAll();
        } else if (strcmp(command, "COUNT") == 0) {
            Count();
        } else if (strcmp(command, "EXISTS") == 0) {
            printf("Insert a key: ");
            scanf("%s", key);
            Exists(key);
        } else if (strcmp(command, "FLUSH") == 0) {
            Flush();
        } else if (strcmp(command, "STRLEN") == 0) { 
            printf("Insert a key: ");
            scanf("%s", key);
            Strlen(key);
        } else if (strcmp(command, "QUIT") == 0) {
            break;
        } else {
            printf("Unknown command.\n");
        }

        free(command);
        free(key);
    }

    free(command);
    free(key);
}

void GetValue(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL && strcmp(pairs[i]->key, key) == 0) {
            printf("%s\n", pairs[i]->value);
            return;
        }
    }
    
    printf("%s", NOK);
}

void SetValue(char* key, char* value) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL && strcmp(pairs[i]->key, key) == 0) {
            free(pairs[i]->value);
            pairs[i]->value = malloc(sizeof(char) * MAXVALUESIZE);
            strcpy(pairs[i]->value, value);
            break;
        } else if (pairs[i] == NULL) {
            pairs[i] = malloc(sizeof(Pair));
            pairs[i]->key = malloc(sizeof(char) * MAXKEYSIZE);
            pairs[i]->value = malloc(sizeof(char) * MAXVALUESIZE);

            strcpy(pairs[i]->key, key);
            strcpy(pairs[i]->value, value);
            break;
        }
    }
}

void DeleteValue(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL && strcmp(pairs[i]->key, key) == 0) {
            free(pairs[i]->key);
            free(pairs[i]->value);
            free(pairs[i]);

            // Since a "freed pointer" can be pointing to anything, we set it to point to NULL
            pairs[i] = NULL;

            printf("%s", OK);
            return;
        }
    }
    
    printf("%s", NOK);
}

void GetAll() {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL) {
            printf("[%s]: %s\n", pairs[i]->key, pairs[i]->value);
        }  
    }
}

void Exists(char *key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL && strcmp(pairs[i]->key, key) == 0) {
            printf("%s", OK);
            return;
        }
    }
    
    printf("%s", NOK);
}

void Count() {
    int numberOfAllocatedItemsInPairArray = 0;
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL) {
            numberOfAllocatedItemsInPairArray++;
        }
    }

    printf("%i\n", numberOfAllocatedItemsInPairArray);
    printf("%s", OK);
}

void Flush() {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL) {
            free(pairs[i]->key);
            free(pairs[i]->value);
            free(pairs[i]);

            // Since a "freed pointer" can be pointing to anything, we set it to point to NULL
            pairs[i] = NULL;
        }
    }
    
    printf("%s", OK);
}

void Strlen(char* key) {
    for (int i = 0; i < MAXPAIRS; i++) {
        if (pairs[i] != NULL && strcmp(key, pairs[i]->key) == 0) {
            printf("%lu\n", strlen(pairs[i]->value));
            printf("%s", OK);
            return;
        }
    }
    
    printf("%s", NOK);
}
