#include <stdio.h>
#include <string.h>

void computeLPS(char pattern[], int m, int lps[])
{
    int length = 0;
    int i = 1;

    lps[0] = 0;

    while(i < m)
    {
        if(pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if(length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[100];

    int i = 0;
    int j = 0;
    int found = 0;

    computeLPS(pattern, m, lps);

    printf("\nLPS Array: ");

    for(i = 0; i < m; i++)
        printf("%d ", lps[i]);

    printf("\n\n");

    i = 0;

    while(i < n)
    {
        if(text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if(j == m)
        {
            printf("Pattern found at index %d\n",
                   i - j);

            found = 1;

            /*
             * Continue searching for other occurrences.
             */
            j = lps[j - 1];
        }
        else if(i < n && text[i] != pattern[j])
        {
            if(j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if(!found)
        printf("Pattern not found in the text.\n");
}

int main()
{
    char text[200];
    char pattern[100];

    printf("========================================\n");
    printf("   KNUTH-MORRIS-PRATT STRING MATCHING\n");
    printf("========================================\n");

    printf("\nEnter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter pattern: ");
    fgets(pattern, sizeof(pattern), stdin);

    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    if(strlen(pattern) == 0)
    {
        printf("\nPattern cannot be empty.\n");
        return 0;
    }

    if(strlen(pattern) > strlen(text))
    {
        printf("\nPattern is longer than the text.\n");
        return 0;
    }

    printf("\nSearching for pattern \"%s\"...\n", pattern);

    KMP(text, pattern);

    printf("\n========================================\n");

    return 0;
}