#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string text = get_string("Text: ");

    // calculate the Coleman-Liau formula
    float L = count_letters(text) / (count_words(text) / 100.0);
    float S = count_sentences(text) / (count_words(text) / 100.0);
    // rounds the index value to the nearest int
    int index = (int) round(0.0588 * L - 0.296 * S - 15.8);

    // put the index into grades
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string s)
{
    int numChar = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            numChar++;
        }
    }

    return numChar;
}

int count_words(string s)
{
    int numWords = 1;

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 32)
        {
            numWords++;
        }
    }

    return numWords;
}

int count_sentences(string s)
{
    int numSent = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i] == 46) || (s[i] == 33) || (s[i] == 63))
        {
            numSent++;
        }
    }
    return numSent;
}