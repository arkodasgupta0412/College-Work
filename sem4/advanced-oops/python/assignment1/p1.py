n = int(input("Enter a number: "))
sieve = [1] * (n+1)
sieve[0], sieve[1], i = 0, 0, 2

# sieve of EratosThenes
while (i * i <= n):
    if (sieve[i]):
        j = i * i
        while (j <= n):
            sieve[j] = 0
            j += i
    i += 1
    
print("Prime numbers <= ",n,":");
for i in range(n+1):
    if (sieve[i]):
        print(i, end=', ')