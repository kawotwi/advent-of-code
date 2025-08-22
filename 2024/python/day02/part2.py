# part1.py
import numpy as np

def recursive_valid_report(levels, i):
    """
    Recursively check if the report is valid by removing one element at a time.
    """
    if i == len(levels):
        return False
    dampened_report = levels[:i] + levels[i+1:]
    start_direction = np.sign(dampened_report[1] - dampened_report[0])
    valid_report = True
    j = 0
    while j < len(dampened_report) - 1:
        diff = dampened_report[j + 1] - dampened_report[j]
        current_direction = np.sign(diff)
        if current_direction != start_direction or abs(diff) not in [1, 2, 3]:
            valid_report = False
            break
        j += 1
    if valid_report:
        return True
    return recursive_valid_report(levels, i + 1)

def main():

    """
    Read in file.
    Split line by spaces.
    Check if list is monotonic.
    Check if nth element is +/- 1 or 3 from n+1 element. 
    """
    total_valid = 0
    with open('input.txt', 'r') as file:
        for line in file:
            levels = [int(x) for x in line.strip().split()]
            print(f"Levels: {levels}")
            # Skip empty lines or lines with only one number
            if len(levels) <= 1:
                continue
            if recursive_valid_report(levels, 0):
                total_valid += 1
                print("Report SAFE\n")
            else:
                # print("Levels: ", levels)
                print("Report UNSAFE\n")

    print(f"Total valid reports: {total_valid}")

if __name__ == '__main__':
    main()