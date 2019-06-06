import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, get_report_of_part, get_filters
from utils.testdata import (
    get_test_size,
    get_test_period,
    get_test_alphabet,
    get_test_seed,
)
from utils.plotting import plt, plot_from_list_of_pairs


plt.figure(figsize=(12, 8))

POSSIBLE_PLOTS = ["size", "period", "alphabet", "seed"]

if len(sys.argv) < 3:
    plot_type = "size"
else:
    plot_type = sys.argv[2]

if plot_type not in POSSIBLE_PLOTS:
    print("Incorrect plot type. Possible types:", "/".join(POSSIBLE_PLOTS))
    sys.exit(1)


def filtered_out(filters, testname):
    if filters == []:
        return False
    for keyword in filters:
        if keyword in testname:
            return False
    return True


def parse_report_per_label_XXX(part, X="size"):
    assert X in ["size", "period", "alphabet", "seed"]

    lines = get_report_of_part(part).split("\n")
    assert lines[0] == "=== " + part + " ==="

    filters = get_filters()

    labels = lines[1].split()[1:]
    results = {}
    for label in labels:
        results[label] = {}

    for line in lines[2:]:
        if len(line) == 0:
            continue
        test_name = line.split()[0]

        if filtered_out(filters, test_name):
            continue

        if part == "periodic" and 1 == get_test_period(part, test_name):
            continue

        if X == "size":
            XXX = get_test_size(part, test_name)
        elif X == "period":
            XXX = get_test_period(part, test_name)
        elif X == "seed":
            XXX = get_test_seed(part, test_name)
        else:
            XXX = get_test_alphabet(part, test_name)
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
        return "string length (N)"
    if X == "period":
        return "period length"
    if X == "alphabet":
        return "alphabet size"
    if X == "seed":
        return "shortest seed length"


def title(part):
    per_period = "Strings with fixed period length (N=500,000)"
    per_seed = "Strings with fixed shortest seed length (N=500,000)"
    random = "Random strings"
    periodic = "Periodic strings"
    seeded = "Strings with proper seed"
    alphabet = "Different strings with fixed alphabet size (N=500,000)"
    return {
        "big_periods": per_period,
        "small_periods": per_period,
        "random": random,
        "periodic": periodic,
        "letters": alphabet,
        "per_seed_small": per_seed,
        "per_seed_big": per_seed,
        "big_seeds": seeded,
        "small_seeds": seeded,
        "total_summary": "Average on all tests",
    }[part]


def real_label(label):
    return {
        "seed_kociumaka.e": "KKRRW",
        "seed_imp.e": "IMP",
        "seed_kociumaka_nlogn.e": "KKRRW-s",
    }[label]


def plot_XXX_of_part(part, X="size"):
    assert X in ["size", "period", "alphabet", "seed"]
    print("plotting", part)
    results = parse_report_per_label_XXX(part, X)

    avg_dict = dict_dict_map(results, list_avg)
    plots = [(label, list(d.items())) for label, d in avg_dict.items()]

    plots.sort(key=lambda x: max(y for _, y in x[1]), reverse=True)
    print([x for x, _ in plots])

    labels = []

    for label, data in plots:
        labels.append(real_label(label))
        print(label, data)
        plot_from_list_of_pairs(label, data)

    if "_periods" in part or "per_seed_big" == part or "letters" == part:
        plt.ylim(ymin=0, ymax=5)
    else:
        plt.ylim(ymin=0, ymax=3)

    plt.title(title(part), fontsize=20)

    plt.legend(labels, loc="upper left")
    # elif part == "letters":
    #     plt.legend(labels, loc="upper right")
    #     plt.ylim(ymin=0, ymax=2)
    # else:
    #     plt.legend(labels, loc="upper left")
    #     plt.ylim(ymin=0, ymax=1.0)

    plt.xlabel(get_X_xlabel(X))
    plt.ylabel("execution time [s]")
    plt.grid()
    plt.show()


for part in get_parts(
    max_argv=4, msg="usage: python3 plot.py part1,part2,... [plot_type, [filters]]"
):
    plot_XXX_of_part(part, plot_type)
