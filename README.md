# Quasiperiods
Experimental Evaluation of Algorithms for Computing Quasiperiods

## Usage


## Implementations

### Directory `seed` :
Directory `seed/` contains implementations if algorithms computing shortest seed of the string.

#### Executables :
Command `make -C seed` builds following executable files:

filename | algorithm | input type
-|-|-
`seed_imp.e`|Iliopoulos|string
`seed_imp_int.e`|Iliopoulos|integers
`seed_lin.e`|Kociumaka|string
`seed_lin_int.e`|Kociumaka|integers
`seed_nlogn.e`|simplified ![equation](http://latex.codecogs.com/gif.latex?O\(n\log(n)\)) version of Kociumaka|string
`seed_nlogn_int.e`|simplified ![equation](http://latex.codecogs.com/gif.latex?O\(n\log(n)\)) version of Kociumaka|integers

If input type is "string", the executable reads single string from `stdin`. For "integers" it expects
![equation](http://latex.codecogs.com/gif.latex?N) integers in format
```
N
a1 a2 a3... aN
```
This input format allows us to test algorithms on tests with huge alphabets.

Output format of all executables is a list if packages.

#### C++ library usage :

To use any of above algorithms, run `make` in location `seed/lib`. It will create directories `imp`, `kkrrw` and `kkrrws`.
Include `"seed/lib/[ALGORITHM].h"` in your code, where `[ALGORITHM]` should be replaced with `imp`, `kkrrw` or `kkrrws`.
It will provide the function
```cpp
void algorithm(std::vector<int> &word, std::vector<Pack> &result);
```
which takes input in `vector<int>` format (consecutive elements of the vector represents consecutive letters),
and appends the output at the end of the vector `result`.

Compile your code linking all objective files (`*.o`) from directory `seed/lib/[ALGORITHM]`.


### Directory  `partial-covers` :
Directory `partial-covers/` contains implementations if algorithms computing partial covers of the string.

#### Executables :
Command `make -C partial-covers` builds following executable files:

filename|description
-|-
`partial_covers_single.e`|Solution for Partial Covers problem. It reads from input a string and a float, representing input string ![equation](http://latex.codecogs.com/gif.latex?T) and value ![equation](http://latex.codecogs.com/gif.latex?\alpha) in percents. On output prints two lines. In the first one prints the length of the shortest partial cover covering at least ![equation](http://latex.codecogs.com/gif.latex?\alpha) positions. On the second line there are starting positions of occurrences of resulting partial covers. Each partial cover is listed once.
`partial_covers_all.e`|Solution for All Partial Covers problem. Input is a single string ![equation](http://latex.codecogs.com/gif.latex?T). On output print ![equation](http://latex.codecogs.com/gif.latex?\|T\|) lines in format ![equation](http://latex.codecogs.com/gif.latex?i:x_i), where ![equation](http://latex.codecogs.com/gif.latex?x_i) is the length of the shortest partial cover which covers at least ![equation](http://latex.codecogs.com/gif.latex?i) positions.
`slow_*`|Brute force solutions of above problems, used in correctness tests.

#### C++ library usage :

To use any of above algorithms, run `make` in location `parial-covers/lib`. It will create directories `algorithm_single` and `algorithm_all`.
Compile your code linking all objective files (`*.o`) from directory `seed/lib/[ALGORITHM]`.

Include one of the following files to your code:

 * `algorithm_all.h`
It provides the function
```cpp
void algorithm(std::vector<int>& word, std::vector<int>& result);
```
which takes input in `vector<int>` format (consecutive elements of the vector represents consecutive letters).
Vector `result` is expected to be empty. As the result, the function resizes `result` to the length `word.size() + 1`.
Element `result[i]` is the length of the shortest partial cover which covers at least `i` positions of `word`.
`result[0]` is filled with 0.

 * `algorithm_single.h`
It provides the function
```cpp
int algorithm(std::vector<int>& word, int min_positions,
              std::vector<int>& result);
```
which which takes the input word in `vector<int>` format (consecutive elements of the vector represents consecutive letters).
`min_positions` should be equal to ![equation](http://latex.codecogs.com/gif.latex?\alpha) - the minimum number of positions
to be covered by the partial cover.

The result of the function is the length of the minimum partial cover which covers at least `min_positions` positions of `word`.
Additionally, it fills the vector `result` with the list of starting positions of all covers of minimum length.
All previous content of `result` is lost.


### Directory `cover` :
Directory `cover/prog` contains implementations if algorithms computing shortest cover of the string.

filename | algorithm
-|-
`cover_afi.cpp`|Apostolico
`cover_breslauer.cpp`|Breslauer
`cover_folk.cpp`|folklore ![equation](http://latex.codecogs.com/gif.latex?O\(n\log(n)\))
`cover_ms.cpp`|Moore and Smyth
`cover_ms_static_mem.cpp`|Moore and Smyth with static array instead of `std::vector`

To compile all programs run `make -C cover/prog`. Input of all executable files is a single string, output
is the length of the cover.


## Performance testing tools

In directories `cover_timetests` and `seed_timetests` are testing tools allowing to run experiments we made in our paper. Usage:

- `make` prepares executable files
- `python3 run.py part`  measures execution times on tests from chosen part and saves it in `report_part.txt`. List of parts is available by running `python3 run.py help`. Tests are chosen in random order.
- `python3 plot.py part plot-type` plots results saved in `report_part.txt`. Plot type defines values on x-axis. Possible types are: "size" (default), "period", "alphabet" and "cover/seed".

## Unit tests

In `seed` and `partial-covers` directories there is `test` subdirectory containing Python script for running all unit tests. Usage: `python test.py all`.

To run tests in `cover` directory execute `make run_all`. To run tests only on solution `cover_XXX.cpp` execute `make run_XXX`.
