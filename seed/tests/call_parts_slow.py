#!/usr/bin/python

word, ln = raw_input().split()
n = len(word)
ln = min(4 * int(ln), n - 2)

for i in range(0, n - ln, ln / 2):
    print word[i:i + ln]

print word[-ln:]
