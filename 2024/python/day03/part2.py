import re

def expr_evaluator(line):
    result = 0
    mul_arr = re.findall(r'mul\((\d+),(\d+)\)', line)
    for a,b in mul_arr:
        result += int(a) * int(b)
    return result

def main():

    result = 0
    with open("input.txt") as f:
        for line in f:

            result += expr_evaluator(line)
    print(f'Result: {result}')





if __name__ == "__main__":
    main()