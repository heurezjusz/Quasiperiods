#!/usr/bin/python

word, ln = raw_input().split()
n = len(word)
ln = 4 * int(ln)

if ln > n:
    print 0, word
else:
    for i in range(0, n - ln, ln / 2):
        print i, word[i:i + ln]

    print n-ln, word[-ln:]
