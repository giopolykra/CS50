#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        //ask user for the height of the triangle
        n = get_int("Height: ");
    }
    while ((n < 1) || (n > 8));

    int i, j;
    //Loop Rows
    for (i = 1; i < n + 1; i++)
    {
        //Loop Columns
        for (j = 0; j < n; j++)
        {
            if (j < n - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }
        printf("\n");
    }
}
