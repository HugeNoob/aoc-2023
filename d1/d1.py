import os

from collections import deque

def part1(input):
    res = 0
    for line in input.split('\n'):
        if not line: continue

        f = l = -1
        for c in line:
            if c.isnumeric():
                if f == -1:
                    f = c
                l = c
    
        res += int(str(f) + str(l))

    return res

def part2(input):
    res = 0
    
    """
    one, two, six, 
    four, five, nine
    three, seven, eight
    """

    nums = {
        'one': 1,
        'two': 2,
        'three': 3,
        'four': 4,
        'five': 5,
        'six': 6,
        'seven': 7,
        'eight': 8,
        'nine': 9
    }

    res = 0
    for line in input.split('\n'):
        if not line: continue

        f = l = -1
        for i, c in enumerate(line):
            if c.isnumeric():
                if f == -1:
                    f = c
                l = c
                continue

            t = -1
            x = ''.join(line[i - 2:i + 1])
            y = ''.join(line[i - 3:i + 1])
            z = ''.join(line[i - 4:i + 1])

            if x in ['one', 'two', 'six']:
                t = nums[x]
            elif y in ['four', 'five', 'nine']:
                t = nums[y]
            elif z in ['three', 'seven', 'eight']:
                t = nums[z]

            if t != -1:
                if f == -1:
                    f = t
                l = t

        res += int(str(f) + str(l))
    
    return res

if __name__ == "__main__":
    dir_path = os.path.dirname(os.path.realpath(__file__))
    i = open(dir_path + '\d1-in.txt', 'r').read()

    print(part1(i))
    print(part2(i))
