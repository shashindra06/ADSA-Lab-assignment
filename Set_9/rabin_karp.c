#include <stdio.h>
#include <string.h>

#define PRIME 101
#define BASE 256

void rabinKarp(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    int patternHash = 0;
    int textHash = 0;
    int h = 1;

    int i, j;
    int found = 0;

    /*
     * h = BASE^(m-1) % PRIME
     */
    for(i = 0; i < m - 1; i++)
        h = (h * BASE) % PRIME;

    /* Calculate initial hashes */
    for(i = 0; i < m; i++)
    {
        patternHash =
            (BASE * patternHash + pattern[i]) % PRIME;

        textHash =
            (BASE * textHash + text[i]) % PRIME;
    }

    /* Slide pattern over text */
    for(i = 0; i <= n - m; i++)
    {
        /*
         * If hash values match, compare characters
         * to avoid false matches due to collision.
         */
        if(patternHash == textHash)
        {
            for(j = 0; j < m; j++)
            {
                if(text[i + j] != pattern[j])
                    break;
            }

            if(j == m)
            {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }

        /* Calculate hash for next window */
        if(i < n - m)
        {
            textHash =
                (BASE * (textHash - text[i] * h)
                 + text[i + m]) % PRIME;

            if(textHash < 0)
                textHash += PRIME;
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
    printf("       RABIN-KARP STRING MATCHING\n");
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

    printf("\nSearching for pattern \"%s\"...\n\n", pattern);

    rabinKarp(text, pattern);

    printf("\n========================================\n");

    return 0;
}