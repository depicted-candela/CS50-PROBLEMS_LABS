#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 1;
    /*Asking for the height of the pyramids*/
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    /*Printing not perfect pyramids*/
    int i;
    /*# per line*/
    for (i = 0; i < height; i++)
    {
        /*White spaces per line*/
        int k;
        for (k = 0; k < height - 1 - i; k++)
        {
            printf(" ");
        }
        /*# rows of left pyramid*/
        int l;
        for (l = -1; l < i; l++)
        {
            printf("#");
        }
        /*two white spaces between pyramids*/
        printf("  ");
        /*# rows of right pyramid*/
        int j;
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}