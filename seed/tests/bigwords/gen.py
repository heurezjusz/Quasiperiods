#!/usr/bin/python
import random
import string


def random_test(n):
    return ''.join(random.choice(string.lowercase) for x in range(n))


def cycle_test(n):
    clen = n // 15
    return (15 * random_test(clen))[:n]


def points_test(n):
    tst = ['a'] * n
    pt = random_test(5)
    i = 50
    while (i + 5 + 2 < n):
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


def write_test(name, tst):
    with open(name, "w") as f:
        f.write(tst + "\n")


def main(inp, num):
    x, n, seed = inp.split()
    n = int(n)
    random.seed(int(seed))
    fname = x + str(num) + ".in"

    if x == "random":
        write_test(fname, random_test(n))

    if x == "cycle":
        write_test(fname, cycle_test(n))

    if x == "points":
        write_test(fname, points_test(n))

    if x == "recursive":
        write_test(fname, recursive_test(n))

    if x == "ababa":
        write_test(fname, ababa_test(n))


for num, inp in enumerate([
        "points 10033 1",
        "points 10033 2",
        "points 50003 3",
        "points 100000 4",
        "random 10030 1",
        "random 10030 2",
        "random 50037 3",
        "random 100000 4",
        "recursive 10 0",
        "recursive 12 0",
        "recursive 15 0",
        "recursive 17 0",
]):
    print inp
    main(inp, num)
