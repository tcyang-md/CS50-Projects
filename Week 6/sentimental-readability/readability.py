# TODO
import cs50

text = cs50.get_string("Text: ")

char_count = 0
word_count = len(text.split())
sentence_count = 0

for char in text:
    if char.isalpha():
        char_count += 1

for char in text:
    if char == '.' or char == '?' or char == "!":
        sentence_count += 1

L = float(char_count / float(word_count / 100))
S = float(sentence_count / float(word_count / 100))
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
