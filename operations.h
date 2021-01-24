#include "constants.h"

typedef struct {
    char* key;
    char* value;
} Pair;

void GetValue(char* key);
void SetValue(char* key, char* value);
void DeleteValue(char* key);
void GetAll();
void Exists(char* key);
void Count();
void Flush();
void Strlen(char* key);