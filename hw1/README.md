# SEC2021-HW1

## Caesar

### decryption result

offset (key): 16
plain text: `PLEASEENCRYPTYOURNAMEWITHTHESAMEKEYANDUPLOADTOLEARNINGINZJU`
human readable version: `PLEASE ENCRYPT YOUR NAME WITH THE SAME KEY AND UPLOAD TO LEARNING IN ZJU`
mission in cipher text: `pxqepysxud`

### cryptanalysis process
1. Write a correct `caesar_decrypt` function, which decrypts a character by inputting it and input the encryption offset.  
2. Loop the offset value, because it has 25 possibilities.  

```python
def caesar_decrypt(char, offset) -> str:
    result = ord(char) - offset
    if result >= ord('A'):
        return chr(result)
    else:
        return chr(result + ord('Z') - ord('A') + 1)


raw = 'FBUQIUUDSHOFJOEKHDQCUMYJXJXUIQCUAUOQDTKFBEQTJEBUQHDYDWYDPZK'

for j in range(1, 26):
    print('offset=' + str(j), end=' ')
    for i in raw:
        print(caesar_decrypt(i, j), end='')
    print('')

```

``` text
---------------------------OUTPUT START-----------------------------
offset=1 EATPHTTCRGNEINDJGCPBTLXIWIWTHPBTZTNPCSJEADPSIDATPGCXCVXCOYJ
offset=2 DZSOGSSBQFMDHMCIFBOASKWHVHVSGOASYSMOBRIDZCORHCZSOFBWBUWBNXI
offset=3 CYRNFRRAPELCGLBHEANZRJVGUGURFNZRXRLNAQHCYBNQGBYRNEAVATVAMWH
offset=4 BXQMEQQZODKBFKAGDZMYQIUFTFTQEMYQWQKMZPGBXAMPFAXQMDZUZSUZLVG
offset=5 AWPLDPPYNCJAEJZFCYLXPHTESESPDLXPVPJLYOFAWZLOEZWPLCYTYRTYKUF
offset=6 ZVOKCOOXMBIZDIYEBXKWOGSDRDROCKWOUOIKXNEZVYKNDYVOKBXSXQSXJTE
offset=7 YUNJBNNWLAHYCHXDAWJVNFRCQCQNBJVNTNHJWMDYUXJMCXUNJAWRWPRWISD
offset=8 XTMIAMMVKZGXBGWCZVIUMEQBPBPMAIUMSMGIVLCXTWILBWTMIZVQVOQVHRC
offset=9 WSLHZLLUJYFWAFVBYUHTLDPAOAOLZHTLRLFHUKBWSVHKAVSLHYUPUNPUGQB
offset=10 VRKGYKKTIXEVZEUAXTGSKCOZNZNKYGSKQKEGTJAVRUGJZURKGXTOTMOTFPA
offset=11 UQJFXJJSHWDUYDTZWSFRJBNYMYMJXFRJPJDFSIZUQTFIYTQJFWSNSLNSEOZ
offset=12 TPIEWIIRGVCTXCSYVREQIAMXLXLIWEQIOICERHYTPSEHXSPIEVRMRKMRDNY
offset=13 SOHDVHHQFUBSWBRXUQDPHZLWKWKHVDPHNHBDQGXSORDGWROHDUQLQJLQCMX
offset=14 RNGCUGGPETARVAQWTPCOGYKVJVJGUCOGMGACPFWRNQCFVQNGCTPKPIKPBLW
offset=15 QMFBTFFODSZQUZPVSOBNFXJUIUIFTBNFLFZBOEVQMPBEUPMFBSOJOHJOAKV
offset=16 PLEASEENCRYPTYOURNAMEWITHTHESAMEKEYANDUPLOADTOLEARNINGINZJU
offset=17 OKDZRDDMBQXOSXNTQMZLDVHSGSGDRZLDJDXZMCTOKNZCSNKDZQMHMFHMYIT
offset=18 NJCYQCCLAPWNRWMSPLYKCUGRFRFCQYKCICWYLBSNJMYBRMJCYPLGLEGLXHS
offset=19 MIBXPBBKZOVMQVLROKXJBTFQEQEBPXJBHBVXKARMILXAQLIBXOKFKDFKWGR
offset=20 LHAWOAAJYNULPUKQNJWIASEPDPDAOWIAGAUWJZQLHKWZPKHAWNJEJCEJVFQ
offset=21 KGZVNZZIXMTKOTJPMIVHZRDOCOCZNVHZFZTVIYPKGJVYOJGZVMIDIBDIUEP
offset=22 JFYUMYYHWLSJNSIOLHUGYQCNBNBYMUGYEYSUHXOJFIUXNIFYULHCHACHTDO
offset=23 IEXTLXXGVKRIMRHNKGTFXPBMAMAXLTFXDXRTGWNIEHTWMHEXTKGBGZBGSCN
offset=24 HDWSKWWFUJQHLQGMJFSEWOALZLZWKSEWCWQSFVMHDGSVLGDWSJFAFYAFRBM
offset=25 GCVRJVVETIPGKPFLIERDVNZKYKYVJRDVBVPREULGCFRUKFCVRIEZEXZEQAL
----------------------------OUTPUT END-------------------------------
```
It is obvious that `offset=16` is correct.  



