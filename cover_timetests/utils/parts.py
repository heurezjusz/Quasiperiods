import sys
import os
from pathlib import Path

PARTS = ["random", "recursive", "periodic", "small_periods", "big_periods", "little_periods"]


def get_parts(max_argv=2, msg=None):
    global PARTS

    if len(sys.argv) < 2 or len(sys.argv) > max_argv or sys.argv[1] == "help":
        if msg is None:
            msg = "usage: python3 %s all/part1,part2,..." % sys.argv[0]
        print(msg)
        sys.exit(1)

    parts = sys.argv[1].split(",")
    chosen = []
    for part in parts:
        if part not in PARTS and part != "all":
            print("Unrecognized part:", part)
            print("available parts: all /", ", ".join(PARTS))
            sys.exit(1)

    if "all" in parts:
        return PARTS
    return parts


def find_tests_of_part(part):
    if len(list(Path(part).glob("*.in"))) == 0:
        os.system("make -C %s ingen" % part)
    return sorted(Path(part).glob("*.in"))


def report_fname(part):
    return "report_%s.txt" % part


def get_report_of_part(part):
    fname = Path(report_fname(part))
    assert fname.exists(), str(fname) + " not generated."
    return fname.read_text()
