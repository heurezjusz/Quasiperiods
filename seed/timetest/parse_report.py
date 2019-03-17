with open('report.out', 'r') as f:
    lines = f.read().split("\n")


def prettyprint(a, b, c, d):
    print " \t| ".join([a, b, c, d])


prettyprint("test name", "time lin", "time nlogn", "time costas")
for i in range(0, len(lines), 4):
    prettyprint(lines[i], lines[i + 1], lines[i + 2], lines[i + 3])
