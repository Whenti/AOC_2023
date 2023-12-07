import sys

lines = sys.stdin.readlines()

labels = ['23456789TJQKA', 'J23456789TQKA']

for part, label in enumerate(labels):
    map = {l: i for i, l in enumerate(label) }
    couples = []

    for line in lines:
        hand, value = line.split(' ')
        numbers = [0] * len(label)
        cards = [map[card] for card in hand]
        for card in cards:
            numbers[card] += 1

        if part:
            joker_number = numbers[map['J']]
            numbers[map['J']] = 0
            max_index = numbers.index(max(numbers))
            numbers[max_index] += joker_number

        game_power = f'{max(numbers)}{numbers.count(2)}'
        game_power += ''.join(str(card).zfill(2) for card in cards)
        couples.append((game_power, int(value)))

    couples.sort(key=lambda x: x[0])
    ans = 0
    for i, couple in enumerate(couples):
        ans += (i+1)*couple[1]
    print(f'part {part}: {ans}')
