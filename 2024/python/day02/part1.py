# part1.py
import numpy as np

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
            # Skip empty lines or lines with only one number
            if len(levels) <= 1:
                continue
            # Check if the sequence is monotonic and has valid steps
            is_valid = True
            expected_direction = np.sign(levels[1] - levels[0])
            for i in range(len(levels) - 1):
                diff = levels[i + 1] - levels[i]
                current_direction = np.sign(diff)
                # Check if monotonic direction is maintained and step size is valid
                if current_direction != expected_direction or abs(diff) not in [1, 2, 3]:
                    is_valid = False
                    break
            if is_valid:
                total_valid += 1
                
    print(f"Total valid levels: {total_valid}")

if __name__ == '__main__':
    main()