import sys
import os
import time
import importlib
import random
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, report_fname
from utils.testdata import get_test_size

PROG = Path("prog")


def run_exe_on_test(exe, test):
    t_start = time.time()
    res = os.system("./%s < %s > /dev/null" % (exe, test))
    t_end = time.time()
    runtime = t_end - t_start
    if res != 0:
        print(exe, "fails...")
    return runtime


def run_on_test(part, test):
    global EXE, REPORT
    times = [test.parts[-1]]
    for exe in EXE:
        if "static_mem" in str(exe) and get_test_size(part, test) > 3e7:
            times.append(None)
        else:
            times.append(run_exe_on_test(exe, test))
    REPORT.append(" ".join(str(t) for t in times))


def find_exe():
    if len(list(PROG.glob("*.e"))) == 0:
        os.system("make -C prog")
    return sorted(PROG.glob("*.e"))


def print_header(part):
    global EXE, REPORT
    print("===", part, "===")
    REPORT.append("=== " + part + " ===")
    REPORT.append("test_name " + " ".join(exe.parts[-1] for exe in EXE))


EXE = find_exe()

print("setting ulimit")
os.system("ulimit -s unlimited")

for part in get_parts():
    REPORT = []

    print_header(part)
    tests = find_tests_of_part(part)
    random.shuffle(tests)
    T = len(tests)

    for (i, test) in enumerate(tests):
        print("[%d%%] running all solutions on %s" % (int(100 * (i + 1) / T), test))
        run_on_test(part, test)

    Path(report_fname(part)).write_text("\n".join(REPORT) + "\n")
