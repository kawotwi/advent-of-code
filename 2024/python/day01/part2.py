# part2.py
import sys
from collections import Counter


def main():
    """
    Main function to read the input file, process the entries, and calculate
    the similarity score, with a metric based on how often numbers in the left
    list show up in the right list.
    """
    filename = sys.argv[1]
    try:
        with open(filename) as file:
            similarity = 0
            left_list = []
            right_list = []

            for line in file:
                entries = line.strip().split() # strips newlines and spilts by spaces
                if entries:
                    left_list.append(entries[0])
                    right_list.append(entries[1])

        right_counter = Counter(right_list)
        similarity = sum(int(id) * right_counter[id] for id in left_list)

        print(f"Total similarity score: {similarity}")
    except FileNotFoundError:
        print(f"Error: The file {filename} was not found.")

if __name__ == "__main__":
    main()
