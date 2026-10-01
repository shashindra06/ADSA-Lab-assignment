#include <stdio.h>
#include <string.h>

#define CHAR_SIZE 256

void buildBadCharacterTable(char pattern[], int m, int badChar[])
{
    int i;

    /*
     * Initially, every character is assumed
     * not to occur in the pattern.
     */
    for(i = 0; i < CHAR_SIZE; i++)
        badChar[i] = -1;

    /*
     * Store the last occurrence of each character.
     */
    for(i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

void boyerMoore(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    int badChar[CHAR_SIZE];

    int shift = 0;
    int found = 0;

    buildBadCharacterTable(pattern, m, badChar);

    while(shift <= n - m)
    {
        int j = m - 1;

        /*
         * Compare pattern from right to left.
         */
        while(j >= 0 &&
              pattern[j] == text[shift + j])
        {
            j--;
        }

        /*
         * Complete match
         */
        if(j < 0)
        {
            printf("Pattern found at index %d\n",
                   shift);

            found = 1;

            /*
             * Shift pattern to search for
             * another occurrence.
             */
            if(shift + m < n)
            {
                shift += m -
                         badChar[(unsigned char)
                                 text[shift + m]];
            }
            else
            {
                shift += 1;
            }
        }
        else
        {
            int badCharacterPosition =
                badChar[(unsigned char)text[shift + j]];

            int movement =
                j - badCharacterPosition;

            if(movement < 1)
                movement = 1;

            shift += movement;
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
    printf("       BOYER-MOORE STRING MATCHING\n");
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

    boyerMoore(text, pattern);

    printf("\n========================================\n");

    return 0;
}