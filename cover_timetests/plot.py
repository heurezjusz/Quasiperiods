import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, get_report_of_part
from utils.testdata import (
    get_test_size,
    get_test_period,
    get_test_alphabet,
    get_test_cover,
)
from utils.plotting import plt, plot_from_list_of_pairs


plt.figure(figsize=(12, 8))

POSSIBLE_PLOTS = ["size", "period", "alphabet", "cover"]

if len(sys.argv) < 3:
    plot_type = "size"
else:
    plot_type = sys.argv[2]

if plot_type not in POSSIBLE_PLOTS:
    print("Incorrect plot type. Possible types:", "/".join(POSSIBLE_PLOTS))
    sys.exit(1)


def parse_report_per_label_XXX(part, X="size"):
    assert X in ["size", "period", "alphabet", "cover"]

    lines = get_report_of_part(part).split("\n")
    assert lines[0] == "=== " + part + " ==="

    labels = lines[1].split()[1:]
    results = {}
    for label in labels:
        results[label] = {}

    for line in lines[2:]:
        if len(line) == 0:
            continue
        test = line.split()[0]

        if X == "cover":
            XXX = get_test_cover(part, test)
        elif X == "size":
            XXX = get_test_size(part, test)
        elif X == "period":
            XXX = get_test_period(part, test)
            if XXX == 1:
                continue
        else:
            XXX = get_test_alphabet(part, test)
            if XXX == 1:
                continue

        for time, label in zip(line.split()[1:], labels):
            if time == "None":
                continue
            if XXX not in results[label]:
                results[label][XXX] = []
            results[label][XXX].append(float(time))

    return results


def dict_dict_map(d, foo):
    res = {}
    for k1, d1 in d.items():
        res[k1] = {}
        for k2, v in d1.items():
            res[k1][k2] = foo(v)
    return res


def list_avg(l):
    return sum(l) / len(l)


def get_X_xlabel(X):
    if X == "size":
        return "test size (N)"
    if X == "period":
        return "period length"
    if X == "alphabet":
        return "alphabet size"
    if X == "cover":
        return "shortest cover length"


def real_label(label):
    return {
        "cover_nlogn.e": "nlogn",
        "cover_maxgap.e": "Moore",
        "cover_maxgap_static_mem.e": "Moore (static arrays)",
        "cover_recursive.e": "Apostolico",
        "cover_breslauer.e": "Breslauer",
        "cover_just_kmp.e": "KMP",
    }[label]


def title(part):
    per_period = "Strings with fixed period length (N=30,000,000)"
    per_cover = "Strings with fixed shortest cover length (N=30,000,000)"
    random = "Random strings"
    periodic = "Periodic strings"
    covered = "Strings with proper cover"
    alphabet = "Different strings with fixed alphabet size (N=30,000,000)"
    return {
        "big_periods": per_period,
        "little_periods": per_period,
        "small_periods": per_period,
        "random": random,
        "periodic": periodic,
        "letters": alphabet,
        "per_cover_small": per_cover,
        "per_cover_big": per_cover,
        "big_covers": covered,
        "small_covers": covered,
        "total_summary": "Average on all tests",
        "recursive": "wololo",
    }[part]


def plot_XXX_of_part(part, X="size"):
    assert X in ["size", "period", "alphabet", "cover"]
    print("plotting", part)
    results = parse_report_per_label_XXX(part, X)
    maxX = max(list(results.items())[0][1].items())[0]

    avg_dict = dict_dict_map(results, list_avg)
    plots = [(label, list(d.items())) for label, d in avg_dict.items()]

    plots.sort(key=lambda x: max(y for _, y in x[1]), reverse=True)
    print([x for x, _ in plots])

    labels = []
    for label, data in plots:
        labels.append(real_label(label))
        print(label, data)
        plot_from_list_of_pairs(label, data)

    plt.title(title(part), fontsize=20)

    plt.xlim(xmin=0, xmax=min(maxX, 3e7))

    if "periods" in part:
        plt.legend(labels, loc="upper right")
    elif part == "letters":
        plt.legend(labels, loc="upper right")
    elif part in ["periodic", "random", "big_covers", "small_covers"]:
        plt.legend(labels, loc="upper left")
    else:
        plt.legend(labels, loc="upper left")

    plt.ylim(ymin=0, ymax=1.5)

    plt.xlabel(get_X_xlabel(X))
    plt.ylabel("execution time [s]")
    plt.grid()
    plt.show()


for part in get_parts(
    max_argv=3, msg="usage: python3 plot.py part1,part2,... [plot_type]"
):
    plot_XXX_of_part(part, plot_type)
