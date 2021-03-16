decrypt_table = {
    'M': 'T',
    'A': 'H',
    'L': 'E',
    'R': 'S',
    'C': 'I',
    'W': 'G',
    'I': 'A',
    'Z': 'R',
    'F': 'D',
    'E': 'O',
    'T': 'P',
    'U': 'W',
    'K': 'U',
    'Y': 'N',
    'G': 'B',
    'H': 'Y',
    'O': 'M',
    'D': 'K',
    'P': 'L',
    'X': 'F',
}


def decrypt(char) -> str:
    if char == ' ':
        return ' '
    for enc, dec in decrypt_table.items():
        if enc == char:
            return dec
    return '?'


cipher_text = 'MAL TIRRUEZF CR MAL RKZYIOL EX MAL OIY UAE RICF MAL ACWALRM DYEUPLFWL CR ME DYEU MAIM UL IZL RKZZEKYFLF GH OHRMLZH'

print(cipher_text)

for cipher_char in cipher_text:
    print(decrypt(cipher_char), end='')
print('')
