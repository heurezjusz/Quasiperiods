import sys
import os
from pathlib import Path
from .testdata import get_test_size

PARTS = [
    "random",
    "letters",
    "small_periods",
    "big_periods",
    "little_periods",
    "small_seeds",
    "big_seeds",
    "periodic",
    "per_seed_big",
    "per_seed_small",
    "total_summary",
]


def get_parts(max_argv=2, msg=None):
    global PARTS

    if len(sys.argv) < 2 or len(sys.argv) > max_argv or sys.argv[1] == "help":
        if msg is None:
            msg = "usage: python3 %s all/part1,part2,..." % sys.argv[0]
        print(msg)
        sys.exit(1)

    parts = sys.argv[1].split(",")
    for part in parts:
        if part not in PARTS and part != "all":
            print("Unrecognized part:", part)
            print("available parts: all /", ", ".join(PARTS))
            sys.exit(1)

    if "all" in parts:
        return PARTS
    return parts


def get_filters():
    if len(sys.argv) < 4:
        return []
    return sys.argv[3].split(",")


def find_tests_of_part(part):
    if len(list(Path(part).glob("*.in"))) == 0:
        os.system("make -C %s ingen" % part)
    return sorted(Path(part).glob("*.in"))


def report_fname(part):
    return "report_%s.txt" % part


def has_multiple_sizes(lines):
    testnames = [line.split(" ")[0] for line in lines if len(line) != 0]
    sizes = set(get_test_size("total_summary", testname) for testname in testnames)
    return len(sizes) > 1


def get_report_of_part(part):
    if part == "total_summary":
        # get all reports
        reports = Path(".").glob("report_*.txt")
        all_lines = []
        header = None
        for fname in reports:
            lines = fname.read_text().split("\n")
            if header is None:
                header = lines[1]
            assert lines[1] == header, "Wrong solutions order in %s" % str(fname)
            if has_multiple_sizes(lines[2:]):
                # makes sense only for different N - size plot
                all_lines += lines[2:]
        return "\n".join(["=== total_summary ===", header] + all_lines)
    else:
        fname = Path(report_fname(part))
        assert fname.exists(), str(fname) + " not generated."
        return fname.read_text()
