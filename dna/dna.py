import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE DNASEQUENCE")

    # TODO: Read database file into a variable
    srts = []

    with open(sys.argv[1]) as file:
        reader1 = csv.DictReader(file)
        for name in reader1:
            # print(name)
            srts.append(name)

    # TODO: Read DNA sequence file into a variable
    # seq = []

    with open(sys.argv[2]) as file:
        seq = file.read()
    # print(seq)

    # TODO: Find longest match of each STR in DNA sequence
    match = {}
    srt = srts[0]
    # print(srt)
    for subseq in srt.keys():
        # print(subseq)
        match[subseq] = 0
    # print(match)
    del match['name']
    # print(match)
    for estr in match:
        match[estr] = longest_match(seq, estr)
    # print(match)

    # TODO: Check database for matching profiles
    flag = False
    for srt in srts:
        for item in match:
            # print(item)
            # print(srt[item])
            # print(srt['name'])
            # print(match[item])
            # print(int(srt[item]) == int(match[item]))
            if int(srt[item]) == int(match[item]):
                flag = True
                # print(flag)
            else:
                flag = False
                # print(srt)
                break
        # print(flag)
        if flag == True:
            print(srt['name'])
    print('No match')


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
