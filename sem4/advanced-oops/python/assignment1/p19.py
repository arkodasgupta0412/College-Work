import math
import cProfile

def find_pythagorean_triples_optimized(limit, print_triples=False):
    triples = []
    
    # Iterate over possible values of m and n
    for m in range(2, int(math.sqrt(limit)) + 1):
        for n in range(1, m):  # n must be smaller than m
            if (m - n) % 2 == 1 and math.gcd(m, n) == 1:  # Opposite parity & coprimeness
                a = m**2 - n**2
                b = 2 * m * n
                c = m**2 + n**2
                
                if c > limit:
                    break  # Stop early if c exceeds the limit
                
                k = 1
                while k * c <= limit:  # Generate multiples of the primitive triple
                    triple = (k * a, k * b, k * c)
                    triples.append(triple)
                    
                    if print_triples:  # Print each triple if enabled
                        print(triple)

                    k += 1
                
    return triples

if __name__ == "__main__":
    limit = 1000  # Change limit as needed
    print("Pythagorean Triples up to", limit)
    cProfile.run('find_pythagorean_triples_optimized(limit, print_triples=True)')
