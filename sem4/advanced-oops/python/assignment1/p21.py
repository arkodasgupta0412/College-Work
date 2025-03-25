import re

# Mapping for number words
ones = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
teens = ["ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]
tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

def number_to_words(n):
    if n == 0:
        return "zero"
    
    words = []

    if n >= 1000:
        words.append(ones[n // 1000] + " thousand")
        n %= 1000

    if n >= 100:
        words.append(ones[n // 100] + " hundred")
        n %= 100
        if n > 0:
            words.append("and")

    if n >= 20:
        words.append(tens[n // 10])
        n %= 10

    elif n >= 10:
        words.append(teens[n - 10])
        n = 0

    if n > 0:
        words.append(ones[n])

    return " ".join(words)

def convert_numbers_to_words(text):
    def replace_number(match):
        number = int(match.group())
        return number_to_words(number)

    return re.sub(r'\b\d+\b', replace_number, text)

def main():
    file_path = input("Enter the file name: ").strip()

    try:
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()

        converted_text = convert_numbers_to_words(content)

        print("\nModified Text:\n")
        print(converted_text)

    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")

if __name__ == "__main__":
    main()
