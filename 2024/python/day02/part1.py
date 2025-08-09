# part1.py
import numpy as np

def main():

    """
    Read in file.
    Split line by spaces.
    Check if list is monotonic.
    Check if nth element is +/- 1 or 3 from n+1 element. 
    """
    total_levels = 0
    with open('input.txt', 'r') as file:
        levels = file.readline().strip().split(' ')
        while levels and len(levels) > 1:
            # if levels:
            monotonic = 1 * np.sign(int(levels[1])-int(levels[0]))
            add_count = True
            for i in range(len(levels) - 1):
                curr_lvl = int(levels[i])
                next_lvl = int(levels[i + 1])
                # check if monotonic
                if 1*np.sign(next_lvl - curr_lvl) != monotonic:
                    add_count = False
                if abs(next_lvl - curr_lvl) not in [1,2,3]:
                    add_count = False
            if add_count:
                total_levels += 1
            levels = file.readline().strip().split(' ')
    print(f"Total valid levels: {total_levels}")

if __name__ == '__main__':
    main()