# Benchmark Results

**Date and Time:** 2025-02-12T23:24:02+03:00  
**Running Command:** `./tests/benchmarks/benchmarks`  
**Run on:** (12 X 3000 MHz CPU s)

## CPU Caches:
- **L1 Data:** 32 KiB (x6)
- **L1 Instruction:** 32 KiB (x6)
- **L2 Unified:** 512 KiB (x6)
- **L3 Unified:** 4096 KiB (x2)

**Load Average:** 2.88, 4.91, 5.74

> ***WARNING***: CPU scaling is enabled, the benchmark real-time measurements may be noisy and will incur extra overhead.

---

## Benchmark Results Summary

| Benchmark                                  | Time        | CPU         | Iterations |
|--------------------------------------------|-------------|-------------|------------|
| **BM_BFS_AdjacencyListGraph/10**          | 1053 ns    | 1053 ns    | 693421     |
| **BM_BFS_AdjacencyListGraph/64**          | 8192 ns    | 8192 ns    | 84907      |
| **BM_BFS_AdjacencyListGraph/512**         | 75183 ns   | 75181 ns   | 9131       |
| **BM_BFS_AdjacencyListGraph/4096**        | 1101803 ns | 1101210 ns | 682        |
| **BM_BFS_AdjacencyListGraph/32768**       | 21228884 ns| 21226063 ns| 31         |
| **BM_BFS_AdjacencyListGraph/100000**      | 84927447 ns| 84924761 ns| 9          |
| **BM_BFS_AdjacencyMatrixGraph/10**        | 1397 ns    | 1397 ns    | 514880     |
| **BM_BFS_AdjacencyMatrixGraph/64**        | 10175 ns   | 10158 ns   | 62662      |
| **BM_BFS_AdjacencyMatrixGraph/512**       | 417794 ns   | 416448 ns   | 1873        |
| **BM_BFS_AdjacencyMatrixGraph/4096**      | 20905303 ns| 20888660 ns| 35         |
| **BM_BFS_AdjacencyMatrixGraph/10000**     | 139143303 ns| 138866862 ns| 5         |

---

### Выводы
- При ```|V| = 4096``` происходит резкий скачок времени работы, но проблема не в алгоритме, а в том, что стало больше промахов по кешу. В остальном время работы растет линейно, что справедливо для алгоритма
- Для BFS список смежности даже при минимальных ```|V|``` работает лучше, поэтому лучше использовать его



