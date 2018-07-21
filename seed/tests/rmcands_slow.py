#!/usr/bin/python

s = raw_input()

res = []

def is_last_occ(i, j, s):
    n = len(s)
    l = j - i + 1
    for b in range(i + 1, n - l + 1):
        if s[i : j + 1] == s[b : b + l]:
            return False
    return True


def is_rcand(i, j, s):
    l = j - i + 1
    n = len(s)
    if n - l > j:
        return False

    min_end_len = n - j - 1
    for b in xrange(i + min_end_len, j + 2):
        if s.endswith(s[i:b]):
            break
    else:
        return False
    return is_last_occ(i, j, s)


def maxgap(l):
    res, last = -1, -1
    for i in l:
        if last != -1:
            res = max(res, i - last)
        last = i
    return res


def is_mcand(i, j, s):
    n = len(s)
    l = j - i + 1
    occ = [x for x in range(n) if s[x : x + l] == s[i : j  + 1]]
    return l >= maxgap(occ)


def add(res, i, j):
    if len(res) == 0 or res[-1][0] != i or res[-1][2] != j - 1:
        res.append([i, j, j])
    else:
        res[-1][2] = j


for i in xrange(len(s)):
    for j in xrange(i, len(s)):
        if is_rcand(i, j, s) and is_mcand(i, j, s):
            add(res, i, j)


print len(res)

for i, j1, j2 in res:
    print i, j1, j2
