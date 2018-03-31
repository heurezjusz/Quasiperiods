#!/usr/bin/python

import os
import sys

PARTS = ["combine", "all"]

CHECKER = {
    "combine": "combine_chk.e"
}

CORRECT = {
    "combine": "combine_slow.e"
}

BIN = {
    "combine": ["combine_str.e", "combine_tree.e"]
}

TEST_DIR = {
    "combine": "combine"
}


if len(sys.argv) != 2:
    print "Usage:", sys.argv[0], "PART1[,PART2,...]"
    print "Available parts are: ", ','.join(PARTS)
    sys.exit(1)


parts = sys.argv[1].split(',')
for part in parts:
    if part not in PARTS:
        print "Unrecognized part:", part
        sys.exit(1)


def print_good(x):
    print '\033[32m' + x + '\033[39m'
def print_bad(x):
    print '\033[31m' + x + '\033[39m'
def print_info(x):
    print '\033[33m' + x + '\033[39m'

def safe_exec(command):
    res = os.system(command)
    if res != 0:
        print "Something went wrong :("
        sys.exit(1)

def test_part(part):
    global CHECKER, CORRECT, BIN, TEST_DIR

    print '=' * 10, part, '=' * 10
    print_info("building " + part)
    os.system('make ' + part)

    for sol in BIN[part]:
        print_info("testing " + sol)
        tst = TEST_DIR[part]
        corr = CORRECT[part]
        chk = CHECKER[part]

        for fname in os.listdir(tst):
            path = os.path.join(tst, fname)
            print fname, '\t',
            safe_exec("./%s < %s > %s" % (corr, path, "out_corr"))
            safe_exec("./%s < %s > %s" % (sol, path, "out_sol"))
            res = os.system('./%s %s out_corr out_sol > sssh' % (chk, path))
            if res != 0:
                print_bad("WRONG")
            else:
                print_good("OK")
            safe_exec('rm out_corr out_sol sssh')

for part in parts:
    if part == "all":
        for p in PARTS:
            if p != "all":
                test_part(p)
    else:
        test_part(part)
