#include "constants.h"

typedef struct {
    char key[MAXKEYSIZE];
    char value[MAXVALUESIZE];
} Pair;

void InitializeEveryFirstByteToZero();
Pair GetValue(char* key);
void SetValue(char* key, char* value);
void DeleteValue(char* key);
void GetAll();
void Exists(char* key);
void Count();
void Flush();
void Strlen(char* key);