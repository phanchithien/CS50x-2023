from cs50 import *

text = get_string("Text:")

words = 1
letters = 0
sentences = 0

for c in text:
    if c.isalpha():
        letters += 1
    elif c.isspace():
        words += 1
    elif c == "." or c == "?" or c == "!":
        sentences += 1

L = float(letters) / float(words) * 100
S = float(sentences) / float(words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

else:
    print("Grade", index)
