def get_largest_n(numbers, n):
    return sorted(numbers, reverse=True)[:n]

def get_smallest_n(numbers, n):
    return sorted(numbers)[:n]

def main():
    numbers = list(map(int, input("Enter numbers separated by space: ").split()))
    n = int(input("Enter N: "))
    
    print("Largest N items:", get_largest_n(numbers, n))
    print("Smallest N items:", get_smallest_n(numbers, n))

if __name__ == "__main__":
    main()
