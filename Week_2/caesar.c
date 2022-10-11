#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check if the given arguments are 2 or not (programs name + key)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int arg_length = strlen(argv[1]);
        //Check if the 2nd argument is valid number or not
        //Loop over the array argument characters
        for (int i = 0; i < arg_length; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    printf("%s", argv[1]);

    int key = atoi(argv[1]);

    string plain_text = get_string("plaintext: ");

    printf("ciphertext: ");

    int plain_text_length = strlen(plain_text);

    for (int j = 0; j < plain_text_length; j++)
    {
        //Keep the upper characters as upper
        if (isupper(plain_text[j]))
        {
            int cipher_char_index = ((((int) plain_text[j] - (int) 'A') + key) % 26) + (int) 'A';
            printf("%c", cipher_char_index);
        }
        //Keep the lower characters as lower
        else if (islower(plain_text[j]))
        {
            int cipher_char_index = ((((int) plain_text[j] - (int) 'a') + key) % 26) + (int) 'a';
            printf("%c", cipher_char_index);
        }
        //if not a character keep it as it is
        else
        {
            printf("%c", plain_text[j]);
        }
    }
    printf("\n");
}
