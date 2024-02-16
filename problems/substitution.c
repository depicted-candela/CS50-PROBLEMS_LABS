#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Initializing custom functions*/
string valid_key_m(string s, string alph, int n);
int valid_key(string s, string alph, int n);
string cipher_text(int nt, int nalph, string t, string k, string a);

int main(int argc, string argv[])
{
    /*Testing if arguments in cmd are complete*/
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    /*Putting the alphabet to contrast*/
    string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /*Extracting key and its length*/
    string key_s = argv[1];
    int n = strlen(key_s);

    /*To stop or to continue with the process by deciding for the key form*/

    if (valid_key(key_s, LETTERS, n) == 1)
    {
        /*Showing a message if the key has not a correct form*/
        printf("%s", valid_key_m(key_s, LETTERS, n));
        return 1;
    }

    /*Getting a plain text*/
    string plaintext = get_string("plaintext: ");
    int nt = strlen(plaintext);
    /*Printing the ciphertext*/
    printf("ciphertext: %s\n", cipher_text(nt, n, plaintext, key_s, LETTERS));
}

/*Rules a of valid key: message*/
string valid_key_m(string s, string alph, int n)
{
    /*To verify if there are 26 characters in the key*/
    int i, j;
    int v1 = 0;
    int v2 = 0;

    /*To verify that in the key there are only alphabetical characters*/
    for (i = 0; i < n; i++)
    {
        /*To verify if there is all alphabetical chars*/
        for (j = 0; j < n; j++)
        {
            if (toupper(alph[i]) == toupper(s[i]))
            {
                v1++;
            }
        }
        for (j = i + 1; j < n; j++)
        {
            if (toupper(s[i]) == toupper(s[j]))
            {
                v2++;
            }
        }
    }
    if (n != 26 || v2 > 0 || v1 != 52)
    {
        return "Invalid key:\n1. Key must contain 26 characters.\n2. Key must not contain repeated characters.\n3. Key must contain only alphabet characters.\n";
    }
    else
    {
        return "";
    }
}


/*Rules of a valid key: return*/
int valid_key(string s, string alph, int n)
{
    /*To verify if there are 26 characters in the key*/
    int i, j;
    int v1 = 0;
    int v2 = 0;

    /*To verify that in the key there are only alphabetical characters*/
    for (i = 0; i < n; i++)
    {
        /*To verify if there is all alphabetical chars*/
        for (j = 0; j < n; j++)
        {
            if (toupper(alph[j]) == toupper(s[i]))
            {
                v1++;
            }
        }
        for (j = i + 1; j < n; j++)
        {
            if (toupper(s[i]) == toupper(s[j]))
            {
                v2++;
            }
        }
    }
    if (v1 != 26 || v2 > 0 || n != 26)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*To make the encryption*/
string cipher_text(int nt, int nalph, string t, string k, string a)
{
    int i, j;
    for (i = 0; i < nt; i++)
    {
        for (j = 0; j < nalph; j++)
        {
            if (a[j] == toupper(t[i]))
            {
                if (isupper(t[i]))
                {
                    t[i] = toupper(k[j]);
                }
                else
                {
                    t[i] = tolower(k[j]);
                }
                break;
            }
            else
            {
                continue;
            }
        }
    }
    return t;
}