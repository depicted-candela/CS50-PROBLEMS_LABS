#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*Initializing auxiliar functions*/
void luhns(long n);
int lenln(long ln);
int card_type(long n, int l, int p);

int main(void)
{
    /*To get the number of the card*/
    long card_n = get_long("Number: ");
    /*To put Lunh's algorithm into action*/
    luhns(card_n);
}


void luhns(long n)
{
    /*var to save digit per digit of the card's number*/
    int d;
    /*var to save card's number*/
    long cn = n;
    /*var to save first step from Lunh's algorithm*/
    int p1 = 0;
    /*var to save second step from Lunh's algorithm*/
    int p2 = 0;
    /*var to save the length of the card number*/
    int ll;
    /*var to save the number that corresponds to the type of the card*/
    int ct;
    /*var to count the condition of digit (odd or even)*/
    int c = 0;

    ll = lenln(cn);
    /*While the length is being reducing until it is equals or greather than 1*/
    while (ll >= 1)
    {
        /*To extract the last element from the number*/
        d = cn % 10;
        /*To delete the last element of the number*/
        cn = cn / 10;
        /*If the extracted number is odd*/
        if (c % 2 != 0)
        {
            /*If the multiplication value have two digits extracts both*/
            if (d > 4)
            {
                /*Add the extracted numbers to the amount of first step*/
                p1 += (d * 2) % 10;
                p1 += (d * 2) / 10;
            }
            else
            {
                /*Add the extracted number to the amount of first step*/
                p1 += d * 2;
            }
            /*Add the extracted number to the amount of second step*/
        }
        else
        {
            p2 += d;
        }
        ll--;
        c++;
    }
    ll = lenln(n);
    /*Conditions to detect the card type or a invalid number*/
    if ((p2 + p1) % 10 == 0)
    {
        ct = card_type(n, ll, 2);
        if (ct == 34 || ct == 37)
        {
            if (ll == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (ct == 51 || ct == 52 || ct == 53 || ct == 54 || ct == 55)
        {
            if (ll == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (card_type(n, ll, 1) == 4)
        {
            if (ll > 12 && ll < 17)
            {
                printf("VISA\n");
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
    else
    {
        /*If is a valid number card but has no corresponding trademark*/
        printf("INVALID\n");
    }
}

/*Extracts the length of a positive value of long data type*/
int lenln(long n)
{
    int ln = floor(log10(n)) + 1;
    return ln;
}

/*Extracts the numbers of the card number requited to determine the card type*/
int card_type(long n, int l, int p)
{
    int ct = n / pow(10, l - p);
    return ct;
}