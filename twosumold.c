
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
  
    int i;
    int *newArray =(int *)malloc(2 * sizeof(int));
                if (returnSize == NULL) 
                return NULL;
for (i = 0; i < numsSize; i++)
{
    for (int j = i + 1; j < numsSize; j++)
    {
       int sum =  nums[i] + nums[j];
        if (sum == target)
        {
            newArray[0] = i;
            newArray[1] = j;
            *returnSize = 2;
                break;
        }
    }
        if (i == numsSize)
        {
            *returnSize = 0;
        return NULL;
        }
    }
return(newArray);
}