## Архитектура

### Структура графов
![Структура графов](./images/arc.png?raw=true)

- `class Edge <edgeType>`
    - Поля
      - `std::int32_t m_from` - начало ребра
      - `std::int32_t m_to` - конец ребра
      - `edgeType m_edge` - структура ребра
    - Методы:
      - `Edge(std::int32_t from, std::int32_t to, edgeType edge)` - конструктор
      - `std::int32_t from()` - геттер начала ребра
      - `std::int32_t to()` - геттер конца ребра
      - `edgeType edge()` - геттер структуры ребра
- `class Graph <edgeType>`
  - Поля
    - `std::int32_t m_numberVertices` - количество вершин
    - `std::int32_t m_numberEdges` - количество ребер
    - `bool m_isDirected` - ориентирован ли граф
  - Виртуальные методы
    - `void addEdge(std::int32_t from, std::int32_t to, edgeType edge)` - добавление ребра
    - `void printEdges(std::ostream& ostream)` - выводит ребра
    - `void getNeighbours(std::int32_t vertex,
      std::vector<Edge<edgeType>>& neighbours)` - записывает в `neighbours` список соседей вершины `vertex`
    - `virtual bool isVertexesConnected(std::int32_t from, std::int32_t to)` - связаны ли вершины
  - Методы
    - `Graph(std::int32_t numberVertices, bool isDirected)` - конструктор
    - `bool isVertexValid(std::int32_t vertex)` - корректна ли вершина
    - `std::int32_t numberVertices()` - геттер количества вершин
    - `std::int32_t numberEdges()` - геттер количества ребер
    - `bool isDirected()` - геттер ориентированности графа
- `class AdjacencyListGraph <edgeType> : Graph <edgeType>`
  - Поля
    - `std::vector<std::vector<Edge<edgeType>>> m_adjList` - список смежности
- `class AdjacencyMatrixGraph <edgeType> : Graph <edgeType>`
  - Поля:
    - `std::vector<std::vector<std::optional<Edge<edgeType>>>> m_adjMatrix` - матрица смежности

### Алгоритмы

#### 1-k BFS
`class BFS_1k <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
  - `std::int32_t m_maxWeight` - значение k в терминах 1-k BFS
- Методы
  - `BFS_1k(Graph<edgeType>& graph, std::int32_t maxWeight)` - конструктор
  - `BFSResult run(std::int32_t startVertex)` - запуск алгоритма от вершины `startVertex`
  - `class BFSResult`
    - `std::vector<std::int32_t> m_distances` - вектор дистанций
    - `std::vector<std::int32_t> m_accessibility` - вектор достижимости
    - `const std::vector<std::int32_t>& distances()` - геттер вектора дистанций
    - `const std::vector<std::int32_t>& accessibility()` - геттер вектора достижимости

#### Алгоритм Дейкстры
`class Dijkstra <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `Dijkstra(Graph<edgeType>& graph)` - конструктор 
  - `DijkstraResult runStandard(std::int32_t start)` - алгоритм за $O(n^2)$
  - `DijkstraResult runOptimized(std::int32_t start)` - алгоритм за $O(E\log⁡V)$
  - `class DijkstraResult`
    - `std::vector<std::int64_t> m_distances` - вектор дистанций
    - `const std::vector<std::int64_t>& distances()` - геттер вектора дистанций

#### Алгоритм Флойда-Уоршелла
`class FloydWarshall <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph`
- Методы
  - `FloydWarshall(Graph<edgeType>& graph)` - конструктор
  - `FloydWarshallResult run()` - запуск алгоритма
  - `class FloydWarshallResult`
    - `std::vector<std::vector<std::int64_t>> m_distances`- массив попарных расстояний
    - `bool m_has_negative_cycles` - есть ли в графе цикл отрицательного веса
    - `const std::vector<std::vector<std::int64_t>>& distances()` - геттер вектора дистанций
    - `const bool has_negative_cycles()` - геттер индикатора наличия отрицательного цикла

#### Алгоритм Куна
`class KuhnMatching <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `KuhnMatching(Graph<edgeType>& graph)` - конструктор
  - `MatchingResult run()` - запуск алгоритма
  - `class MatchingResult`
    - `std::vector<std::int32_t> m_matching` - вектор паросочетаний. Если паросочетания с вершиной `v` не существует, то `matching[v]=−1`
    - `const std::vector<std::int32_t>& matching()` - гетер вектора паросочетаний.
  
#### Алгоритм Беллмана-Форда
`class BellmanFord <edgeType>`
- Поля
  - `Graph<edgeType>& m_graph` - граф
- Методы
  - `BellmanFord(Graph<edgeType>& graph)` - конструктор
  - `BellmanFord run(std::int32_t start_vertex)` - запуск алгоритма
  - `class BellmanFordResult`
    - `std::vector<std::int64_t> m_distances` - вектор дистанций
    - `bool m_has_negative_cycles` - есть ли в графе цикл отрицательного веса
    - `const std::vector<std::int64_t>& distances()` - гетер вектора дистанций
    - `const bool has_negative_cycles()` - геттер индикатора наличия отрицательного цикла