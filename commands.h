typedef struct {
    char* key;
    char* value;
} Pair;

void GetValue(Pair** pairArray, char** key);
void SetValue(Pair** pairArray, char** key, char** value);
void DeleteValue(Pair** pairArray, char** key);
void GetAll(Pair** pairArray);
void Exists(Pair** pairArray, char** key);
void Count(Pair** pairArray);
void Flush(Pair** pairArray);
void Strlen(Pair** pairArray, char** key);
