#!/usr/bin/python

w = raw_input()
N = len(w)

sa = []

words = set()
for i in range(N):
    for j in range(i + 1,N):
        words.add(w[i:j])
    sa.append((w[i:], i))

print len(words)
print ' '.join(str(x) for _,x in sorted(sa))

print '\n'.join(str(x) for x,_ in sorted(sa))