## Vignere

### decryption result

key: `cat`
plain text: `itisessentialtoseekoutenemyagentswhohavecometoconductespionageagainstyouandtobribethemtoserveyougivetheminstructionsandcareforthemthusdoubledagentsarerecruitedandusedsuntzutheartofwar`
human readable version: `it is essential to seek out enemy agents who have come to conduct espionage against you / and to bribe them to serve you / give them instructions and care for them / thus doubled agents are recruited and used / sun tzu / theart of war`

### cryptanalysis process

1. We have to solve this problem by *brute force*.  
2. Try every cipher key which has 1 byte, 2 bytes and 3 bytes, and so on.  
3. After decrypted a cipher text, score it by the following two method:  
    1. Search for some of the sub-strings in the plain text, while the sub-strings are the pronouns in English. These pronouns are stored in a map, while the values of each pronoun key is a integer score. If a pronoun hits, then the plain text gain the according score of this pronoun.  
    2. Analise the appearance of character `e` in the plaint text. 
4. After processed the two method mentioned above, set a proper threshold for each of them. Currently, the threshold of the first method is `>= 2`, and the second is `>= 20`.  

Note: the following code only shows the condition of 3-byte-key. The code of other conditions are similar to this.  
```python
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

```

```text
---------------------------OUTPUT START-----------------------------
key=cat, e_count=26, pronoun_score=3 itisessentialtoseekoutenemyagentswhohavecometoconductespionageagainstyouandtobribethemtoserveyougivetheminstructionsandcareforthemthusdoubledagentsarerecruitedandusedsuntzutheartofwar
key=cjt, e_count=20, pronoun_score=2 ikisvssvntzalkosvekfutvnedyaxenkswyohrvetomvtotonuuckesgioeagvagrinjtyfuaedtfbrzbekhedtojermeyfugzvekhedinjtrlctzonjanucaieffrtyemkhujdolblvdaxenksaiervcrlitvdaedujedjunkzukherrtffwrr
key=ckt, e_count=23, pronoun_score=2 ijisussuntyaljosuekeutunecyawenjswxohqvesomutosontucjesfiodaguagqinityeuaddtebrybejhectoierleyeugyvejhecinitrkctyoniantcahefertxemjhuidokbludawenjsaherucrkitudadduiediunjzujheqrtefwqr
key=dat, e_count=20, pronoun_score=2 htiresrensiaktoreejousendmyzgemtsvhogavdcoletncomdubterpinnafeafaimstxouzndsobqibdthdmtnseqvexoufivdthdmimstqucsiomsamdczreeorshelthtsdnubkedzgemtszreqecquisedzndtsecsumtztthdarsofvar
key=eot, e_count=20, pronoun_score=2 gfiqqsqqnruajfoqqeiaurqncyyyselfsutofmvcookqtmoolpuafeqbimzaeqaemiletwauyzdrabpubcfhcytmeephewaueuvcfhcyiletpgcruolealpcydedarrtekfhsedmgbjqdyselfsydepqcpgirqdyzdseebeulfzsfhcmrrafumr
key=iat, e_count=20, pronoun_score=4 ctimesmenniaftomeeeounenymyugehtsqhobavycogeticohduwtempiinaaeaaaihstsouundnoblibythymtiselvesouaivythymihstlucniohsahdcurezornhegthosdiubfedugehtsurelecluinedundosexsuhtzothyarnofqar
key=lag, e_count=20, pronoun_score=2 ztvjefjeakinctbjerbohkeavmlrgretfnhbyaivcbdegfcbedhttrjpvfnnxenxavesgpohrnqkooiiovtuvmgfsrivrpohxiivtuvmvesgiupkibesnedprrrwoekhrdtulsqfuoceqrgretfrrriepiuvkeqrnqlsrushetmltuvaekosnae
key=qkt, e_count=20, pronoun_score=2 ujieuseunfyaxjoeueweufunqcymwezjsixotqvqsoyutasoztuojeefiadasuasqizitkeumddfebdybqjhqctaiedlekeusyvqjhqcizitdkcfyoziaztcmhererfxeyjhgidakbxudmwezjsmheducdkifudmddgiepiuzjzgjhqqrfefiqr
key=rwt, e_count=21, pronoun_score=2 txidisdinemawxodievsueinpqylkeyxshlosevpgoxitzgoyhunxedtizrariareiywtjsulrdesbcmbpxhpqtzweczejsurmvpxhpqiywtcycemoywayhclveqsrelexxhfwdzybwidlkeyxslveciccyieidlrdfweowuyxzfxhperesfher
----------------------------OUTPUT END------------------------------
```
The first output get the best score. It has the highest `e_count`, while scores 3 in `pronoun_score`.  



