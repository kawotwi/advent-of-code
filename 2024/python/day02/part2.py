# part2.py
import sys

import numpy as np


def is_valid_sequence(levels):
    """Check if a sequence follows the required pattern (monotonic with
    differences of 1, 2, or 3)"""
    if len(levels) <= 1:
        return True

    start_direction = np.sign(levels[1] - levels[0])
    if start_direction == 0:  # No change between first elements
        return False

    for i in range(len(levels) - 1):
        diff = levels[i + 1] - levels[i]
        current_direction = np.sign(diff)
        if current_direction != start_direction or abs(diff) not in [1, 2, 3]:
            return False

    return True

def can_be_valid_report(levels):
    """Check if report can become valid by removing one element"""
    # First check if it's already valid without removing anything
    if is_valid_sequence(levels):
        return True

    # Try removing each element
    for i in range(len(levels)):
        modified_levels = levels[:i] + levels[i+1:]
        if is_valid_sequence(modified_levels):
            return True

    return False

def main():
    """
    Read reports from file and count valid ones (those that are valid
    or can become valid by removing one element)
    """
    total_valid = 0

    if len(sys.argv) < 2:
        print("Usage: python part2.py <input_file>")
        sys.exit(1)
    filename = sys.argv[1]

    with open(filename) as file:
        for line in file:
            levels = [int(x) for x in line.strip().split()]

            if len(levels) <= 1:
                continue

            if can_be_valid_report(levels):
                total_valid += 1

    print(f"Total valid reports: {total_valid}")

if __name__ == '__main__':
    main()
