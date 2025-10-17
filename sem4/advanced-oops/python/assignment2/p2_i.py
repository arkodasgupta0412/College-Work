def compute_prefix_sums(nums):
    n = len(nums)
    prefix_sums = [0] * n
    prefix_sums[0] = nums[0]
    for i in range(1, n):
        prefix_sums[i] = prefix_sums[i - 1] + nums[i]
    return prefix_sums

def process_queries(prefix_sums, query_ranges):
    for left, right in query_ranges:
        if left == 0:
            result = prefix_sums[right]
        else:
            result = prefix_sums[right] - prefix_sums[left - 1]
        print(result)

def main():
    n = int(input("Enter the size of the array (n): "))
    nums = list(map(int, input(f"Enter {n} elements: ").split()))

    q = int(input("Enter the number of queries (q): "))
    query_ranges = []
    print(f"Enter {q} queries as pairs (left right):")
    for _ in range(q):
        left, right = map(int, input().split())
        query_ranges.append((left, right))

    prefix_sums = compute_prefix_sums(nums)
    process_queries(prefix_sums, query_ranges)

if __name__ == "__main__":
    main()