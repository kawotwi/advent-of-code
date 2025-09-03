import re
# """
#     result = 0
#     open file read line by line:
#         evaluate regex expressions and return an array from that line of possible candidates
#         calculate the product and add to result


#     for later* re.findall(r'mul\((\d+),(\d+)\)', text)
#     re.findall(r"mul\((\d+),(\d+)\)", line)
# """

def main():

    result = 0
    with open("input.txt") as f:
        for line in f:
            mul_arr = re.findall(r'mul\((\d+),(\d+)\)', line)
            for a,b in mul_arr:
                result += int(a) * int(b)
    print(f'Result: {result}')





if __name__ == "__main__":
    main()