def get_differences(mat1, mat2):
    d = len(mat1)
    r = len(mat1[0])
    c = len(mat1[0][0])

    d1 = [[[0] * c for _ in range(r)] for _ in range(d)]
    d2 = [[[0] * c for _ in range(r)] for _ in range(d)]
    gap = [[[0] * c for _ in range(r)] for _ in range(d)]
    net = [[[0] * c for _ in range(r)] for _ in range(d)]
    now = [[0] * c for _ in range(r)]

    for z in range(1, d):
        for i in range(r):
            for j in range(c):
                d1[z][i][j] = mat1[z][i][j] - mat1[z-1][i][j]
                d2[z][i][j] = mat2[z][i][j] - mat2[z-1][i][j]
                gap[z][i][j] = d1[z][i][j] - d2[z][i][j]

    for i in range(r):
        for j in range(c):
            now[i][j] = mat1[0][i][j] - mat2[0][i][j]
            net[0][i][j] = now[i][j]

    for z in range(1, d):
        for i in range(r):
            for j in range(c):
                now[i][j] += gap[z][i][j]
                net[z][i][j] = now[i][j]

    return d1, d2, net

def input_matrix(d, r, c):
    mat = []
    for z in range(d):
        part = []
        print(f"Slice {z + 1}:")
        for i in range(r):
            row = list(map(int, input().split()))
            part.append(row)
        mat.append(part)
    return mat

def show(mat, title):
    print(f"\n{title}: {mat}")

def run():
    d = int(input("Slices: "))
    r = int(input("Rows: "))
    c = int(input("Cols: "))

    print("Matrix A:")
    a = input_matrix(d, r, c)
    print("Matrix B:")
    b = input_matrix(d, r, c)

    x, y, z = get_differences(a, b)
    show(a, "A")
    show(b, "B")
    show(x, "Delta A")
    show(y, "Delta B")
    show(z, "Net Diff")

run()
