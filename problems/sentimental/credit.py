# TODO
import cs50 as cs
import math as m


def main():
    # To get the number of the card
    card_n = cs.get_int("Number: ")
    # To put Lunh's algorithm into action
    luhns(card_n)

# To calculate Lunhs number


def luhns(n):
    # var to save digit per digit of the card's number
    # var to save card's number
    cn = n
    # var to save first step from Lunh's algorithm
    p1 = 0
    # var to save second step from Lunh's algorithm
    p2 = 0
    # var to save the length of the card number

    # var to save the number that corresponds to the type of the card
    # var to count the condition of digit (odd or even)
    c = 0

    ll = lenln(cn)
    # While the length is being reducing until it is equals or greather than 1

    while ll >= 1:
        # To extract the last element from the number
        d = int(cn % 10)
        # To delete the last element of the number
        cn = int(cn / 10)
        # If the extracted number is odd
        if int(c % 2) != 0:
            # If the multiplication value have two digits extracts both
            if d > 4:
                # Add the extracted numbers to the amount of first step
                p1 += int((d * 2) % 10)
                p1 += int((d * 2) / 10)
            else:
                # Add the extracted number to the amount of first step
                p1 += int(d * 2)
            # Add the extracted number to the amount of second step
        else:
            p2 += d

        ll -= 1
        c += 1
    ll = lenln(n)
    # Conditions to detect the card type or an invalid number

    if int((p2 + p1) % 10) == 0:
        ct = card_type(n, ll, 2)
        if ct == 34 or ct == 37:
            if ll == 15:
                print("AMEX\n")
            else:
                print("INVALID\n")
        elif ct == 51 or ct == 52 or ct == 53 or ct == 54 or ct == 55:
            if ll == 16:
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        elif card_type(n, ll, 1) == 4:
            if ll > 12 and ll < 17:
                print("VISA\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID\n")
    else:
        # If is a valid number card but has no corresponding trademark
        print("INVALID\n")

# Extracts the length of a positive value of long data type


def lenln(n):
    ln = int(m.floor(m.log10(n)) + 1)
    return ln

# Extracts the numbers of the card number requited to determine the card type


def card_type(n, l, p):
    ct = int(n / m.pow(10, l - p))
    return ct


if __name__ == "__main__":
    main()