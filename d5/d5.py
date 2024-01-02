import os

from bisect import bisect_left

def part1(input):
    lines = input.split('\n')
    seeds = [int(x) for x in lines[0][7:].split(' ')]

    i = 2
    while i < len(lines):
        start = lines[i]

        i += 1
        events = []
        while i < len(lines) and lines[i]:
            dest, source, length = lines[i].split(' ')
            events.append([int(source), int(dest), int(length)])
            i += 1
        events.sort()

        nxt = []
        for seed in seeds:
            j = bisect_left(events, [seed, 0, 0]) - 1

            s, d, l = events[j]
            if s <= seed <= s + l: 
                nxt.append(d + (seed - s))
            else:
                nxt.append(seed)
        
        i += 1
        seeds = nxt

    print(min(seeds))

def part2(input):
    lines = input.split('\n')
    seeds = [int(x) for x in lines[0][7:].split(' ')]
    ranges = []
    for i in range(0, len(seeds), 2):
        ranges.append([seeds[i], seeds[i + 1]])
    
    i = 2
    while i < len(lines):
        ranges.sort()
        start = lines[i]

        i += 1
        events = []
        while i < len(lines) and lines[i]:
            dest, source, length = lines[i].split(' ')
            events.append([int(source), int(dest), int(length)])
            i += 1
        events.sort()

        nxt = []
        for s, d, l in events:
            for j in range(len(ranges)):
                if not ranges[j]: continue
                start, length = ranges[j]
                if s + l < start or start + length < s:
                    continue

                if start < s:
                    nxt.append([d, start + length - s])
                    left = s - start
                    ranges[j] = [start, left]
                elif start + length <= s + l:
                    nxt.append([d + (start - s), length])
                    ranges[j] = None
                else:
                    nxt.append([d + (start - s), (s + l) - start])
                    ranges[j] = [s + l, (start + length) - (s + l)]

        nxt.extend([r for r in ranges if r])

        i += 1
        ranges = nxt

    print(min(a for a, b in ranges))

if __name__ == "__main__":
    dir_path = os.path.dirname(os.path.realpath(__file__))
    i = open(dir_path + '\d5.in', 'r').read()

    part2(i)