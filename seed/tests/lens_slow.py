#!/usr/bin/python

s = raw_input()
n = len(s)

sets = [set() for i in xrange(n + 2)]

for i in xrange(n):
    for j in xrange(i + 1, n + 1):
        sets[j - i].add(s[i:j])

for i in xrange(1, n + 1):
    print ("%d:%d" % (i, len(sets[i])))
