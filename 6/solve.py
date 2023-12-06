import sys
import re
import math

def readline_fmt():
    line = sys.stdin.readline()
    return re.sub(' +', ' ', line.rstrip())

def solve(time, record):
    # - hold**2 + hold * time - record > 0
    a, b, c = - 1, time, -record
    delta = b ** 2 - 4 * a * c
    if delta <= 0:
        return 0
    sdelta = math.sqrt(delta)
    x2, x1 = (- b - sdelta) / (2 * a), (- b + sdelta) / (2 * a)
    return math.ceil(x2-1) - math.floor(x1+1) + 1

# part 1
times = [int(x) for x in readline_fmt().split(' ')[1:]]
records = [int(x) for x in readline_fmt().split(' ')[1:]]
ans1 = 1
for time, record in zip(times, records):
    ans1 *= solve(time, record)
print(ans1)

# part 2
big_time = int(''.join(str(x) for x in times))
big_record = int(''.join(str(x) for x in records))
ans2 = solve(big_time, big_record)
print(ans2)
