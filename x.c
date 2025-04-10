#include<stdlib.h>
void countCharacters(char *str, int *vowels, int *consonants, int *digits, int *spaces) {
    *vowels = *consonants = *digits = *spaces = 0;
    for (int i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if (ch >= 'a' && ch <= 'z') {
            if (strchr("aeiou", ch)) (*vowels)++;
            else (*consonants)++;
        } else if (isdigit(ch)) (*digits)++;
        else if (ch == ' ') (*spaces)++;
    }
}
void reverseWords(char *str) {
    char word[100], result[1000] = "";
    int i = 0, j = 0;

    while (1) {
        if (str[i] != ' ' && str[i] != '\0') {
            word[j++] = str[i];
        } else {
            word[j] = '\0';
            for (int k = j - 1; k >= 0; k--)
                strncat(result, &word[k], 1);
            if (str[i] == ' ') strcat(result, " ");
            j = 0;
        }
        if (str[i] == '\0') break;
        i++;
    }
    strcpy(str, result);
}
void toUppercase(char *str) {
    for (int i = 0; str[i]; i++) str[i] = toupper(str[i]);
}
int isPalindrome(char *str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        while (!isalnum(str[left])) left++;
        while (!isalnum(str[right])) right--;
        if (tolower(str[left]) != tolower(str[right])) return 0;
        left++; right--;
    }
    return 1;
}
int areAnagrams(char *s1, char *s2) {
    int count[256] = {0};
    for (int i = 0; s1[i]; i++) count[(unsigned char)s1[i]]++;
    for (int i = 0; s2[i]; i++) count[(unsigned char)s2[i]]--;
    for (int i = 0; i < 256; i++)
        if (count[i] != 0) return 0;
    return 1;
}


void spaceToUnderscore(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ') str[i] = '_';
}
int countUniqueWords(char *str) {
    char *words[100];
    int count = 0;
    char *token = strtok(str, " \n");
    while (token) {
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) words[count++] = token;
        token = strtok( NULL , " \n");
    }
    return count;
}
