import sys
import math

def f(coeffs, x):
    multiplier = [1]
    for i in range(len(coeffs)):
        multiplier.append(multiplier[i] * (x-i))
    return sum(coeff * multiplier[i] for i, coeff in enumerate(coeffs))

ans1, ans2 = 0, 0
for line in sys.stdin.readlines():
    v = [int(a) for a in line.split(' ')]
    coeffs = [v[0]]
    for x in range(1, len(v)):
        # v[2] = a + b * 2 + c * (2-1) * 2
        # v[2] = f_(2) + c * 2!
        # c = (v[2] - f_(2)) / 2!
        coeffs.append((v[x] - f(coeffs, x)) / math.factorial(x))
    ans1 += f(coeffs, len(v))
    ans2 += f(coeffs, -1)

print("part 1:", round(ans1))
print("part 2:", round(ans2))
