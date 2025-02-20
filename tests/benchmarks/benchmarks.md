# Benchmark Results

## Ubuntu 22.04.5 LTS 

**Date and Time:** 2025-02-12T23:24:02+03:00  
**Running Command:** `./tests/benchmarks/benchmarks`  
**Run on:** (12 X 3000 MHz CPU s)

### CPU Caches:
- **L1 Data:** 32 KiB (x6)
- **L1 Instruction:** 32 KiB (x6)
- **L2 Unified:** 512 KiB (x6)
- **L3 Unified:** 4096 KiB (x2)

**Load Average:** 2.88, 4.91, 5.74

> ***WARNING***: CPU scaling is enabled, the benchmark real-time measurements may be noisy and will incur extra overhead.

---

### Benchmark Results Summary

| Benchmark                                      | Time         | CPU          | Iterations |
|------------------------------------------------|--------------|--------------|------------|
| **BM_BFS_AdjacencyListGraph/10**                   | 12137 ns    | 12084 ns     | 59216      |
| **BM_BFS_AdjacencyListGraph/64**                   | 66394 ns    | 65996 ns     | 9487       |
| **BM_BFS_AdjacencyListGraph/512**                  | 578483 ns   | 576239 ns    | 1130       |
| **BM_BFS_AdjacencyListGraph/4096**                 | 5070797 ns  | 5008486 ns   | 118        |
| **BM_BFS_AdjacencyListGraph/32768**                | 61212262 ns | 59482337 ns  | 11         |
| **BM_BFS_AdjacencyListGraph/100000**               | 216312548 ns | 211561761 ns | 3          |
| **BM_BFS_AdjacencyMatrixGraph/10**                 | 20397 ns    | 20317 ns     | 34790      |
| **BM_BFS_AdjacencyMatrixGraph/64**                 | 129613 ns   | 127389 ns    | 5435       |
| **BM_BFS_AdjacencyMatrixGraph/512**                | 1441838 ns  | 1437275 ns   | 460        |
| **BM_BFS_AdjacencyMatrixGraph/4096**               | 39003045 ns | 38881860 ns  | 18         |
| **BM_BFS_AdjacencyMatrixGraph/10000**              | 158197948 ns | 156946770 ns | 5          |
| **BM_Dijkstra_AdjacencyListGraph/10**              | 10048 ns    | 9995 ns      | 65704      |
| **BM_Dijkstra_AdjacencyListGraph/64**              | 52772 ns    | 52493 ns     | 11680      |
| **BM_Dijkstra_AdjacencyListGraph/512**             | 579982 ns   | 577368 ns    | 1122       |
| **BM_Dijkstra_AdjacencyListGraph/4096**            | 6913927 ns   | 6895109 ns   | 99         |
| **BM_Dijkstra_AdjacencyListGraph/32768**           | 68077589 ns | 67823432 ns  | 8          |
| **BM_Dijkstra_AdjacencyListGraph/100000**          | 260179425 ns | 259632284 ns | 3          |
| **BM_Dijkstra_AdjacencyMatrixGraph/10**            | 19247 ns    | 19111 ns     | 37697      |
| **BM_Dijkstra_AdjacencyMatrixGraph/64**            | 161177 ns   | 160054 ns    | 4238       |
| **BM_Dijkstra_AdjacencyMatrixGraph/512**           | 3098385 ns   | 3083381 ns   | 227        |
| **BM_Dijkstra_AdjacencyMatrixGraph/4096**          | 62814600 ns | 62455392 ns   | 11         |
| **BM_Dijkstra_AdjacencyMatrixGraph/5000**          | 87997167 ns   | 87673466 ns   | 8          |

---

Проанализировав бенчмарки можно сказать
- При больших данных, `|V| = 100000` bfs работает быстрее алгоритма Дейкстры (`216312548 ns` против `260179425 ns`). Это происходит из-за того, что для 1-k bfs подходят ребра с ограниченными весами `(<= k)`, тогда как Дейкстра ограничена только неотрицательностью ребер. Если веса ребер в графе невелики, то лучше использовать 1-k bfs, иначе алгоритм Дейкстры
- Список смежности гораздо оптимальнее матрицы смежности: (bfs) при `|V| = 32768` алгоритм на списке смежности работает за `61212262 ns`, при `|V| = 10000` алгоритм на матрице смежности работает за `158197948 ns` -- время в 2.5 раза больше, а размер графа в 3.2 раза меньше