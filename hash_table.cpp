/*
 Student Name: Praneeth Eddu    
 Date: 4/4/18

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* they are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    //Creating a HashTableEntry instance
    HashTableEntry* newTableEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry));

    
    if (!newTableEntry) {
        return newTableEntry;
    }
    //Initialize the HashTableEntry struct
    newTableEntry->key = key;
    newTableEntry->value = value;
    newTableEntry->next = NULL;

    //return this hash table entry 
    return newTableEntry;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/

static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
    //Initialize
    HashTableEntry* myEntry;
    unsigned int keyIndex;
    keyIndex = hashTable->hash(key); //returns the hashTable's key
    myEntry = hashTable->buckets[keyIndex]; //myEntry pointing to the bucket location
    //Walk the list to match the key and return the pointer ot hashTableEntry
    while (myEntry) {
        if (myEntry->key == key) {
            return myEntry;
        }
        myEntry = myEntry->next;
    }
    //if key doesn't exists, 
    return NULL; //NULL
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets are empty, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
    HashTableEntry* myEntry;
    unsigned int numBuckets;
    numBuckets = hashTable->num_buckets; //returns the number of buckets in hashTable
    unsigned int i;
    /* Goes through every bucket and first destroys the HashTableEntry's values,
    the pointer to the bucket, the bucket itself */ 
    for (i = 0; i < numBuckets; i++) {
        while (hashTable->buckets[i]) {
            myEntry = hashTable->buckets[i];
            hashTable->buckets[i] = hashTable->buckets[i]->next;
            free(myEntry->value);
            free(myEntry);
        }
    free(hashTable->buckets[i]);
    }
    free(hashTable); //destroys the entire hashTable
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
    //new HashTable entry
    HashTableEntry* hashEntry;
    unsigned int keyIndex;
    keyIndex = hashTable->hash(key); //returns the hashTable's key
    void* temp; //temp can hold any type of data
    //Using the key given, checks to see if the key matches and inserts the value accordingly
    if (hashEntry = findItem(hashTable, key)) {
        temp = hashEntry->value;
        if (temp == value) {
            return NULL; 
        }
        hashEntry->value = value;
        return temp; //returns the value overwirtitten
    }
    hashEntry = createHashTableEntry(key,value);
    if (!hashEntry) {
        return hashEntry; //if no HashEntries are found, returns the pointer to the hashEntry
    }
    hashEntry->next = hashTable->buckets[keyIndex];
    hashTable->buckets[keyIndex] = hashEntry;
    return NULL; //if key not present, return NULL
} 

void* getItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* hashEntry;
    hashEntry = findItem(hashTable, key);
    //if key is doesnt exist, return null
    if (hashEntry == NULL) {
        return NULL;
    }
    return hashEntry->value; //walk the list
}

void* removeItem(HashTable* hashTable, unsigned int key) {
    //new HashTable entry 
    HashTableEntry* myHash;
    unsigned int keyIndex;
    keyIndex = hashTable->hash(key); //returns the hashTable's key
    myHash = hashTable->buckets[keyIndex]; //myHash points to bucket Location
    if (!(hashTable->buckets[keyIndex])) {
        return NULL; //if key not present
    }
    //Temporaries
    HashTableEntry* tempVal;
    HashTableEntry* temp;
    //Check to see if the key matches the first node
    if (hashTable->buckets[keyIndex]->key == key) {
        temp = hashTable->buckets[keyIndex]; //temp points to the node with the correct key present
        hashTable->buckets[keyIndex] = hashTable->buckets[keyIndex]->next;
        tempVal->value = temp->value; //value is stored in tempVal
        free(temp); //deallocated from the heap
        return tempVal; //return value
    }
    myHash = hashTable->buckets[keyIndex];
    while (myHash->next) {
        if (myHash->next->key == key) {
            temp = myHash; //temp points to the hashTable node
            myHash = myHash->next->next;
            tempVal->value = temp->next->value; //value is stored in tempVal
            free(temp->next); //deallocated from the heap
            return tempVal; //return value
        }
        myHash = myHash->next; //walk the list
    }
    return NULL;
}

void deleteItem(HashTable* hashTable, unsigned int key) {
    //new hashTable entry
    HashTableEntry* myHash;
    unsigned int keyIndex;
    keyIndex = hashTable->hash(key);
    myHash = hashTable->buckets[keyIndex];
    HashTableEntry* temp;
    //if the first entry matches the key, deletes the value and the hashTable entry
    if (myHash->key == key) {
        temp = myHash;
        hashTable->buckets[keyIndex] = myHash->next; //buckets pointing to the next entries buckets
        free(temp->value); //value deallocated from the heap
        free(temp);  //hashTableEntry deallocated from the heap
        myHash = NULL;
    }
    //Using the key, deletes the value and the hashTable entry
    while (myHash->next) {
        if (myHash->next->key == key) {
            temp = myHash->next; //temp pointing the hash Table entry
            myHash = myHash->next->next;
            hashTable->buckets[keyIndex]->next = temp->next; //buckets pointing to the next entries buckets
            free(temp->value); //value deallocated from the heap
            free(temp); //hashTableEntry deallocated from the heap
        }
        myHash = myHash->next; //walk the list
    }
}