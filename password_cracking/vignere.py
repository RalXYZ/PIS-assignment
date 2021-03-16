weight = {
    'him': 1, 'his': 1,
    'she': 2, 'her': 2,
    'you': 1, 'your': 2,
    'our': 1, 'ours': 2,
    'they': 2, 'them': 2, 'their': 3,
    'self': 2, 'selves': 4,
}


def caesar_decrypt(char, offset) -> str:
    result = ord(char) - offset
    if result >= ord('a'):
        return chr(result)
    else:
        return chr(result + ord('z') - ord('a') + 1)


def vignere_decrypt(cipher_char, key_char) -> str:
    return caesar_decrypt(cipher_char, ord(key_char) - ord('a'))


def calc_score(plaintext) -> int:
    score = 0
    for k, value in weight.items():
        if plaintext.find(k) != -1:
            score += value
    return score


cipher_text = 'ktbueluegvitnthuexmonveggmrcgxptlyhhjaogchoemqchpdnetxupbqntietiabpsmaoncnwvoutiugtagmmqsxtvxaoniiogtagmbpsmtuvvihpstpdvcrxhokvhxotawswquunewcgxptlcrxtevtubvewcnwwsxfsnptswtagakvoyyak'
key = ''
key_length = 3

for i in range(0, 26):
    key += chr(i + ord('a'))
    for j in range(0, 26):
        if j == i:
            continue
        key += chr(j + ord('a'))
        for k in range(0, 26):
            if k == i or k == j:
                continue
            key += chr(k + ord('a'))
            position = 0
            e_count = 0
            plain_text = ''
            for cipher_char in cipher_text:
                plain_char = vignere_decrypt(cipher_char, key[position])
                if plain_char == 'e':
                    e_count += 1
                plain_text += plain_char
                position += 1
                position %= key_length
            score = calc_score(plain_text)
            if score >= 2 and e_count >= 20:
                print('key=' + key, end=', ')
                print('e_count=' + str(e_count), end=', ')
                print('pronoun_score=' + str(score), end=' ')
                print(plain_text)
            key = key[:2]
        key = key[:1]
    key = key[:0]
