#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    char *key;
    char **strs;
    int strsSize;
    struct node_s *next;
} node_t;

typedef struct table_s {
    node_t **array;
    int size;
} table_t;

table_t *create_table(int size) {
    table_t *ht = malloc(sizeof(table_t));
    if (ht == NULL)
        return NULL;

    ht->array = malloc(sizeof(node_t *) * size);
    if (ht->array == NULL) {
        free(ht);
        return NULL;
    }

    ht->size = size;
    for (int i = 0; i < size; i++)
        ht->array[i] = NULL;

    return ht;
}

char *sort_key(char *str) {
    int size = strlen(str);
    int hash[26] = {0};
    char *key = malloc(size + 1);
    char *k = key;
    int i = 0;

    while (str[i]) {
        hash[str[i] - 'a']++;
        i++;
    }

    for (i = 0; i < 26; i++) {
        for (int j = 0; j < hash[i]; j++) {
            *k++ = i + 'a';
        }
    }

    *k = '\0';
    return key;
}

unsigned int index_key(const unsigned char *key, unsigned long int size) {
    unsigned int index;
    index = hash_djb2(key) % size;
    return index;
}

node_t *create_node(const char *key, const char *value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;

    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        free(new_node);
        return NULL;
    }

    new_node->strsSize = 1;
    new_node->strs = malloc(sizeof(char *));
    new_node->strs[0] = strdup(value);

    new_node->next = NULL;
    return new_node;
}

node_t *find_key(table_t *ht, char *key, char *value) {
    unsigned int index = index_key((const unsigned char *)key, ht->size);
    node_t *current = ht->array[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Add the new value to the node
            current->strsSize++;
            current->strs = realloc(current->strs, current->strsSize * sizeof(char *));
            current->strs[current->strsSize - 1] = strdup(value);
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int set_hashtable(table_t *ht, char *key, char *value) {
    node_t *node = create_node(key, value);
    if (ht == NULL || key == NULL || value == NULL || node == NULL)
        return 0;

    unsigned int index = index_key((const unsigned char *)key, ht->size);
    node_t *current = ht->array[index];

    if (current == NULL) {
        ht->array[index] = node;
    } else {
        // Add the new node to the beginning of the linked list (chaining)
        node->next = current;
        ht->array[index] = node;
    }
    return 1;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes) {
    char ***result = NULL;
    int *colsSize = NULL;
    size_t i;

    table_t *hash_table = create_table(strsSize);
    *returnSize = 0;

    for (int i = 0; i < strsSize; i++) {
        char *key = sort_key(strs[i]);
        node_t *found = find_key(hash_table, key, strs[i]);

        if (found == NULL) {
            set_hashtable(hash_table, key, strs[i]);
            (*returnSize)++;
        }

        free(key); // Free the key after use
    }

    colsSize = (int *)malloc(*returnSize * sizeof(int));
    result = (char ***)malloc(*returnSize * sizeof(char **));
    *returnColumnSizes = colsSize;

    int resultIndex = 0;

    for (i = 0; i < hash_table->size; i++) {
        node_t *current = hash_table->array[i];

        while (current) {
            colsSize[resultIndex] = current->strsSize;
            result[resultIndex] = current->strs;
            current = current->next;
            resultIndex++;
        }
    }

    return result;
}

int main() {
    char *strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int strsSize = sizeof(strs) / sizeof(strs[0]);
    int returnSize;
    int *returnColumnSizes;

    char ***result = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("\"%s\"", result[i][j]);
            if (j < returnColumnSizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}