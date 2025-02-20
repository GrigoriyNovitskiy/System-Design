# Memory usage

Использовался профайлер [heaptrack](https://github.com/KDE/heaptrack)

### Использование памяти при тесте `benchmarks_bfs1_k.cpp`:
- Most memory allocations - `graph::BFS_1k<int>::run(int)`
	- `BM_BFS_AdjacencyListGraph(benchmark::State&)` - 11069484 allocations, 3530578 temporary
	- `BM_BFS_AdjacencyMatrixGraph(benchmark::State&)` - 7743928 allocations, 7715 temporary
- Peak contributions - `BM_BFS_AdjacencyMatrixGraph(benchmark::State&)` - 1,6GB
- Most temporary allocations - `std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::operator=(std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > const&)` - 3530578 allocations
- Total system memory 16,1GB
- Total memory leaked 1,4kB - все утечки не вызваны работой библиотеки, они происходят внутри библиотеки benchmarks

### Использование памяти при тесте `benchmarks_dijkstra.cpp`:
- Most memory allocations - `void std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::_M_realloc_insert<graph::Edge<int> const&>(__gnu_cxx::__normal_iterator<graph::Edge<int>*, std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > >, graph::Edge<int> const&) in benchmarks` - 7349126 allocations
- Peak contributions - `BM_Dijkstra_AdjacencyMatrixGraph(benchmark::State&)` - 400,1MB
- Most temporary allocations - `std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > >::operator=(std::vector<graph::Edge<int>, std::allocator<graph::Edge<int> > > const&)` - 3232364 allocations
- Total system memory 16,1GB
- Total memory leaked 1,4kB  - все утечки не вызваны работой библиотеки, они происходят внутри библиотеки benchmarks
