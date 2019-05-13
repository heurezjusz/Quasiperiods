import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, report_fname
from utils.testdata import get_test_size

PROG = Path("prog")
REPORT = []


def run_exe_on_test(exe, test):
    t_start = time.time()
    res = os.system("./%s < %s > /dev/null" % (exe, test))
    t_end = time.time()
    runtime = t_end - t_start
    if res != 0:
        print(exe, "fails...")
    return runtime


def run_on_test(part, test):
    print("running all solutions on %s" % test)
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

for part in get_parts():
    print_header(part)
    for test in find_tests_of_part(part):
        run_on_test(part, test)

    Path(report_fname(part)).write_text("\n".join(REPORT) + "\n")
