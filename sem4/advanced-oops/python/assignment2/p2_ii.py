def build_prefix_sum(matrix, rows, cols):
    dp = [[0] * (cols + 1) for _ in range(rows + 1)]

    for r in range(1, rows + 1):
        for c in range(1, cols + 1):
            dp[r][c] = (
                matrix[r - 1][c - 1]
                + dp[r - 1][c]
                + dp[r][c - 1]
                - dp[r - 1][c - 1]
            )
    return dp


def handle_queries(dp, queries):
    for r1, c1, r2, c2 in queries:
        r1 += 1
        c1 += 1
        r2 += 1
        c2 += 1

        sub_sum = (
            dp[r2][c2]
            - dp[r1 - 1][c2]
            - dp[r2][c1 - 1]
            + dp[r1 - 1][c1 - 1]
        )
        print(sub_sum)


def main():
    rows, cols = map(int, input("Enter m and n: ").split())
    print("Enter row-wise:")
    matrix = [list(map(int, input().split())) for _ in range(rows)]

    q = int(input("Enter number of queries: "))
    print("Enter queries:")
    queries = [tuple(map(int, input().split())) for _ in range(q)]

    dp = build_prefix_sum(matrix, rows, cols)
    handle_queries(dp, queries)


if __name__ == "__main__":
    main()

