# TODO
# importing libraries needed
import cs50 as c
import sys

# a do while loop
while True:
    h = c.get_int('Height: ')
    if h > 0 and h < 9:
        for i in range(h):
            # formated string
            ans = " "*(h-i-1)+"#"*(i+1)+"  "+"#"*(i+1)
            print(f"{ans}")
        break
    else:
        continue