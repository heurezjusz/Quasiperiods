def _get_test_size_from_name(testname):
    fname = str(testname).split("/")[-1]
    N = fname.split("_")[1]
    return int(N)


def _get_test_period_by_name(testname):
    fname = str(testname).split("/")[-1]
    pin = fname.split("_")[3]
    p = pin.split(".")[0]
    return int(p)


def _get_test_seed_by_name(testname):
    fname = str(testname).split("/")[-1]
    p = fname.split("_")[2]
    return int(p)


def _get_test_alphabet(part, testname):
    fname = str(testname).split("/")[-1]
    idx = {"letters": 2, "big_periods": 2}[part]
    A = fname.split("_")[idx]
    return int(A)


def get_test_size(part, testname):
    if part in [
        "random",
        "letters",
        "small_periods",
        "big_periods",
        "little_periods",
        "small_seeds",
        "big_seeds",
        "periodic",
        "per_seed_big",
        "per_seed_small",
        "total_summary",
    ]:
        return _get_test_size_from_name(testname)
    else:
        raise NotImplementedError


def get_test_period(part, testname):
    if part in ["small_periods", "big_periods", "little_periods", "periodic"]:
        return _get_test_period_by_name(testname)
    else:
        raise NotImplementedError


def get_test_seed(part, testname):
    if part in ["small_seeds", "big_seeds", "per_seed_big", "per_seed_small"]:
        return _get_test_seed_by_name(testname)
    else:
        raise NotImplementedError


def get_test_alphabet(part, testname):
    if part in ["letters"]:
        return _get_test_alphabet(part, testname)
    else:
        raise NotImplementedError
