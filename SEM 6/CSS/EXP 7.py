import random

class DES:
    def __init__(self, key):
        self.bits = [0, 1]
        self.KEY = key
        self.IP = [     47, 12, 60, 6, 35, 37, 16, 63, 
                        26, 7, 57, 29, 40, 39, 23, 34, 
                        24, 27, 0, 28, 42, 45, 21, 48, 
                        13, 2, 33, 32, 1, 5, 22, 44, 
                        30, 43, 58, 62, 25, 50, 59, 3, 
                        46, 17, 20, 10, 11, 51, 41, 38, 
                        19, 4, 53, 18, 61, 36, 54, 52, 
                        8, 9, 55, 14, 31, 56, 49, 15]
        self.PC_1 = [   8, 29, 50, 18, 13, 30, 51, 36, 
                        2, 43, 32, 45, 55, 59, 26, 22, 
                        20, 38, 17, 39, 41, 23, 37, 6, 
                        54, 35, 5, 16, 58, 60, 44, 47, 
                        10, 42, 9, 24, 62, 34, 49, 3,
                        14, 63, 25, 7, 48, 28, 15, 52, 
                        61, 56, 46, 33, 11, 31, 21, 27, 
                        4, 0, 53, 57, 19, 1, 12, 40]
        self.PC_2 = [   35, 52, 50, 4, 3, 22, 10, 34, 
                        24, 29, 6, 55, 53, 26, 39, 28, 
                        12, 19, 11, 0, 13, 14, 32, 21, 
                        37, 45, 33, 18, 49, 48, 20, 16, 
                        2, 27, 40, 25, 5, 43, 44, 42, 
                        31, 17, 38, 47, 51, 9, 1, 15]

    def print_matrix(self, matrix, row_length=8):
        """Prints a matrix in a readable format."""
        counter = 0
        for i in range(len(matrix)):
            print(matrix[i], end=" ")
            counter += 1
            if counter == row_length:
                print()
                counter = 0

    def initial_permutation(self, plain_text):
        """Performs the initial permutation on the plain text."""
        return [plain_text[self.IP[i] - 1] for i in range(64)]

    def permutation_choice_1(self):
        """Performs the first permutation choice on the key."""
        return [self.KEY[self.PC_1[i] - 1] for i in range(56)]

    def permutation_choice_2(self, key):
        """Performs the second permutation choice on the key."""
        return [key[self.PC_2[i] - 1] for i in range(48)]

    def left_circular_shift(self, key, shifts=1):
        """Performs a left circular shift on the key."""
        return key[shifts:] + key[:shifts]

    def expand_2nd_half(self, permuted_text):
        """Expands the second half of the permuted text."""
        expansion_table = [ 31, 0, 1, 2, 3, 4, 3, 4, 
                            5, 6, 7, 8, 7, 8, 9, 10, 
                            11, 12, 11, 12, 13, 14, 15, 16, 
                            15, 16, 17, 18, 19, 20, 19, 20, 
                            21, 22, 23, 24, 23, 24, 25, 26, 
                            27, 28, 27, 28, 29, 30, 31, 21]
        return [permuted_text[index % len(permuted_text)] for index in expansion_table]

    def contract_2nd_half(self, permuted_half):
        """Contracts the second half of the permuted text."""
        contraction_table = [   5, 6, 19, 20, 28, 11, 27, 16, 
                                0, 14, 22, 25, 4, 17, 30, 9, 
                                1, 7, 23, 13, 31, 26, 2, 8, 
                                18, 12, 29, 5, 21, 10, 3, 24]
        return [permuted_half[index % len(permuted_half)] for index in contraction_table]

    def perform_XOR(self, permuted_half, permuted_key_2):
        """Performs XOR operation between permuted half and permuted key."""
        return [permuted_half[i] ^ permuted_key_2[i] for i in range(48)]

    def encrypt(self, plain_text):
        """Performs the DES encryption algorithm."""
        permuted_text = self.initial_permutation(plain_text)
        permuted_key_1 = self.permutation_choice_1()

        for i in range(1, 17):
            print(f"\n\nRound {i}:")
            shifted_key = self.left_circular_shift(permuted_key_1)
            permuted_key_2 = self.permutation_choice_2(shifted_key)

            print(f"Permuted Key for Round {i}:")
            self.print_matrix(permuted_key_2, 8)

            permuted_half = self.expand_2nd_half(permuted_text[32:])
            permuted_half = self.perform_XOR(permuted_half, permuted_key_2)

            print(f"\nPermuted 2nd Half for Round {i}:")
            self.print_matrix(permuted_half, 8)

            permuted_half = self.contract_2nd_half(permuted_half)
            permuted_text = permuted_half + permuted_text[:32]

            print(f"\nOutput of Round {i}:")
            self.print_matrix(permuted_text, 8)

        return permuted_text

def main():
    plain_text = [  1, 1, 0, 1, 1, 0, 0, 0, 
                    0, 1, 1, 1, 0, 0, 1, 0, 
                    0, 0, 1, 1, 0, 0, 0, 1, 
                    1, 1, 1, 1, 0, 0, 0, 1, 
                    1, 1, 0, 0, 0, 1, 1, 1, 
                    0, 1, 0, 0, 0, 0, 1, 1, 
                    1, 1, 1, 1, 1, 0, 0, 1, 
                    1, 0, 1, 1, 0, 1, 1, 0]
    
    # key = [random.choice(bits)for _ in range(64)]
    KEY = [         0, 1, 0, 1, 0, 0, 0, 1, 
                    0, 0, 0, 1, 1, 1, 1, 0, 
                    0, 0, 0, 0, 1, 1, 0, 0, 
                    1, 1, 0, 1, 0, 0, 0, 0, 
                    1, 0, 1, 1, 1, 1, 0, 1, 
                    0, 1, 1, 0, 1, 1, 1, 1, 
                    1, 1, 1, 1, 0, 1, 0, 1, 
                    0, 0, 1, 1, 1, 0, 0, 1]

    des = DES(KEY)

    print("Plain Text:")
    des.print_matrix(plain_text, 8)

    cipher_text = des.encrypt(plain_text)

    print("\n\nFinal Cipher Text:")
    des.print_matrix(cipher_text, 8)

main()