#include <stdio.h>
#include "header.h"
int containsDuplicate(int* nums, int numsSize){
int i, j;
for (i = 0; i < numsSize; i++)
{
    for(j = i + 1; j < numsSize; j++)
    {
        if(nums[i] == nums[j])
        return 0;
    }
}
return 1;
}
