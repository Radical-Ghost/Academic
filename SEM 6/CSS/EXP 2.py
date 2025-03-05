def encrypt(text, shift):   
    encrypted_text  = ''    
    for i in range(0, len(text)):    
        if text[i] == " ":
            encrypted_text += " "
        elif text[i].isupper():
            encrypted_text += chr(((ord(text[i]) - 65 + shift) % 26) + 65)
        else:
            encrypted_text += chr(((ord(text[i]) - 97 + shift) % 26) + 97)

    return encrypted_text

def decrypt(text, shift):
    decrypted_text = ''
    for i in range(0, len(text)):  
        if ord(text[i]) == 32:
            decrypted_text += " "
        elif text[i].isupper():
            decrypted_text += chr(((ord(text[i]) - 65 - shift) % 26) + 65)
        else:
            decrypted_text += chr(((ord(text[i]) - 97 - shift) % 26) + 97)
    return decrypted_text

def main():
    text = input("Enter text to be encrypted: ")
    shift = int(input("Enter value of shift for the cipher: "))
    shift = shift % 26

    encrypted_text = encrypt(text, shift)
    decrypted_text = decrypt(encrypted_text, shift)

    print(f"Encrypted Text: {encrypted_text}\nDecrypted Text: {decrypted_text}")

main()  
