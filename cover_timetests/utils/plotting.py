from matplotlib import pyplot as plt
import itertools


DASHESCYCLE = itertools.cycle(
    [[10, 10], [5, 5], [3, 3], [10, 1], [10, 5, 5, 5], [3, 3, 5, 3, 10, 3]]
)
COLORCYCLE = itertools.cycle(["#000000", "#555555", "#AAAAAA"])


def plot_from_list_of_pairs(lst):
    x, y = zip(*sorted(lst))
    plt.plot(x, y, "o", color=next(COLORCYCLE), markersize=5, dashes=next(DASHESCYCLE))
