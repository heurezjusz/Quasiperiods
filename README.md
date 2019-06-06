# Quasiperiods
Experimental Evaluation of Algorithms for Computing Quasiperiods

## Implementations

### Directory `cover` :
`cover/prog` contains implementations if algorithms computing shortest cover of the string.

filename | algorithm
-|-
`cover_afi.cpp`|Apostolico
`cover_breslauer.cpp`|Breslauer
`cover_folk.cpp`|folklore $O(n\log n)$
`cover_ms.cpp`|Moore and Smyth
`cover_ms_static_mem.cpp`|Moore and Smyth with static array instead of `std::vector`

To compile all programs run `make -C cover/prog`. Input of all executable files is a single string, output
is the length of the cover.

### Directory `seed` :
`seed/` contains implementations if algorithms computing shortest seed of the string. Command `make -C seed` builds following executable files:

filename | algorithm | input type
-|-|-
`seed_imp.e`|Iliopoulos|string
`seed_imp_int.e`|Iliopoulos|integers
`seed_lin.e`|Kociumaka|string
`seed_lin_int.e`|Kociumaka|integers
`seed_nlogn.e`|simplified $O(n\log n)$ version of Kociumaka|string
`seed_nlogn_int.e`|simplified $O(n\log n)$ version of Kociumaka|integers

If input type is "string", the executable reads single string from `stdin`. For "integers" it expects
$N$ integers in format
```
N
a1 a2 a3... aN
```
This input format allows us to test algorithms on tests with huge alphabets.

Output format of all executables is a list if packages.
