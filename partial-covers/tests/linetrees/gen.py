import os
import string
import random
random.seed(42)


def line(N):
    return [(i, i + 1) for i in range(1, N)]


def rand(N):
    l = line(N)
    random.shuffle(l)
    return l


def write_test(fname, test):
    with open(fname, 'w') as f:
        N = len(test) + 1
        f.write("%d\n" % N)
        f.write('\n'.join("%d %d" % x for x in test))
        f.write("\n")


for i in [5, 10, 15, 20, 30, 50, 100, 1000]:
    write_test("line%d.in" % i, line(i))
    write_test("invline%d.in" % i, line(i)[::-1])
    write_test("randline%d.in" % i, rand(i))
