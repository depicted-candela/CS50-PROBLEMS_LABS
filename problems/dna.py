import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable

    with open(sys.argv[1]) as f:
        # Reading the csv file using DictReader
        csv_reader = csv.DictReader(f)

        # Converting the file to dictionary by first converting to list and then converting the list to dict
        dict_from_csv = dict(list(csv_reader)[0])

        # Making a list from the keys of the dict
        str_names = list(dict_from_csv.keys())
        str_names = str_names[1:]
        l_s_n = len(str_names)

    db = {}
    with open(sys.argv[1]) as f:
        r = csv.DictReader(f)
        for row in r:
            str = {}
            for c in str_names:
                str[c] = int(row[c])
            db[row['name']] = str

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2]) as f:
        r = csv.reader(f)
        for row in r:
            seq = row[0]

    # TODO: Find longest match of each STR in DNA sequence

    l_match = {}
    for i in str_names:
        l_match[i] = longest_match(seq, i)

    # TODO: Check database for matching profiles

    check = 0
    # Walking throughout the database structure
    for i, j in db.items():
        c = 0
        for u, v in j.items():
            for x, y in l_match.items():
                if x == u and v == y:
                    c += 1
            if c == l_s_n:
                print(i)
                check = 1
                break
    if check == 0:
        print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
