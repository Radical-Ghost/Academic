def encryption(plain_text, key):
    plain_text = plain_text.replace(" ", "")
    num_cols = len(plain_text)
    
    fence = [['' for _ in range(num_cols)] for _ in range(key)]
    fence_row = 0
    direction = 1

    for i, char in enumerate(plain_text):
        fence[fence_row][i] = char
        fence_row += direction
        if fence_row == 0 or fence_row == key - 1:
            direction *= -1

    print("\nEncryption: \nRail Fence: \n")
    for row in fence:
        print("\t".join(row))
        print("\n")

    cipher = ''.join([''.join(row) for row in fence])
    print(f"Cipher: {cipher}")
    return cipher

def decryption(cipher, key):
    num_cols = len(cipher)
    fence = [['' for _ in range(num_cols)] for _ in range(key)]
    fence_row = 0
    direction = 1

    for i in range(num_cols):
        fence[fence_row][i] = '*'
        fence_row += direction
        if fence_row == 0 or fence_row == key - 1:
            direction *= -1

    index = 0
    for row in range(key):
        for col in range(num_cols):
            if fence[row][col] == '*':
                fence[row][col] = cipher[index]
                index += 1

    print("\nDecryption: \nRail Fence: \n")
    for row in fence:
        print("\t".join(row))
        print("\n")

    plain_text = ''
    fence_row = 0
    direction = 1

    for i in range(num_cols):
        plain_text += fence[fence_row][i]
        fence_row += direction
        if fence_row == 0 or fence_row == key - 1:
            direction *= -1
    
    print(f"Decrypted Code: {plain_text}")

def main():
    plain_text = input("Enter plaintext: ")
    key = int(input("Enter Key: "))
    
    cipher = encryption(plain_text, key)
    decryption(cipher, key)
    
main()