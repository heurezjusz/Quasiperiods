import sys
import os
from pathlib import Path

PARTS = ["random", "recursive"]


def get_parts():
    global PARTS

    if len(sys.argv) != 2 or sys.argv[1] == "help":
        print("usage: python3 run.py all/part1,part2,...")
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
