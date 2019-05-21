import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, get_report_of_part, get_filters
from utils.testdata import get_test_size, get_test_period, get_test_alphabet
from utils.plotting import plt, plot_from_list_of_pairs


plt.figure(figsize=(12, 8))

POSSIBLE_PLOTS = ["size", "period", "alphabet"]

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
    assert X in ["size", "period", "alphabet"]

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

        if X == "size":
            XXX = get_test_size(part, test_name)
        elif X == "period":
            XXX = get_test_period(part, test_name)
        else:
            XXX = get_test_alphabet(part, test_name)

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


def plot_XXX_of_part(part, X="size"):
    assert X in ["size", "period", "alphabet"]
    print("plotting", part)
    results = parse_report_per_label_XXX(part, X)

    avg_dict = dict_dict_map(results, list_avg)
    plots = [(label, list(d.items())) for label, d in avg_dict.items()]

    plots.sort(key=lambda x: max(y for _, y in x[1]), reverse=True)
    print([x for x, _ in plots])

    labels = []

    for label, data in plots:
        labels.append(label)
        print(label, data)
        plot_from_list_of_pairs(label, data)

    if X == "period":
        plt.ylim(ymin=0, ymax=5)

    if X == "alphabet":
        plt.legend(labels, loc="lower right")
    else:
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
