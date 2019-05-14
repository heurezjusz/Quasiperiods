import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import get_parts, find_tests_of_part, get_report_of_part
from utils.testdata import get_test_size
from utils.plotting import plt, plot_from_list_of_pairs


plt.figure(figsize=(12, 8))


def parse_report_per_label_size(part):
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
        size = get_test_size(part, test)
        for time, label in zip(line.split()[1:], labels):
            if time == "None":
                continue
            if size not in results[label]:
                results[label][size] = []
            results[label][size].append(float(time))

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


def plot_size_of_part(part):
    print("plotting", part)
    results = parse_report_per_label_size(part)

    avg_dict = dict_dict_map(results, list_avg)
    plots = [(label, list(d.items())) for label, d in avg_dict.items()]

    plots.sort(key=lambda x: max(y for _, y in x[1]), reverse=True)
    print([x for x, _ in plots])

    labels = []

    for label, data in plots:
        labels.append(label)
        print(label, data)
        plot_from_list_of_pairs(data)

    plt.legend(labels, loc="upper left")

    plt.xlabel("test size (N)")
    plt.ylabel("execution time [s]")
    plt.grid()
    plt.show()


for part in get_parts():
    plot_size_of_part(part)
