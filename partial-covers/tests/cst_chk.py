#!/usr/bin/python

import sys

_, fin, fwzo, fsol = sys.argv

with open(fin, 'r') as f:
    N = len(f.read().split("\n")[0])

with open(fwzo, 'r') as f:
    lines_wzo = f.read().split("\n")

with open(fsol, 'r') as f:
    lines_sol = f.read().split("\n")

idx = 0
M = min(len(lines_sol), len(lines_wzo))
for i in range(1, N + 1):
    swzo = set()
    ssol = set()
    idx += 1
    while idx < M and not lines_wzo[idx].startswith("=="):
        swzo.add(lines_wzo[idx])
        ssol.add(lines_sol[idx])
        idx += 1

    if swzo != ssol:
        print "WRONG for len =", i
        sys.exit(1)

print "OK"
