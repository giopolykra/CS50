#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Ask user to provide a name
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
