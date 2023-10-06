#include <stdio.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct data_t{
    int key;
    int index;
    struct data_t *next;
} data;
typedef struct hash_table{
    data **array;
    int size;
} table;
table *creat_table (int size){
    table *ht = malloc (sizeof(table));
    if (ht == NULL)
    return NULL;

    ht->array = malloc (sizeof(data *) * size);
    if (ht->array == NULL){
    free(ht);
    return NULL;
    }

    ht->size = size;
    for (int i = 0; i < size; i++)
    ht->array[i] = NULL;

    return ht;
}
/**
 * hash_djb2 - implementation of the djb2 algorithm
 * @str: string used to generate hash value
 *
 * Return: hash value
 */
unsigned long int hash_djb2(const unsigned int key)
{
	unsigned long int hash;

	hash = 5381;
	
		hash = ((hash << 5) + hash) + key; /* hash * 33 + c */
	return (hash);
}
unsigned int index_key(table *ht, int key){
    unsigned int index;
  index =  hash_djb2(abs(key)) % ht->size;
    return index;
}

 data* find_key(table* ht, int key) {
    unsigned int index = index_key(ht, key);
    data* current = ht->array[index];

    while (current != NULL) {
        if (current->key == key)
            return current;
        current = current->next;
    }

    return NULL;
}


void set_table(table *ht, int key, int value){
    unsigned int index = index_key(ht, key);
    data *current = ht->array[index];
    while (current){
        if (current->key == key){
            current->index = value;
            return;
        }
        current = current->next;
    }
        data *new= malloc(sizeof(data));
        if (new == NULL) {
            return;
        }
   new->key = key;
    new->index = value;
    new->next = ht->array[index];
    ht->array[index] = new;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
  
    int i;
    int diff;
    int *newArray =(int *)malloc(2 * sizeof(int));
                if (newArray == NULL) 
                return NULL;
    table *ht = creat_table(numsSize);
for (i = 0; i < numsSize; i++)
{
diff = target - nums[i];
data *found = find_key(ht, diff); 
if (found != NULL){
            newArray[0] = i;
            newArray[1] = found->index;
            *returnSize = 2;
                return newArray;
}
else   
set_table(ht, nums[i], i);
}
*returnSize = 0;
        return NULL;
}



int main() {
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1;
    int* result1 = twoSum(nums1, sizeof(nums1) / sizeof(nums1[0]), target1, &returnSize1);
    if (result1 != NULL) {
        printf("Test Case 1: Indices are %d and %d\n", result1[0], result1[1]);
        free(result1);
    } else {
        printf("Test Case 1: No solution found.\n");
    }

    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(nums2, sizeof(nums2) / sizeof(nums2[0]), target2, &returnSize2);
    if (result2 != NULL) {
        printf("Test Case 2: Indices are %d and %d\n", result2[0], result2[1]);
        free(result2);
    } else {
        printf("Test Case 2: No solution found.\n");
    }

    int nums3[] = {0,4,3,0};
    int target3 = 0;
    int returnSize3;
    int* result3 = twoSum(nums3, sizeof(nums3) / sizeof(nums3[0]), target3, &returnSize3);
    if (result3 != NULL) {
        printf("Test Case 3: Indices are %d and %d\n", result3[0], result3[1]);
        free(result3);
    } else {
        printf("Test Case 3: No solution found.\n");
    }

    return 0;
}
