#!/usr/bin/python

w = raw_input()
w += '$'
N = len(w)
sa = []

wlens = [set() for i in xrange(N + 1)]

words = set()
for i in range(N):
    for j in range(i + 1, N + 1):
        words.add(w[i:j])
        wlens[j - i].add(w[i:j])
    sa.append((w[i:], i))

def lcp_(a, b):
    i = 0
    while a[:i] == b[:i]: i += 1
    return i - 1

sa.sort()
# number of words
print len(words)
# number of words of some len
print ' '.join(str(len(x)) for x in wlens)
# suffix array
print ' '.join(str(x) for _,x in sa)
# sorted suffixes
print '\n'.join(str(x) for x,_ in sa)
lcp = []
for i in range(N - 1):
    lcp.append(lcp_(sa[i][0], sa[i + 1][0]))

# lcp aray
print ' '.join(str(x) for x in lcp + [0])
