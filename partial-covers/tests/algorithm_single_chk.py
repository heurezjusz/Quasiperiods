#!/usr/bin/python

import sys

_, fin, fwzo, fsol = sys.argv

with open(fin, 'r') as f:
    S = f.read().split()[0]
    N = len(S)

with open(fwzo, 'r') as f:
    lines_wzo = f.read().split("\n")

with open(fsol, 'r') as f:
    lines_sol = f.read().split("\n")

if lines_wzo[0] != lines_sol[0]:
    print "WRONG, wiersz 1: %s vs %s\n" % (lines_sol[0], lines_wzo[0])
    sys.exit(1)

if lines_wzo[0] == "0":
    print "NOPE"
    sys.exit(0)


def set_from_poslist(l, d):
    return set(S[i:i + d] for i in [int(x) - 1 for x in l.split()])


d = int(lines_wzo[0])
if set_from_poslist(lines_sol[1], d) != set_from_poslist(lines_wzo[1], d):
    print "WRONG\nsets of words are different"
    sys.exit(1)

print "OK"
