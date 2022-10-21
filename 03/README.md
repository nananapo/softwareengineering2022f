## sort

file : sort.cc

#### example output
```sh
$ make
$ ./sort 100000
Insert: 9417 ms
Quick: 4 ms
std::sort: 4 ms
Count: 3 ms
Radix: 300263 ms
```

** Radix sort is too slow! **

#### insertion sort

function : void insertSort()
stable : Yes
time complexity : O(N^2)

#### quick sort

function : quickSort
stable : No
worst time comlexity : O(N^2)
avg time complextity : O(NlogN)

This implementation of quick sort is not a stable sort.
Because the partition() swaps values.

#### counting sort

function : countSort
time complexity : O(N)
space complexity : O(N)

#### Radix sort

function : radixSort
time complexity : 入力がn個のd桁の数の時、挿入ソートしているのでO(d(N^2))

```cpp
void stableSortK(std::vector<int>& arr, int k)
```
stableSortK sorts numbers by the kth digit.
It is stable sort.
