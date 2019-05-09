import sys
import os
import time
from pathlib import Path

PROG = Path('prog')
PARTS = ["random"]
REPORT_FNAME = 'report.txt'
REPORT = []


def find_exe():
    return sorted(PROG.glob("*.e"))


def get_parts():
    global PARTS

    if len(sys.argv) != 2 or sys.argv[1] == "help":
        print("usage: python3 run.py all/part1,part2,...")
        sys.exit(1)

    parts = sys.argv[1].split(',')
    for part in parts:
        if part not in PARTS and part != "all":
            print("Unrecognized part:", part)
            print("available parts: all /", ", ".join(PARTS))
            sys.exit(1)

    if "all" not in parts:
        PARTS = parts


def run_exe_on_test(exe, test):
    t_start = time.time()
    res = os.system('./%s < %s > /dev/null' % (exe, test))
    t_end = time.time()
    runtime = t_end - t_start
    return runtime


def run_on_test(test):
    print("running all solutions on %s" % test)
    global EXE, REPORT
    times = [test.parts[-1]]
    for exe in EXE:
        times.append(run_exe_on_test(exe, test))
    REPORT.append(" ".join(str(t) for t in times))


def find_tests_of_part(part):
    os.system("make -C %s ingen" % part)
    return sorted(Path(part).glob("*.in"))


def print_header(part):
    global EXE, REPORT
    print("===", part, "===")
    REPORT.append("=== " + part + " ===")
    REPORT.append("test_name " + " ".join(exe.parts[-1] for exe in EXE))


EXE = find_exe()
get_parts()

for part in PARTS:
    print_header(part)
    for test in find_tests_of_part(part):
        run_on_test(test)

Path(REPORT_FNAME).write_text("\n".join(REPORT) + "\n")