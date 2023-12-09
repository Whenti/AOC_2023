import sys

def f(m, x):
    ans = 0
    for p, s in enumerate(m):
        to_add = s
        for i in range(p):
            to_add *= (x - i)
        ans += to_add
    return ans

lines = sys.stdin.readlines()

ans1 = 0
ans2 = 0
for line in lines:
    v = [int(a) for a in line.split(' ')]
    m = [v[0]]
    prod = 1
    for x in range(1, len(v) - 1):
        # a + b * 2 + c * (2-1) * 2 = v[2]
        # prod(x) = x * (x-1) * ... * 1
        # f_(x) + new_m * prod(x) = v[x]
        # new_m = (v[x] - f_(x)) / prod(x)
        prod *= x
        m.append((v[x] - f(m, x)) / prod)
    ans1 += f(m, len(v))
    ans2 += f(m, -1)

print(ans1)
print(ans2)
