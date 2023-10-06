#ifndef HEADER_H
#define HEADER_H
hh *creat_hashtable(int size);
node *creat_node(const char *key);
unsigned long int key_index(long int key, unsigned long int size);

int containsDuplicate(int* nums, int numsSize);
#endif