from matplotlib import pyplot as plt
import itertools


BLACK = "#000000"
GREY = "#AAAAAA"
RED = "#EE4444"
BLUE = "#0066ff"
ORANGE = "#ff8000"
GREEN = "#33cc33"


color_dash_dict = {
    "seed_kociumaka.e": (BLUE, [10, 1]),
    "seed_imp.e": (RED, [10, 1]),
    "seed_kociumaka_nlogn.e": (GREEN, [1, 2]),
}


def plot_from_list_of_pairs(label, lst):
    color, dashes = color_dash_dict[label]
    x, y = zip(*sorted(lst))
    print("plot with color %s and style %s" % (color, str(dashes)))
    plt.plot(x, y, "o", color=color, markersize=5, dashes=dashes)
