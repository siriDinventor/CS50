import csv
import sys
from csv import DictReader


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python script.py input.csv input.txt")
        sys.exit(1)

    # Read CSV database file into a list of dictionaries
    data_csv = sys.argv[1]
    txt_file = sys.argv[2]

    with open(data_csv, "r") as csvfile:
        reader = DictReader(csvfile)
        dict_list = list(reader)

    # Read DNA sequence file into a variable
    with open(txt_file, "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    max_counts = []
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        max_count = longest_match(sequence, STR)
        max_counts.append(max_count)

    # Check database for matching profiles
    for i in range(len(dict_list)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            if int(max_counts[j - 1]) == int(dict_list[i][reader.fieldnames[j]]):
                matches += 1
            if matches == (len(reader.fieldnames) - 1):
                print(dict_list[i]['name'])
                sys.exit(0)

    # If no match is found
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0

        while (i + count * subsequence_length) < sequence_length:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
