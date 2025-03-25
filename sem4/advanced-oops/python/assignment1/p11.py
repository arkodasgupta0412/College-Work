class TextProcessor:
    def __init__(self, text):
        self.words = text.lower().split()
    
    def find_palindromes(self):
        return [word for word in self.words if word == word[::-1]]
    
    def find_unique_words(self):
        return list(set(self.words))

text = input()
processor = TextProcessor(text)
print("Palindromes:", processor.find_palindromes())
print("Unique words:", processor.find_unique_words())
