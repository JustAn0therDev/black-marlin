#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "constants.h"

void GetValue(Pair** pairArray, char** key) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, *key) == 0) {
      printf("%s\n", (*pairArray+i)->value);
      return;
    }
  }

  printf("%s", NOK);
}

void SetValue(Pair** pairArray, char** key, char** value) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, *key) == 0) {
      free((*pairArray+i)->value);

      (*pairArray+i)->value = malloc(sizeof(char) * MAXVALUESIZE);
      strcpy((*pairArray+i)->value, *value);

      break;
    } else if (strcmp((*pairArray+i)->key, EMPTYSTRING) == 0) {
      free((*pairArray+i)->key);
      free((*pairArray+i)->value);

      (*pairArray+i)->key   = malloc(sizeof(char) * MAXKEYSIZE);
      (*pairArray+i)->value = malloc(sizeof(char) * MAXVALUESIZE);

      strcpy((*pairArray+i)->key, *key);
      strcpy((*pairArray+i)->value, *value);

      break;
    }
  }
}

void DeleteValue(Pair** pairArray, char** key) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, *key) == 0) {
      free((*pairArray+i)->key);
      free((*pairArray+i)->value);

      (*pairArray+i)->key   = malloc(sizeof(char) * 2);
      (*pairArray+i)->value = malloc(sizeof(char) * 2);

      strcpy((*pairArray+i)->key, EMPTYSTRING);
      strcpy((*pairArray+i)->value, EMPTYSTRING);

      printf("%s", OK);
      return;
    }
  }

  printf("%s", NOK);
}

void GetAll(Pair** pairArray) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, EMPTYSTRING) != 0) {
      printf("[%s]: %s\n", (*pairArray+i)->key, (*pairArray+i)->value);
    }
  }
}

void Exists(Pair** pairArray, char** key) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, *key) == 0) {
      printf("%s", OK);
      return;
    }
  }

  printf("%s", NOK);
}

void Count(Pair** pairArray) {
  int numberOfAllocatedItemsInPairArray = 0;
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, EMPTYSTRING) != 0) {
      numberOfAllocatedItemsInPairArray++;
    }
  }

  printf("%i\n", numberOfAllocatedItemsInPairArray);
  printf("%s", OK);
}

void Flush(Pair** pairArray) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp((*pairArray+i)->key, EMPTYSTRING) != 0) {
      free((*pairArray+i)->key);
      free((*pairArray+i)->value);

      (*pairArray+i)->key   = malloc(sizeof(char) * 2);
      (*pairArray+i)->value = malloc(sizeof(char) * 2);

      strcpy((*pairArray+i)->key, EMPTYSTRING);
      strcpy((*pairArray+i)->value, EMPTYSTRING);
    }
  }

  printf("%s", OK);
}

void Strlen(Pair** pairArray, char** key) {
  for (int i = 0; i < MAXPAIRS; i++) {
    if (strcmp(*key, (*pairArray+i)->key) == 0) {
      printf("%lu\n", strlen((*pairArray+i)->value));
      printf("%s", OK);
      return;
    }
  }

  printf("%s", NOK);
}
