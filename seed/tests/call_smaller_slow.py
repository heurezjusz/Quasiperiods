#!/usr/bin/python

word, ln = raw_input().split()
ln = int(ln)
n = len(word)

s = set()
chosen = ['.'] * n

for i in range(n - ln + 1):
    if word[i:i + ln] in s:
        continue
    s.add(word[i:i + ln])
    for x in range(i, i + ln):
        chosen[x] = 'x'

tmp = ''
for i in range(n):
    if chosen[i] == 'x':
        tmp += word[i]
    else:
        if tmp != '':
            print tmp
            tmp = ''
if tmp != '':
    print tmp
    tmp = ''