## Unknown

### substitution table
```python
# the substitution table is written in JSON format
# the key is cipher text
# the value is plain text

---------------JSON START----------------
{
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
----------------JSON END-----------------
```

plain text: `THE PASSWORD IS THE SURNAME OF THE MAN WHO SAID THE HIGHEST KNOWLEDGE IS TO KNOW THAT WE ARE SURROUNDED BY MYSTERY`

### cryptanalysis process

1. `MAL` appears multiple times in the cipher text, which means the encryption procedure of each character is *independent* (have no relation to the context).  
2. In English, the three-letter-word that appears most frequently is `THE`. Let's assume the plain text of `MAL` is `THE`.  
3. Then, many of the `T`, `H` and `E` in the sentence reveals. So we can guess more things based on the new information.  
4. Keep guessing until we successfully decrypt it.  

Note: The following code performs the way I try to guess the encryption relation. The code shows the status that I have already guessed almost half of the cipher text.  

```python
decrypt_table = {
    'M': 'T',
    'A': 'H',
    'L': 'E',
    'R': 'S',
    'C': 'I',
    'W': 'G',
    'I': 'A',
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

```

```text
---------------------------OUTPUT START-----------------------------
MAL TIRRUEZF CR MAL RKZYIOL EX MAL OIY UAE RICF MAL ACWALRM DYEUPLFWL CR ME DYEU MAIM UL IZL RKZZEKYFLF GH OHRMLZH
THE ?ASS???? IS THE S???A?E ?? THE ?A? ?H? SAI? THE HIGHEST ?????E?GE IS T? ???? THAT ?E A?E S???????E? ?? ??STE??
----------------------------OUTPUT END------------------------------
```