class CustomString:
    def __init__(self, text):
        self.text = text
        self.words = text.split()
    
    def __len__(self):
        word_counts = {}
        for word in self.words:
            word_counts[word] = word_counts.get(word, 0) + 1
        repetitive_words = {word: count for word, count in word_counts.items() if count > 1}
        return len(self.text) if not repetitive_words else sum(repetitive_words.values())
    
    def most_common_words(self, n=1):
        word_counts = {}
        for word in self.words:
            word_counts[word] = word_counts.get(word, 0) + 1
        sorted_words = sorted(word_counts.items(), key=lambda x: x[1], reverse=True)
        return sorted_words[:n]

text = input("Enter text: ")
custom_str = CustomString(text)
print("Length:", len(custom_str))
n = int(input("Enter number of most common words to display: "))
print("Most common words:", custom_str.most_common_words(n))
