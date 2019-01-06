#!/usr/bin/python

import os
import sys

PARTS = sorted(["all", "partitions"])

CHECKER = {
    "partitions": None,
}

CORRECT = {
    "partitions": "partitions_slow.e",
}

BIN = {
    "partitions":
    ["partitions.e", "partitions_rand_labels.e", "partitions_rand_renames.e"],
}

TEST_DIR = {"partitions": "linetrees"}

GENINPUT = []


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


cnt_ok, cnt_all = 0, 0
parts_failed = []


def test_part(part):
    global CHECKER, CORRECT, BIN, TEST_DIR, cnt_ok, cnt_all

    print '=' * 10, part, '=' * 10
    print_info("building " + part)
    safe_exec('make ' + part)

    ok, bad = 0, 0

    for sol in BIN[part]:
        print_info("testing " + sol)
        tst = TEST_DIR[part]
        corr = CORRECT[part]
        chk = CHECKER[part]

        for fname in sorted(os.listdir(tst)):
            if not fname.endswith('.in'):
                continue
            path = os.path.join(tst, fname)
            print fname, '\t',

            if tst in GENINPUT:
                safe_exec("python ./%s/gen.py < %s > data.in" % (tst, path))
                path = 'data.in'

            safe_exec("./%s < %s > %s" % (corr, path, "out_corr"))
            safe_exec("./%s < %s > %s" % (sol, path, "out_sol"))

            if chk is None:
                res = os.system('diff out_corr out_sol > /dev/null')
            else:
                res = os.system(
                    './%s %s out_corr out_sol > /dev/null' % (chk, path))

            if res != 0:
                print_bad("WRONG")
                bad += 1
            else:
                print_good("OK")
                ok += 1
            safe_exec('rm out_corr out_sol')
            if tst in GENINPUT:
                safe_exec('rm data.in')

    print_info('passed %d/%d tests' % (ok, ok + bad))
    cnt_ok += ok
    cnt_all += ok + bad
    if bad != 0:
        parts_failed.append(part)


for part in parts:
    if part == "all":
        for p in PARTS:
            if p != "all":
                test_part(p)
    else:
        test_part(part)

if cnt_ok < cnt_all:
    print_bad('Some errors occured in parts: %s' % (",".join(parts_failed)))
    print_info('passed %d/%d tests' % (cnt_ok, cnt_all))
else:
    print_good('\033[1mOK! All tests passed! (%d)\033[0m' % cnt_all)
