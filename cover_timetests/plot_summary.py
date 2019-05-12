import sys
import os
import time
import importlib
from pathlib import Path

utils = importlib.import_module("utils")
from utils.parts import PARTS, get_parts, find_tests_of_part, get_report_of_part
from utils.testdata import get_test_size


def plot_size_of_part(part):
    print("plotting", part)
    lines = get_report_of_part(part).split("\n")
    assert lines[0] == "=== " + part + " ==="


get_parts()
for part in PARTS:
    plot_size_of_part(part)