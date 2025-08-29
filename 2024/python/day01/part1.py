# part1.py
import sys


def main():
    """
    Main function to read the input file, process the entries, and calculate
    the total distance between location IDs.
    """
    if len(sys.argv) < 2:
        print("Usage: python part1.py <input_file>")
        sys.exit(1)
    filename = sys.argv[1]
    try:
        with open(filename) as file:
            total_distance = 0
            left_list = []
            right_list = []
            for line in file:
                entries = line.strip().split() # strips newlines and spilts by spaces
                if entries != []:
                    left_list.append(entries[0])
                    right_list.append(entries[1])
        file.close()

        left_list = sorted(left_list)
        right_list = sorted(right_list)

        # Iterate through the lists and calculate the total distance
        for i in range(len(left_list)):
            pair = (left_list[i], right_list[i])
            dist = abs(int(pair[0]) - int(pair[1]))
            total_distance += dist

        print(f"Total distance: {total_distance}")
    except FileNotFoundError:
        print(f"Error: The file {filename} was not found.")

if __name__ == "__main__":
    main()
