def caesar_decrypt(char, offset) -> str:
    result = ord(char) - offset
    if result >= ord('A'):
        return chr(result)
    else:
        return chr(result + ord('Z') - ord('A') + 1)


raw = 'FBUQIUUDSHOFJOEKHDQCUMYJXJXUIQCUAUOQDTKFBEQTJEBUQHDYDWYDPZK'

for j in range(1, 26):
    print('Offset=' + str(j), end=' ')
    for i in raw:
        print(caesar_decrypt(i, j), end='')
    print('')
