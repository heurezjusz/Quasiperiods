#!/bin/python

s = raw_input()

res = []

def is_lcand(i, j, s):
    for b in xrange(i, j - i + 2):
        if s.startswith(s[b:j+1]):
            break
    else:
        return False
    return s.find(s[i:j+1]) == i


def add(res, i, j):
    if len(res) == 0 or res[-1][0] != i or res[-1][2] != j - 1:
        res.append([i, j, j])
    else:
        res[-1][2] = j


for i in xrange(len(s)):
    for j in xrange(i, len(s)):
        if is_lcand(i, j, s):
            add(res, i, j)


for i, j1, j2 in res:
    print i, j1, j2
