def compute_wer(ref: str, hyp: str) -> float:
    
    R = ref.strip().split()  
    H = hyp.strip().split()

    m = len(R)
    n = len(H)
    
    prev = list(range(n + 1))  
    cur = [0] * (n + 1)
    for i in range(1, m + 1):
        cur[0] = i  
        for j in range(1, n + 1):
            cost = 0 if R[i - 1] == H[j - 1] else 1
            cur[j] = min(prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + cost)
        
        prev, cur = cur, prev

    wer = prev[n] / m  
    return wer

def main():
    ref = input("Enter reference sentence: ")
    hyp = input("Enter hypothesis sentence: ")
    wer = compute_wer(ref, hyp)
    print(f"Word Error Rate (WER): {wer:.4f}")

if __name__ == "__main__":
    main()
