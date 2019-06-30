from matplotlib import pyplot as plt
import itertools


BLACK = "#000000"
GREY = "#AAAAAA"
RED = "#EE4444"
BLUE = "#0066ff"
ORANGE = "#ff8000"
GREEN = "#33cc33"
LINE = [10, 1]
DOTS = [1, 2]
DASHES = [5, 5]

color_dash_dict = {
    "cover_breslauer.e": (GREEN, DASHES),
    "cover_ms.e": (BLACK, LINE),
    "cover_ms_static_mem.e": (BLACK, DASHES),
    "cover_folk.e": (BLUE, LINE),
    "cover_afi.e": (ORANGE, DOTS),
    "cover_just_kmp.e": (RED, DASHES),
}


def plot_from_list_of_pairs(label, lst):
    color, dashes = color_dash_dict[label]
    x, y = zip(*sorted(lst))
    print("plot with color %s and style %s" % (color, str(dashes)))
    plt.plot(x, y, "o", color=color, markersize=5, dashes=dashes)
