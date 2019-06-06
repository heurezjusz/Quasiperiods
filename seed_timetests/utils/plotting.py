from matplotlib import pyplot as plt
import itertools


DASHESCYCLE = itertools.cycle([[10, 1], [1, 2], [5, 5]])
COLORCYCLE = itertools.cycle(["#000000", "#AAAAAA", "#555555"])
CURRENT_COLOR = next(COLORCYCLE)
CHANGE_COLOR = [5, 5]

color_dash_dict = {
    "seed_kociumaka.e": ("#000000", [10, 1]),
    "seed_costas.e": ("#AAAAAA", [10, 1]),
    "seed_kociumaka_nlogn.e": ("#000000", [1, 2]),
}


def plot_from_list_of_pairs(label, lst):
    global CURRENT_COLOR
    color, dashes = color_dash_dict[label]
    x, y = zip(*sorted(lst))
    print("plot with color %s and style %s" % (color, str(dashes)))
    plt.plot(x, y, "o", color=color, markersize=5, dashes=dashes)
