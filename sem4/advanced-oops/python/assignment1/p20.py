def tokenize_and_map(lines):
    token_dict = {}
    tokenized_lines = []
    max_length = 0

    for line in lines:
        tokens = line.strip().split()
        tokenized_line = []
        
        for token in tokens:
            if token not in token_dict:
                token_dict[token] = len(token_dict) + 1
            
            tokenized_line.append(token_dict[token])

        tokenized_lines.append(tokenized_line)
        max_length = max(max_length, len(tokenized_line))

    return tokenized_lines, token_dict, max_length


def pad_lines(tokenized_lines, max_length, pad_value=0):
    return [line + [pad_value] * (max_length - len(line)) for line in tokenized_lines]


def main():
    print("Enter lines of text (enter a blank line to stop):")
    lines = []
    
    while True:
        line = input().strip()
        if line == "":
            break
        lines.append(line)

    tokenized_lines, token_dict, max_length = tokenize_and_map(lines)
    padded_lines = pad_lines(tokenized_lines, max_length)

    print("\nTokenized and Padded Lines:")
    for line in padded_lines:
        print(" ".join(map(str, line)))

    print("\nToken Dictionary:")
    for token, num in token_dict.items():
        print(f"'{token}': {num}")

    print(f"\nAll lines are now of length {max_length}.")

if __name__ == "__main__":
    main()
