import math 

def print_table(key, block_size, row, columnar):
    for c in range(block_size):
        print(f"{key[c]}", end="\t")

    print("<-- Position for Cipher\n")

    for c in range(block_size):
        print("-------", end="")
    
    print("\n")
    
    for r in range(row):
        for c in range(block_size):
            print(f"{columnar[r][c]}\t", end='')
        if r == 0:
            print("<-- Columnar Transposition Matrix", end='')
        print("\n")

def encryption(plain_text, key, block_size):
    cipher = ''
    plain_text = plain_text.replace(" ", "").lower()

    counter = 0
    plain_text_length = len(plain_text)
    row = math.ceil(plain_text_length / block_size)
    
    columnar = [['' for _ in range(block_size)] for _ in range(row)]

    for r in range(row):
        for c in range(block_size):
            if counter < plain_text_length:
                columnar[r][c] += plain_text[counter]
                counter += 1
            else:
                columnar[r][c] += 'x'
            
    counter = 0
    while(counter < block_size):
        for r in range(row):
            cipher += columnar[r][key[counter]-1]
        counter += 1

    new_key = [None for _ in range(block_size)]
    counter = 0
    while(counter < block_size):
        new_key[key[counter]-1] = counter + 1
        counter += 1

    print("\nEncryption: \n")
    print_table(new_key, block_size, row, columnar)
    print(f"\nCipher: {cipher}")
            
    return cipher

def decryption(cipher, key, block_size):
    plain_text = ''
    cipher = cipher.replace(" ", "").lower()

    counter = 0
    cipher_length = len(cipher)
    row = math.ceil(cipher_length / block_size)
    
    columnar = [['' for _ in range(block_size)] for _ in range(row)]

    counter = 0
    cipher_counter = 0
    while(counter < block_size):
        for r in range(row):
            columnar[r][key[counter]-1] += cipher[cipher_counter]
            cipher_counter += 1
        counter += 1

    for r in range(row):
        for c in range(block_size):
            plain_text += columnar[r][c]

    new_key = [None for _ in range(block_size)]
    counter = 0
    while(counter < block_size):
        new_key[key[counter]-1] = counter + 1
        counter += 1

    print("\n\nDecryption: \n")
    print_table(new_key, block_size, row, columnar)
    print(f"\nPlain Text: {plain_text}")

def main():
    plain_text = input("Enter plain text to be encrypted: ")
    key = input("Enter the key to be used (in numbers): ").split()
    for i in range(len(key)):
        key[i] = int(key[i])
    block_size = len(key)
    
    cipher = encryption(plain_text, key, block_size)
    decryption(cipher, key, block_size)
    
main()