#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /*To getting someone's name*/
    string name = get_string("What's your name? ");
    /*To print someone's name*/
    printf("Hello, %s\n", name);
}