#!/usr/bin/python


def matches(s, i, j, offset):
    x = j - i
    if offset < 0:
        i -= offset
        offset = 0
        x = j - i
    if offset + x > len(s):
        j -= offset + x - len(s)
        x = j - i
        offset = len(s) - x
    #print "cmp", i, j, s[i:j], "to", offset,  \
    #    x + offset, s[offset:offset + x]
    return s[i:j] == s[offset:x + offset]


def is_a_seed(s, i, j):
    #print s[i:j]
    last_pos = -1
    x = j - i
    n = len(s)
    for offset in xrange(-x + 1, n):
        if last_pos + 1 >= offset and matches(s, i, j, offset):
         #       print "lp <-", offset + x - 1
            last_pos = offset + x - 1
     #   print "lp", last_pos, "off", offset
    #print last_pos >= n - 1
    return last_pos >= n - 1


s = raw_input()
n = len(s)

res = []
res_s = set()


def res_add(i, j):
    j -= 1
    if len(res) > 0 and res[-1][0] == i and res[-1][2] == j - 1:
        res[-1] = (i, res[-1][1], j)
    else:
        res.append((i, j, j))


for i in xrange(0, n):
    for j in xrange(i + 1, n + 1):
        if not s[i:j] in res_s and is_a_seed(s, i, j):
            res_s.add(s[i:j])
            res_add(i, j)

print len(res)
for (i, j1, j2) in res:
    print i, j1, j2
