*This project has been created as part of the 42 curriculum by werlim, lukperei.*

# push_swap

## Description

`push_swap` takes a list of integers and prints a short list of operations that sorts them, using two stacks (**a** and **b**) and 11 allowed operations (`sa sb ss pa pb ra rb rr rra rrb rrr`). The numbers start in a (the first argument is the top). At the end, a must be sorted with the smallest on top, and b must be empty.

Before sorting, the program measures the **disorder** of a: the share of number pairs that are in the wrong order (0 = sorted, 1 = reversed). It then runs one of four strategies:

| Flag | Strategy | Class (in operations) |
|------|----------|-----------------------|
| `--simple` | Minimum extraction | O(n²) |
| `--medium` | Chunk sort | O(n√n) |
| `--complex` | Binary radix sort | O(n log n) |
| `--adaptive` (default) | Picks one of the above from the disorder | depends on disorder |

### Contributions

| Learner | Parts | Files |
|---------|-------|-------|
| werlim | Design and task split, data structures, the 11 operations, list helpers, rank assignment, disorder, dispatcher, adaptive strategy, radix sort, medium sort main loop and push-back phase, `--bench`, `ps_printf`, Makefile | `push_swap.h`, `main.c`, `op_*.c`, `ps_node_utils.c`, `ps_struct_init.c`, `ps_assign_rank.c`, `ps_disorder.c`, `ps_dispatch.c`, `ps_is_sorted.c`, `ps_bench.c`, `sort_adaptive.c`, `sort_complex.c`, `ps_printf/` |
| lukperei | Argument parsing and error checks, flag handling, simple sort, small-input sorts (2 to 5 numbers), rotation check, medium sort chunk helpers, libft | `parsing.c`, `parsing_utils.c`, `parsing_utils2.c`, `ps_assign_flag.c`, `sort_simple.c`, `sort_simple2.c`, `sort_simple_utils.c`, `sort_simple_utils2.c`, `sort_medium_utils.c`, `libft/` |

## Instructions

```sh
make                      # builds libft, ps_printf and push_swap
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <numbers>
```

```sh
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG              # check the result
./push_swap $ARG | wc -l                             # count operations
./push_swap --bench $ARG > /dev/null                 # show only the benchmark
./push_swap --bench $ARG 2> bench.txt | ./checker_linux $ARG
```

- Numbers can be separate arguments or one quoted string.
- No arguments, or numbers already sorted: nothing is printed.
- Bad input (not an integer, outside `int` range, duplicate, empty argument, unknown flag, two strategy flags): `Error` on stderr.
- `--bench` prints the disorder, the strategy and its class, the total operations, and the count of each operation. It prints to stderr, so it never mixes with the operations on stdout.

## Algorithms

All algorithms work on each number's **rank** (its position in sorted order, 0 to n-1) instead of its value. This turns negative or huge numbers into 0 to n-1.

### Shortcuts that run before every strategy

- **Rotation check.** If a is already in order but shifted (for example `4 5 1 2 3`), the program only rotates the smallest number to the top the shorter way and stops.
- **Small inputs (2 to 5 numbers).** 2 numbers: one swap. 3 numbers: put the largest at the bottom, then swap the top two if needed (at most 2 operations). 4 and 5 numbers: push the smallest one or two to b, sort the 3 left, push back (at most 6 and 10 operations).

These are fixed costs for n ≤ 5, so they do not change the complexity class of any strategy.

### Simple: minimum extraction — O(n²)

Find the smallest number in a, rotate it to the top the shorter way (`ra` or `rra`), and push it to b. Repeat until a is empty, then `pa` everything back.

- **Operations:** with k numbers left, reaching the smallest costs at most k/2 rotations. In total that is at most n²/4 + 2n, so O(n²).
- **Memory:** O(1) extra. Operations only move existing nodes.

### Medium: chunk sort — O(n√n)

1. Split the ranks into groups of √n (0–9, 10–19, … for 100 numbers).
2. For each group in turn, rotate a and push every number of that group to b.
3. Push back from b, each time rotating the largest number to the top first.

- **Operations:** step 2 needs at most one full turn of a per group. That is √n groups × n rotations. In step 3 the largest number is always in the top group of b, so it is at most √n moves away. Both steps are about n√n, so O(n√n).
- **Memory:** O(1) extra.

### Complex: binary radix sort — O(n log n)

Look at the rank in binary, one bit at a time, starting with the lowest bit. For each bit, go through a once: bit 0 → `pb`, bit 1 → `ra`. Then `pa` everything back. Each pass keeps the order set by the previous passes, so after the highest bit, a is sorted.

- **Operations:** ranks fit in log₂(n) bits (9 bits for 500). Each pass costs at most 2n operations. Total at most 2n·log₂(n), so O(n log n).
- **Memory:** O(1) extra.

### Adaptive

| Disorder | Method used | Why |
|----------|-------------|-----|
| < 0.2 | Simple | Nearly sorted: the smallest number is almost always near the top, so each step costs about one move. |
| 0.2 – 0.5 | Medium | Too messy for simple sort. Chunk sort costs about the same whatever the order. |
| ≥ 0.5 | Complex | As messy as random input or worse. Radix has the best worst case. |

The thresholds 0.2 and 0.5 come from the subject. Each regime gets the method whose strength matches it, and each method stays within the class the subject requires (O(n²), O(n√n), O(n log n)). Memory is O(1) extra in every case.

### Results (operations)

| n | simple | medium | complex | adaptive |
|---|-------:|-------:|--------:|---------:|
| 2 / 3 / 4 / 5 (worst case) | 1 / 2 / 6 / 10 | same | same | same |
| 100 random | ~1500 | ~820 | 1084 | ≤ 1084 |
| 500 random | ~32000 | ~8100 | 6784 | ≤ 8150 |

### Resources

- Selection (min) Sort (Wikipedia) - https://en.wikipedia.org/wiki/Selection_sort
- Bucket/Chunk Sort (Wikipedia) - https://en.wikipedia.org/wiki/Bucket_sort
- Radix Sort (Wikipedia) - https://en.wikipedia.org/wiki/Radix_sort

### Use of AI

We used AI mainly as a tutor: explaining concepts (linked lists, the sorting algorithms, Makefile), refining the codebase after solving bugs found, and drafting this README, which we checked and edited. All code sumbitted are written entirely by us.