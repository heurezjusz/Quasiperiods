#!/usr/bin/python
import random
import string

x, n, seed = raw_input().split()
n = int(n)
random.seed(seed)

def random_test(n):
    return ''.join(random.choice(string.lowercase) for x in range(n))

def cycle_test(n):
    clen = n // 15
    return (15 * random_test(clen))[:n]

def points_test(n):
    tst = ['a'] * n
    pt = random_test(5)
    i = 50
    while(i + 5 + 2 < n):
        diff = random.choice([-2, -1, 0, 1, 2])
        for j in xrange(len(pt)):
            tst[i + j + diff] = pt[j]
        i += 100
    return ''.join(tst)

def recursive_test(n):
    if n <= 0:
        return 'a'
    return recursive_test(n - 1) + chr(ord('a') + n) + recursive_test(n - 1)

def ababa_test(n):
    return ('a' * n + 'b') * 2 + 'a' * n


if x == "random":
    print random_test(n)

if x == "cycle":
    print cycle_test(n)

if x == "points":
    print points_test(n)

if x == "recursive":
    print recursive_test(n)

if x == "ababa":
    print ababa_test(n)
