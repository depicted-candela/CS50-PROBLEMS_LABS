import cs50 as cs
import sys as s


# Alphabet symbols associated to Scrabble
LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWYZ'
# Detecting the length of the array

arr_len = len(LETTERS)


def main():
    text = cs.get_string("Text: ")
    col = coleman(count_letters(text), count_words(text), count_sentences(text))
    if col > 16:
        print("Grade 16+\n")
    elif col < 0:
        print("Before Grade 1\n")
    else:
        print(f"Grade {col}")

# To calculate the amount of letters


def count_letters(text):
    letters = 0
    n = len(text)
    for i in range(n):
        for j in range(arr_len):
            if text[i].upper() == LETTERS[j]:
                letters += 1
    # print(f"Letras: {letters}", end = " ")
    return letters

# To calculate the amount of words (separated by spaces and counting the last
# word when counter reach the last character)


def count_words(text):
    words, j = 0, 0
    n = len(text)
    for i in range(n):
        if text[i] == ' ':
            words += 1
        j += 1
    if n == j and n > 0:
        words += 1
    # print(f"Words: {words}", end = " ")
    return words

# To calculate sentences by dividing the text in its
# (., !, ?)


def count_sentences(text):
    sent = 0
    n = len(text)
    for i in range(n):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sent += 1
    # print(f"Frases: {sent}", end = " ")
    return sent

# To calculate Coleman's formula considering
# results of operations with data types


def coleman(l, w, s):
    col = int(round(0.0588 * ((l / w) * 100.0) - 0.296 * ((s / w) * 100.0) - 15.8))
    return col


if __name__ == "__main__":
    main()