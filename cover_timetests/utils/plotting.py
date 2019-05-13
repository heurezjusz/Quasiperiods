from matplotlib import pyplot as plt
import itertools


DASHESCYCLE = itertools.cycle([[10, 1], [1, 2], [5, 5]])
COLORCYCLE = itertools.cycle(["#000000", "#AAAAAA", "#555555"])
CURRENT_COLOR = next(COLORCYCLE)
CHANGE_COLOR = [5, 5]


def plot_from_list_of_pairs(lst):
    global CURRENT_COLOR
    dashes = next(DASHESCYCLE)
    x, y = zip(*sorted(lst))
    print("plot with color %s and style %s" % (CURRENT_COLOR, str(dashes)))
    plt.plot(x, y, "o", color=CURRENT_COLOR, markersize=5, dashes=dashes)

    if dashes == CHANGE_COLOR:
        print("*")
        CURRENT_COLOR = next(COLORCYCLE)

