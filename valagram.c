#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool isAnagram(char * s, char * t){
	int hash[26] = {0};
	int i = 0;
	while (s[i])
	{
		hash[s[i] - '\0' - 97]++;
		i++;
	}
	i = 0;
	while (t[i]){
		hash[t[i] - '\0' - 97]--;
		i++;
	}
	i = 0;
	for(; i < 26; i++ ){
		if (hash[i] != 0)
			return false;
	}

	return true; 
}
int main() {
	char s[] = "anagram";
	char t[] = "nagaram";

	if (isAnagram(s, t)) {
		printf("The strings are anagrams.\n");
	} else {
		printf("The strings are not anagrams.\n");
	}

	return 0;
}

