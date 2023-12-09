
def f(m, x):
    ans = 0
    for p, s in enumerate(m):
        to_add = s
        for i in range(p+1):
            to_add *= x ** i
        ans += to_add
    return ans

def prod(x, i):
    ans = 1
    for j in range(i):
        ans *= (x - j)
    return ans

v = [1, 3, 6, 10, 15, 21, 16]
# v = [0, 3, 6, 9, 12, 15, 12]
# v = [10, 13, 16, 21, 30, 45, 34]

m = [v[0]]
for x in range(1, len(v)):
    print(m)
    # print('m: ', m)
    # a + b * x + c * (x-1) * x = v[2]
    # prod(x, i) = x * (x-1) * ... * (x - (i - 1))
    # f_(x) + new_m * prod(x, i) = v[x]
    # new_m = (v[x] - f_(x)) / prod(x, i)
    new_m = (v[x] - f(m, x)) / prod(x, x)
    if new_m == 0:
        break
    m.append(new_m)

m = m[:4]
print([f(m, i) for i in range(len(v))])
