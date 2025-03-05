def digraph(plain_text):
    plain_text = plain_text.upper().replace(" ", "")
    p_len = len(plain_text)
    
    digraph_text = []
    i = 0
    while(i < p_len):
        if i+1 < p_len and plain_text[i] == plain_text[i+1]:
            digraph_text.append(plain_text[i] + "X")
            i += 1
        else: 
            digraph_text.append(plain_text[i] + (plain_text[i+1] if i+1 < p_len else "X"))
            i += 2
        
    return digraph_text
        
def key_matrix(key):
    key_mat = []
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"

    key_temp = set()
    for i in key:
        if i not in key_temp:
            key_temp.add(i)
            key_mat.append(i)
    
    for i in alphabet:
        if i not in key_temp:
            key_temp.add(i)
            key_mat.append(i)
            
    key_mat = [key_mat[i:i+5] for i in range(0, 25, 5)]
    print("Matrix: ")
    for i in range(5):
        for j in range(5):
            print(key_mat[i][j], end=' ')
        print("\n")
        
    return key_mat

def find_pos(key_mat, alphabet):
    for i in range(5):
        if alphabet in key_mat[i]:
            return i, key_mat[i].index(alphabet)

def encryption(key_mat, digraph_text):
    encrypted_text = []
    for i in digraph_text:
        row1, col1 = find_pos(key_mat, i[0])
        row2, col2 = find_pos(key_mat, i[1])

        if row1 == row2:
            encrypted_text.append(key_mat[row1][(col1 + 1)  % 5] + key_mat[row1][(col2 + 1) % 5])
        elif col1 == col2:
            encrypted_text.append(key_mat[(row1 + 1) % 5][col1] + key_mat[(row2 + 1) % 5][col1])
        else:
            encrypted_text.append(key_mat[row1][col2] + key_mat[row2][col1])
    
    print(f"Encrypted Text: {''.join(encrypted_text)}")
    return encrypted_text

def decryption(key_mat, encrypted_text):
    decrypted_text = []
    for i in encrypted_text:
        row1, col1 = find_pos(key_mat, i[0])
        row2, col2 = find_pos(key_mat, i[1])

        if row1 == row2:
            decrypted_text.append(key_mat[row1][(col1 - 1)  % 5] + key_mat[row1][(col2 - 1) % 5])
        elif col1 == col2:
            decrypted_text.append(key_mat[(row1 - 1) % 5][col1] + key_mat[(row2 - 1) % 5][col1])
        else:
            decrypted_text.append(key_mat[row1][col2] + key_mat[row2][col1])

    print(f"Decrypted Text: {''.join(decrypted_text)}")

def main():
    plain_text = input("Enter plaintext: ")
    key = input("Enter Key: ")
    
    plain_text = plain_text.upper().replace("J", "I")
    key = key.upper().replace("J", "I")
    
    digraph_text =  digraph(plain_text)
    key_mat = key_matrix(key)
    
    encrypted_text = encryption(key_mat, digraph_text)
    decryption(key_mat, encrypted_text)

main()