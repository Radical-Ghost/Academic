import random

bits = [0, 1]

# key = [random.choice(bits)for _ in range(64)]
KEY = [0, 1, 0, 1, 0, 0, 0, 1, 
        0, 0, 0, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        1, 1, 0, 1, 0, 0, 0, 0, 
        1, 0, 1, 1, 1, 1, 0, 1, 
        0, 1, 1, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 1, 1, 1, 0, 0, 1]

IP = [47, 12, 60, 6, 35, 37, 16, 63, 
      26, 7, 57, 29, 40, 39, 23, 34, 
      24, 27, 0, 28, 42, 45, 21, 48, 
      13, 2, 33, 32, 1, 5, 22, 44, 
      30, 43, 58, 62, 25, 50, 59, 3, 
      46, 17, 20, 10, 11, 51, 41, 38, 
      19, 4, 53, 18, 61, 36, 54, 52, 
      8, 9, 55, 14, 31, 56, 49, 15]

PC_1 = [
    8, 29, 50, 18, 13, 30, 51, 36, 
    2, 43, 32, 45, 55, 59, 26, 22, 
    20, 38, 17, 39, 41, 23, 37, 6, 
    54, 35, 5, 16, 58, 60, 44, 47, 
    10, 42, 9, 24, 62, 34, 49, 3,
    14, 63, 25, 7, 48, 28, 15, 52, 
    61, 56, 46, 33, 11, 31, 21, 27, 
    4, 0, 53, 57, 19, 1, 12, 40]

PC_2 = [
    38, 51, 8, 0, 17, 9, 46, 52, 
    26, 40, 30, 48, 50, 16, 21, 4, 
    34, 53, 11, 36, 25, 19, 63, 28, 
    56, 23, 39, 61, 3, 1, 12, 41, 
    18, 2, 6, 37, 5, 62, 60, 49, 
    15,42, 59, 10, 27, 54, 31, 32, 
    55, 33, 14, 7, 24, 13, 35, 47, 
    43, 22, 44, 57, 20, 45, 58, 29]

def initial_permutation(plain_text):
    permuted = [0] * 64
    
    for i in range(64):
        permuted[i] = plain_text[IP[i] - 1]

    return permuted

def Permutation_choice_1():
    KEY_PC_1 = [0] * 56
    
    for i in range(56):
        KEY_PC_1[i] = KEY[PC_1[i] - 1]

    return KEY_PC_1

def Permutation_choice_2(key):
    KEY_PC_2 = [0] * 48
    
    for i in range(48):
        KEY_PC_2[i] = key[PC_2[i] - 1]

    return KEY_PC_2

def Left_Circular_Shift(key):
    return key[1:] + key[:1]

def expand_2nd_half(permuted_text):
    expanded = []
    expansion_table = [31, 0, 1, 2, 3, 4, 3, 4, 
                       5, 6, 7, 8, 7, 8, 9, 10, 
                       11, 12, 11, 12, 13, 14, 15, 16, 
                       15, 16, 17, 18, 19, 20, 19, 20, 
                       21, 22, 23, 24, 23, 24, 25, 26, 
                       27, 28, 27, 28, 29, 30, 31, 21]
    
    for index in expansion_table:
        expanded.append(permuted_text[index % len(permuted_text)])

    return expanded

def perform_XOR(permuted_half, permuted_key_2):
    for i in range(48):
        permuted_half[i] = permuted_half[i] ^ permuted_key_2[i]
    
    return permuted_half
      
def Bit_Swap(plain_text):
    pass

def Des(plain_text):
    permuted_text = initial_permutation(plain_text) #inital permutation of plain text (64 bits) 
    permuted_key_1 = Permutation_choice_1() #Permuted Choice 1 for key (56 bits)

    for i in range(1, 17):
        permuted_key_1 = Left_Circular_Shift(permuted_key_1) #left circular shift (56 bits)
        permuted_key_2 = Permutation_choice_2(permuted_key_1) #permuted choice 2 for key (48 bits)

        permuted_half = expand_2nd_half(plain_text[32:])
        permuted_text = perform_XOR(permuted_half, permuted_key_2)
        permuted_text = Bit_Swap(permuted_text)

    return permuted_text

def main():
    # plain_text = [[random.choice(bits) for _ in range(8)] for _ in range(8)]
    
    plain_text = [1, 1, 0, 1, 1, 0, 0, 0, 
                  0, 1, 1, 1, 0, 0, 1, 0, 
                  0, 0, 1, 1, 0, 0, 0, 1, 
                  1, 1, 1, 1, 0, 0, 0, 1, 
                  1, 1, 0, 0, 0, 1, 1, 1, 
                  0, 1, 0, 0, 0, 0, 1, 1, 
                  1, 1, 1, 1, 1, 0, 0, 1, 
                  1, 0, 1, 1, 0, 1, 1, 0]

    Cipher_text = Des(plain_text)

    print(f"Final Cipher Text: ")
    counter = 0
    for i in range(64):
        print(plain_text[i], end=" ")
        counter += 1
        if counter == 8:
            print("\n", end="")
            counter = 0

main()