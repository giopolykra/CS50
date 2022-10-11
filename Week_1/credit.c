#include <cs50.h>
#include <stdio.h>

long get_card_number(void);
long get_length(long);
long get_checksum(long);
long get_first_digits(long);

int main(void)
{
    // Ask user for the viza code
    long n = get_card_number();
    long cc = get_length(n);
    long l = get_checksum(n);
    long ff = get_first_digits(n);

    //For testing
    //printf("%ld %ld %ld %ld \n",n,cc,l,ff);

    if (l % 10 == 0)
    {
        if ((cc == 16) && ((ff > 50) && (ff < 56)))
        {
            printf("MASTERCARD\n");
        }
        else if (((cc == 13) || (cc == 16)) && (ff / 10 == 4))
        {
            printf("VISA\n");
        }
        else if ((cc == 15) && ((ff == 34) || (ff == 37)))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

long get_card_number(void)
{
    // Ask user to give cda number
    long n;
    do
    {
        n =  get_long("Number: ");
    }
    while (n < 0);
    return n;
}

long get_length(long n)
{
    // Computes the length of the imput number
    int i = 0;
    long cc = n;
    while (cc > 0)
    {
        cc = cc / 10;
        i++;
    }
    return i;
}

long get_checksum(long n)
{
    // Computes the checksum of the cards number
    int sum1 = 0;
    int sum2 = 0;
    long x = n;
    int total = 0;
    int mod1;
    int mod2;
    int d1;
    int d2;

    //Loop untill we excaust all the digits
    do
    {
        //remove the last digit
        mod1 = x % 10;
        x = x / 10;
        sum1 += mod1;

        //remove the second to last digit
        mod2 = x % 10;
        x = x / 10;
        mod2 *= 2;

        sum2 += mod2 % 10 + mod2 / 10;

    }
    while (x > 0);

    return sum2 + sum1;
}

long get_first_digits(long n)
{
    // Gets the two first digits of the imput number
    long start = n;
    do
    {
        start = start / 10;
    }
    while (start > 100);
    return start;
}
