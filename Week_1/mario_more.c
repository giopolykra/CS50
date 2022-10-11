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
    for (i = 0; i < n; i++)
    {
        //Loop Columns
        for (j = 0; j < n + i + 4; j++)
        {
            if (((n - i - 1 < j) && (j < n + 1)) || (n + 2 < j))
            {
                printf("#");
            }
            else if ((j < n - i - 1) || ((n < j) && (j < n + 3)))
            {
                printf(" ");
            }

        }
        printf("\n");
    }
}
