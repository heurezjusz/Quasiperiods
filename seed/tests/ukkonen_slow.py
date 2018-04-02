#!/usr/bin/python

w = raw_input()
w += '$'
N = len(w)

sa = []

words = set()
for i in range(N):
    for j in range(i + 1,N):
        words.add(w[i:j])
    sa.append((w[i:], i))

def lcp_(a, b):
    i = 0
    while a[:i] == b[:i]: i += 1
    return i - 1

sa.sort()
print len(words)
print ' '.join(str(x) for _,x in sa)

print '\n'.join(str(x) for x,_ in sa)

lcp = []
for i in range(N - 1):
    lcp.append(lcp_(sa[i][0], sa[i + 1][0]))

print ' '.join(str(x) for x in lcp + [0])
