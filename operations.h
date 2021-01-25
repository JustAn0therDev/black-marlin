#include "constants.h"

typedef struct {
    char* key;
    char* value;
} Pair;

void AllocateMemoryForPair(Pair** pairInArray);
void GetValue(char* key);
void SetValue(char* key, char* value);
void DeleteValue(char* key);
void GetAll(void);
void Exists(char* key);
void Count(void);
void Flush(void);
void Strlen(char* key);
