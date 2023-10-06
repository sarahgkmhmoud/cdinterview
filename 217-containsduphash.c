#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct chash_node_t{
    int key;
    int value;
    struct chash_node_t *next;
} node;
typedef struct chash_table_t{
    node **array;
    int size;
} hh;
hh *creat_hashtable(int size);
node *creat_node(int key, int value);
int chash_table_set(hh *ht, int key, int value);
bool containsDuplicate(int* nums, int numsSize);
/**
 *
 * 
 *
*/
hh *creat_hashtable(int size){
hh *hash = malloc(sizeof(hh));
if (hash == NULL)
return NULL;
hash->size = size;
hash->array = malloc(sizeof(node *) * size);
unsigned long int key_index(long int key, unsigned long int size);
if(hash->array == NULL)
{
    free(hash);
    return NULL;
}
for (int i = 0; i < size; i++)
    {
        hash->array[i] = NULL;
    }
return (hash);
}
/**
 * 
 * 
 * 
 * 
*/
node *creat_node(int key, int value){
    node *newnode;
    newnode = malloc(sizeof(node));
    if (newnode == NULL)
    return NULL;

    newnode->key = key;
    newnode->value = value;


    return newnode;
}
/**
 * 
 * 
 * 
*/
unsigned long int key_index(long int key, unsigned long int size)
{
    unsigned long int index = key % size;

    return index;
}
/**
 * 
 * 
 * 
*/
int chash_table_set(hh *ht, int key, int value){
unsigned long int index;
node *ptr = NULL, *current;
if (ht == NULL)
exit(EXIT_FAILURE);
index = key_index(key, ht->size);
ptr = ht->array[index];
while (ptr){
    if (ptr->key == key && ptr->value == value)
    {
        return 0;
    }
    ptr = ptr->next;
}
current = creat_node(key, value);
 if (current == NULL)
        exit(EXIT_FAILURE);
        current->next = ht->array[index];
        ht->array[index] = current;
return 1;
}
/**
 * 
 * 
 * 
 * 
*/
bool containsDuplicate(int* nums, int numsSize){
int i, j;
hh *table = creat_hashtable(numsSize);
for (i = 0; i < numsSize; i++){
    if (chash_table_set(table,nums[i],nums[i]) == 0)
    return true; 
}
return false;
}

int main() {
    int nums[] = {1,3,4,2,10,200,1200,300,250,390}; // Example input array
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    if (containsDuplicate(nums, numsSize)) {
        printf("Duplicate found!\n");
    } else {
        printf("No duplicates found.\n");
    }

    return 0;
}
