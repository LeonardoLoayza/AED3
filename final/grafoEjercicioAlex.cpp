#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <queue>
using namespace std;

template<typename E>
class Edge
{
public:
	int from;
	int to;
	E   data;
	
	Edge(int f, int t, E d)
	{
		from = f;
		to   = t;
		data = d;
	}
};

template<typename N, typename E>
class Node
{
public:
	int           index;
	N             data;
	list<Edge<E>> edges;
	
	Node(int i, N d)
	{
		index = i;
		data  = d;
	}
	
	void addEdge(int to, E d)
	{
		edges.push_back(Edge<E>(index, to, d));
	}
	
	void removeEdge(int to)
	{
		for (auto it = edges.begin(); it != edges.end(); ++it)
		{
			if (it->to == to) { 
				edges.erase(it);
				break; 
			}
		}
	}
	
	bool hasEdge(int to)
	{
		for (auto& e : edges)
			if (e.to == to) return true;
		return false;
	}
};

template<typename N, typename E>
class Graph
{
private:
	int numVertices;
	bool directed;
	vector<Node<N,E>> nodes;
	
public:
	Graph(bool dir = false);
	
	int         addNode(N data);
	void        removeNode(int u);
	void        addEdge(int u, int v, E data);
	void        removeEdge(int u, int v);
	bool        hasEdge(int u, int v);
	Node<N,E>&  getNode(int u);
	int         vertexCount();
	void        print();
	vector<int> findPath(int from, int to);
	void        precalcAllPaths();
	vector<int> findPathFromPreCalc(int from, int to);
	
private:
	void validateVertex(int u);
};

template<typename N, typename E>
Graph<N,E>::Graph(bool dir)
{
	numVertices = 0;
	directed    = dir;
}

template<typename N, typename E>
int Graph<N,E>::addNode(N data)
{
	nodes.push_back(Node<N,E>(numVertices, data));
	numVertices++;
	return numVertices - 1;
}

template<typename N, typename E>
void Graph<N,E>::removeNode(int u)
{
	validateVertex(u);
	
	for (int i = 0; i < numVertices; i++)
	{
		if (i == u) continue;
		for (auto it = nodes[i].edges.begin(); it != nodes[i].edges.end(); )
		{
			if (it->to == u)
				it = nodes[i].edges.erase(it);
			else
			{
				if (it->to > u) // que hace aca ?
					it->to--;
				++it;
			}
		}
	}
	
	nodes.erase(nodes.begin() + u);
	numVertices--;
	
	for (int i = u; i < numVertices; i++)
		nodes[i].index = i;
}

template<typename N, typename E>
void Graph<N,E>::addEdge(int u, int v, E data)
{
	validateVertex(u);  validateVertex(v);
	nodes[u].addEdge(v, data);
	if (!directed)
		nodes[v].addEdge(u, data);
}

template<typename N, typename E>
void Graph<N,E>::removeEdge(int u, int v)
{
	validateVertex(u);  validateVertex(v);
	nodes[u].removeEdge(v);
	if (!directed)
		nodes[v].removeEdge(u);
}

template<typename N, typename E>
bool Graph<N,E>::hasEdge(int u, int v)
{
	validateVertex(u);  validateVertex(v);
	return nodes[u].hasEdge(v);
}

template<typename N, typename E>
Node<N,E>& Graph<N,E>::getNode(int u)
{
	validateVertex(u);
	return nodes[u];
}

template<typename N, typename E>
int Graph<N,E>::vertexCount()
{
	return numVertices;
}

template<typename N, typename E>
void Graph<N,E>::print()
{
	for (int u = 0; u < numVertices; u++)
	{
		cout << nodes[u].index << "(" << nodes[u].data << ") -> ";
		for (auto& e : nodes[u].edges)
			cout << e.to << "(" << e.data << ") ";
		cout << "\n";
	}
}

template<typename N, typename E>
vector<int> Graph<N,E>::findPath(int from, int to)
{
	validateVertex(from);  validateVertex(to);
	
	/* algorithm to find a path between 'from' and 'to', traversing the graph */
	// N - node, E edge 
	if(from == to ) return {from}; 
	const E INF = 1e9; 
	
	vector<E> dist(numVertices,INF); 
	vector<int> parent(numVertices,-1); 
	vector<bool> visited(numVertices,false);
	
	// <E,int> distancia acumulada, id del nodo 
	// que cosas tiene este priority_queue ?
	// solo distancia acumulada, con id del nodo 
	priority_queue<pair<E,int> ,
				   vector<pair<E,int>>, 
				   greater<pair<E,int> >> pq; 
	
	dist[from]=0;
	pq.push({0,from});
	
	while(!pq.empty()){
		// sacamos el primer elemento 
		// auto[currentDist, curr]=pq.top(); 
		pair<E,int> topPair = pq.top(); 
		pq.pop(); 
		
		E currentDist = topPair.first; 
		int curr = topPair.second;
		
		if(visited[curr]) // en caso ya lo visite,zafo, sino lo proceso
			continue; 
		
		// proceso el indice del nodo curr,
		// pero si es curr la llegada (to) zafari 
		visited[curr]=true; 
		
		if(curr==to)
			break; 
		
		// visiatare todos los aristas del nodo actual 
		for(auto&edge : nodes[curr].edges) {
			int neighbor=edge.to; 
			E weight = edge.data; // peso de la arista
			// si la distancia de curr + el peso de mi edge actual 
			// es menor a la distancia que tengo guardada 
			// en el vector dist de nieghbor. ENTONCES LA GUARDO 
			if(!visited[neighbor] && dist[curr] + weight < dist[neighbor] ){
				dist[neighbor]=dist[curr]+weight; 
				parent[neighbor]=curr; 
				pq.push({dist[neighbor],neighbor}); // distancia del nodo, nodo
			}
		}
	}
	vector<int>path; 
	if(dist[to]==INF) // no encontramos ni pincho
		return path; 
	
	for(int i=to;i!=-1;i=parent[i]){
		path.push_back(i); 
	}
	reverse(path.begin(),path.end());
	return path;
}

template<typename N, typename E>
void Graph<N,E>::precalcAllPaths()
{
	/* algorithm to compute paths between all pairs of nodes and store them in a precomputed structure */
}

template<typename N, typename E>
vector<int> Graph<N,E>::findPathFromPreCalc(int from, int to)
{
	vector<int> path;
	
	/* retrieves the precomputed path between 'from' and 'to' in O(1), assumes precalcAllPaths() was called first */
	
	return path;
}

template<typename N, typename E>
void Graph<N,E>::validateVertex(int u)
{
	assert(u >= 0 && u < numVertices);
}

int main()
{
	Graph<char, int> g;
	
	int a = g.addNode('A');
	int b = g.addNode('B');
	int c = g.addNode('C');
	int d = g.addNode('D');
	
	g.addEdge(a, b, 5);
	g.addEdge(a, c, 3);
	g.addEdge(b, d, 7);
	g.addEdge(c, d, 2);
	
	cout << "Initial:\n";
	g.print();
	
	g.removeNode(b);
	cout << "\nAfter removeNode(b):\n";
	g.print();
	
	return 0;
}
