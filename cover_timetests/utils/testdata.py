def _get_test_size_from_name(testname):
    fname = str(testname).split("/")[-1]
    N = fname.split("_")[1]
    return int(N)


def _get_test_period_by_name(testname):
    fname = str(testname).split("/")[-1]
    pin = fname.split("_")[3]
    p = pin.split(".")[0]
    return int(p)


def get_test_size(part, testname):
    if part in ["random", "recursive", "periodic", "small_periods", "big_periods", "little_periods"]:
        return _get_test_size_from_name(testname)
    else:
        raise NotImplementedError


def get_test_period(part, testname):
    if part in ["periodic", "small_periods", "big_periods", "little_periods"]:
        return _get_test_period_by_name(testname)
    else:
        raise NotImplementedError
