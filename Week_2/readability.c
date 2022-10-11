#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float grade(string text);

int main(void)
{
    string text_ = get_string("Text: ");
    int index = round(grade(text_));
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

float grade(string text)
{
    int n = strlen(text);
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0; i < n; i++)
    {
        char c = text[i];
        //Count the letters
        if (isalpha(c) != 0)
        {
            letters++;
        }

        //Count the words
        if (c == ' ')
        {
            words++;
        }
        //Count the sentences
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }
    //Because we missed one word in the begining
    words += 1;

    //printf("letters:%i words:%i sentences:%i \n",letters,words,sentences);

    float L = (float) letters / (float) words * 100.0;
    float S = (float) sentences / (float) words * 100.0;
    //printf("%f %f\n",L,S);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    //printf("%f\n",index);

    return index;
}
