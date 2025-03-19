// This program constructs a hash table.

// include statements

// Define {key, value} structure. (Define key and value as char datatype)
typedef struct {
    char key;
    char value;
} KeyValuePair;

// Define the Hash Table structure. [Hint: a hash table is an array of {key, value} pairs]
typedef struct {
    KeyValuePair** items;
    int size;
    int count;
} HashTable;

// Create {key, value} pairs. [Hint: you need to allocate memory for key and value
// and return a pointer to the {key, value} pair]