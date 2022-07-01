import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("python dna.py data.csv sequence.txt")
        quit()

    # TODO: Read database file into a variable
    dna_database = []
    header = []
    seq_count = {}

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        # just getting a list of the sequences, remove the commas, remove name, remove newline
        header = next(file).strip().split(",")
        del header[0]
        for seq in header:
            seq_count.update({seq: 0})

        file.seek(0)
        for row in reader:
            dna_database.append(row)

    # TODO: Read DNA sequence file into a variable
    dna_sequence = ""
    with open(sys.argv[2], "r") as file:
        dna_sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    for seq in seq_count:
        seq_count[seq] = longest_match(dna_sequence, seq)


    # TODO: Check database for matching profiles
    for person in dna_database:
        matchcounter = 0
        for seq in seq_count:
            # print(f"{seq_count[seq]}")
            # print(f"{person[seq]}")
            if int(seq_count[seq]) == int(person[seq]):
                matchcounter += 1
        if matchcounter == len(header):
            print(person["name"])
            return

    print("No match")
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
