#!/usr/bin/python

import os
import sys

PARTS = sorted(["combine", "maxgap", "all", "ukkonen", "ukkonen_perf",
                "lcands", "rmcands", "maxgap_nlogn", "rmcands_nlogn", "seeds_nlogn",
                "lens", "choose_sub", "call_smaller", "call_parts", "seeds", "combine2"])

CHECKER = {
    "call_parts": None,
    "call_smaller": None,
    "choose_sub": None,
    "combine": "packs_chk.e",
    "combine2": "packs_chk.e",
    "lcands": "packs_chk.e",
    "lens": None,
    "maxgap": None,
    "maxgap_nlogn": None,
    "rmcands": "rmcands_chk.e",
    "rmcands_nlogn": "rmcands_chk.e",
    "ukkonen": None,
    "ukkonen_perf": None,
    "seeds_nlogn": "packs_chk.e",
    "seeds": "packs_chk.e"
}

CORRECT = {
    "call_parts": "call_parts_slow.py",
    "call_smaller": "call_smaller_slow.py",
    "choose_sub": "choose_sub_slow.py",
    "combine": "combine_slow.e",
    "combine2": "combine2_slow.e",
    "maxgap": "maxgap_slow.e",
    "maxgap_nlogn": "maxgap_nlogn_slow.e",
    "lcands": "lcands_slow.py",
    "lens": "lens_slow.py",
    "rmcands": "rmcands_slow.py",
    "rmcands_nlogn": "rmcands_slow.py",
    "ukkonen": "ukkonen_slow.py",
    "ukkonen_perf": "ukkonen_perf_slow.e",
    "seeds_nlogn": "seeds_slow.py",
    "seeds": "seeds_slow.py"
}

BIN = {
    "call_parts": ["call_parts.e"],
    "call_smaller": ["call_smaller.e"],
    "choose_sub": ["choose_sub.e"],
    "combine": ["combine.e"],
    "combine2": ["combine2.e"],
    "maxgap": ["maxgap.e"],
    "maxgap_nlogn": ["maxgap_nlogn.e"],
    "lcands": ["lcands.e"],
    "lens": ["lens.e"],
    "rmcands": ["rmcands.e"],
    "rmcands_nlogn": ["rmcands_nlogn.e"],
    "ukkonen": ["ukkonen.e"],
    "ukkonen_perf": ["ukkonen_perf.e"],
    "seeds_nlogn": ["seeds_nlogn.e"],
    "seeds": ["seeds_lin.e"]
}


TEST_DIR = {
    "call_parts": "words_with_num",
    "call_smaller": "words_with_num",
    "choose_sub": "words_with_num",
    "combine": "combine",
    "combine2": "combine2",
    "lcands": "words",
    "lens": "words",
    "maxgap": "maxgap",
    "maxgap_nlogn": "maxgap",
    "rmcands": "words",
    "rmcands_nlogn": "words",
    "ukkonen": "words",
    "ukkonen_perf": "bigwords",
    "seeds_nlogn": "smallwords",
    "seeds": "smallwords"
}

GENINPUT = ["bigwords"]


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


for part in parts:
    if part == "all":
        for p in PARTS:
            if p != "all":
                test_part(p)
    else:
        test_part(part)

if cnt_ok < cnt_all:
    print_bad('Some errors occured')
    print_info('passed %d/%d tests' % (cnt_ok, cnt_all))
else:
    print_good('\033[1mOK! All tests passed! (%d)\033[0m' % cnt_all)
