import math

def gcd(a, h):
    while h != 0:
        a, h = h, a % h
    return a

def mod_inverse(e, phi):
    t, new_t = 0, 1
    r, new_r = phi, e
    while new_r != 0:
        quotient = r // new_r
        t, new_t = new_t, t - quotient * new_t
        r, new_r = new_r, r - quotient * new_r
    if r > 1:
        raise ValueError("e is not invertible")
    if t < 0:
        t = t + phi
    return t

p = int(input("Enter prime number p: "))
q = int(input("Enter prime number q: "))
n = p * q
phi = (p - 1) * (q - 1)

print(f"Calculated totient (phi) = {phi}")

e = int(input("\nEnter value for e (must be co-prime with phi and less than phi): "))
while gcd(e, phi) != 1 or e >= phi:
    e = int(input("Invalid input. Enter value for e (must be co-prime with phi and less than phi): "))

d = mod_inverse(e, phi)

msg = int(input("Enter message to be encrypted: "))
print("Message data =", msg)

c = pow(msg, e, n)
print("Encrypted data =", c)

m = pow(c, d, n)
print("Original Message Sent =", m)