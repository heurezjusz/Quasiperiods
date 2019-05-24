from matplotlib import pyplot as plt
import itertools


BLACK = "#000000"
GREY = "#AAAAAA"
LINE = [10, 1]
DOTS = [1, 2]
DASHES = [5, 5]

color_dash_dict = {
    "cover_breslauer.e": (GREY, LINE),
    "cover_maxgap.e": (BLACK, LINE),
    "cover_maxgap_static_mem.e": (BLACK, DOTS),
    "cover_nlogn.e": (GREY, DOTS),
    "cover_recursive.e": (BLACK, DASHES),
}


def plot_from_list_of_pairs(label, lst):
    color, dashes = color_dash_dict[label]
    x, y = zip(*sorted(lst))
    print("plot with color %s and style %s" % (color, str(dashes)))
    plt.plot(x, y, "o", color=color, markersize=5, dashes=dashes)

