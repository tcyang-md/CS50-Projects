#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define _GNU_SOURCE
#include <stdlib.h>

string sub_cipher(string key, string s);

int main(int argc, string argv[])
{
    // too many keys or not enough keys
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    // key isn't 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }
    // valid 26 letters, continue
    else
    {
        string key = argv[1];

        // checks invalid characters
        for (int i = 0; i < strlen(key); i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Key contains invalid characters.\n");
                exit(1);
            }
        }

        // checks repeat characters in key
        for (int i = 0; i < strlen(key); i++)
        {
            char letter = key[i];
            int count = 0;
            for (int j = 0; j < strlen(key); j++)
            {
                if (tolower(letter) == tolower(key[j]))
                {
                    count++;
                }
            }
            if (count > 1)
            {
                printf("Key contains duplicate characters.\n");
                exit(1);
            }
            count = 0;
        }


        // get text
        string plain = get_string("Plain text: ");

        //call cipher
        printf("ciphertext: %s\n", sub_cipher(key, plain));

    }
}

string sub_cipher(string key, string s)
{
    // change the key to uppercase
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }

    // go through the whole string
    for (int i = 0; i < strlen(s); i++)
    {

        int s_num = s[i];

        // adjust uppercase
        if (s_num >= 65 && s_num <= 90)
        {
            s[i] = key[s_num - 65];
        }
        // adjust lowercase
        else if (s_num >= 97 && s_num <= 122)
        {
            s[i] = key[s_num - 97];
            // since key is uppercase, and you know this is lowercase, gotta change the key to lower
            s[i] = tolower(s[i]);
        }
    }

    return s;
}