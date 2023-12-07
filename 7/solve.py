import sys

lines = sys.stdin.readlines()

labels = ['23456789TJQKA', 'J23456789TQKA']

for part, label in enumerate(labels):
    map = {i: l for l, i in enumerate(label) }
    couples = []

    for line in lines:
        hand, value = line.split(' ')
        numbers = [0] * 16
        for x in hand:
            numbers[map[x]] += 1

        if part:
            joker_number = numbers[0]
            numbers[0] = 0
            max_index = numbers.index(max(numbers))
            numbers[max_index] += joker_number

        hand_hex = f'{max(numbers)}{numbers.count(2)}'
        hand_hex += ''.join(hex(map[x])[-1] for x in hand)
        couples.append((int(hand_hex, 16), int(value)))

    couples.sort(key=lambda x: x[0])
    ans = 0
    for i, couple in enumerate(couples):
        ans += (i+1)*couple[1]
    print(f'part {part}: {ans}')
