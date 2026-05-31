#include <unordered_map>
#include <list>

template<typename V, typename E>
class Graph
{
    private:
    class ActualVertex;
    class ActualEdge;

    typedef std::unordered_map<ActualVertex*,ActualEdge*> IncidenceMap;
    //---------- nested ActualVertex class ---------
    class ActualVertex {
      public:
        V element;
        IncidenceMap outgoing; 
        IncidenceMap incoming;
        typename std::list<ActualVertex>::iterator pos;   // needed to erase from vertex_list
        ActualVertex(V elem) : element{elem} {}
    }; //---------- end of ActualVertex class ---------
    
    //---------- nested ActualEdge class ---------
    class ActualEdge {
      public:
        ActualVertex* origin; 
        ActualVertex* dest; 
        double weight; 
        E element; //  
        typename std::list<ActualEdge>::iterator pos;    // needed to erase from edge_list
        ActualEdge(ActualVertex* u, ActualVertex* v, double w, E e)
            : origin{u}, dest{v}, weight{w}, element{e} {}
    }; //---------- end of ActualEdge class ---------


  public:
    //---------- nested Vertex class ---------
    class Vertex {
      private:
        friend class Graph;
        ActualVertex* vert{nullptr};
        Vertex(const ActualVertex* v) : vert{const_cast<ActualVertex*>(v)} {}
        
      public:
        Vertex() {}
        V& operator*() const { return vert->element; }
        V* operator->() const { return &(vert->element); }
        bool operator==(Vertex other) const { return vert == other.vert; }
        bool operator!=(Vertex other) const { return vert != other.vert; }
        bool operator<(Vertex other) const { return vert < other.vert; }   // arbitrary rule as map/pq key
    };  //---------- end of Vertex ---------

    //---------- nested Edge class ---------
    class Edge {
      private:
        friend class Graph;
        ActualEdge* edge{nullptr};
        Edge(const ActualEdge* e) : edge{const_cast<ActualEdge*>(e)} {}
        
      public:
        Edge() {}
        int weight() const { return edge->weight; }
        E& operator*() const { return edge->element; }
        E* operator->() const {return &(edge->element); }
        bool operator==(Edge other) const { return edge == other.edge; }
        bool operator!=(Edge other) const { return edge != other.edge; }
        bool operator<(Edge other) const { return edge < other.edge; }    // arbitrary rule as map/pq key
    };

    private:
    // --------- Graph instance variables -----------
    std::list<ActualVertex> vertex_list;
    std::list<ActualEdge> edge_list;
    bool directed;

  public:    
    // Creates a new graph (directed or undirected, as specified by argument)
    Graph(bool is_directed) : directed{is_directed} {}

    // Returns true if graph is directed, false otherwise
    bool is_directed() const { return directed; }
    
    // Returns the number of vertices in the graph
    int num_vertices() const { return vertex_list.size(); }

    // Returns the number of edges in the graph
    int num_edges() const { return edge_list.size(); }
    
    // Returns a list of Vertex tokens
    std::list<Vertex> vertices() const {
        std::list<Vertex> result;
        for (const ActualVertex& v : vertex_list)      // Note: reference variable to get correct pointer
            result.emplace_back(Vertex(&v));
        return result;
    }

    // Returns a list of Edge tokens
    std::list<Edge> edges() const {
        std::list<Edge> result;
        for (const ActualEdge& e : edge_list)         // Note: reference variable to get correct pointer
            result.push_back(Edge(&e));
        return result;
    }

    // Return true if there exists an edge from u to v, false otherwise

    bool has_edge(Vertex u, Vertex v) const {
        return (u.vert->outgoing.count(v.vert) == 1);
    }
    
    // Return the edge from u to v; undefined behavior if no such edge exists
    Edge get_edge(Vertex u, Vertex v) const {
        return Edge(u.vert->outgoing.find(v.vert)->second); // find returns {ActualVertex*,ActualEdge*}
    }
    ////////////////////////////////////////

    // Returns the number of outgoing (or incoming) edges for Vertex v
    
    // UTILIZE WITH NEIGHBORS AND ENDPOINTS
    int degree(Vertex v, bool outgoing = true) const {
        IncidenceMap& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        return adj.size();
    }

    // Returns a list of outgoing (or incoming) Vertex tokens for neighbors of Vertex v

    // UTILIZE WITH ENPOINTS 
    std::list<Vertex> neighbors(Vertex v, bool outgoing = true) const {
        std::list<Vertex> result;
        IncidenceMap& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        for (auto p : adj)                          // p is {ActualVertex*,ActualEdge*} pair
            result.push_back(Vertex(p.first));
        return result;
    }
    
    // Returns a list of outgoing (or incoming) Edge tokens for Vertex v
    std::list<Edge> incident_edges(Vertex v, bool outgoing = true) const {
        std::list<Edge> result;
        IncidenceMap& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        for (auto p : adj)                          // p is {ActualVertex*,ActualEdge*} pair
            result.push_back(Edge(p.second));
        return result;
    }
    
    // Returns the (origin,destination) pair for Edge e
    std::pair<Vertex,Vertex> endpoints(Edge e) const {
        return {Vertex(e.edge->origin), Vertex(e.edge->dest)};
    }
    
    // Returns the opposite endpoint to Vertex v for Edge e
    Vertex opposite(Edge e, Vertex v) const {
        return Vertex(v.vert == e.edge->origin ? e.edge->dest : e.edge->origin);
    }

    // Create a new vertex storing given element, and return Vertex token
    Vertex insert_vertex(V elem) {
        auto iter = vertex_list.emplace(vertex_list.end(), elem);
        iter->pos = iter;             // save new vertex's position within vertex_list
        return Vertex(&*iter);        // wrap the pointer to newly stored ActualVertex
    }

    // Inserts new edge from u to v, storing given element, and given weight (default 1)
    // If edge already exists, updates weight and element for that existing edge.
    // Returns Edge token
    Edge insert_edge(Vertex u, Vertex v, double weight = 1.0, E elem = E()) {
        if (u.vert->outgoing.count(v.vert) == 0) {  // new edge
            auto iter = edge_list.insert(edge_list.end(), ActualEdge(u.vert, v.vert, weight, elem));
            iter->pos = iter;                   // save new edge's position within edge_list
            ActualEdge* stored = &*iter;        // pointer to newly stored ActualEdge
            // now add edge to adjacency maps for vertices
            u.vert->outgoing[v.vert] = stored;  // outgoing edge for u
            IncidenceMap& adj{directed ? v.vert->incoming : v.vert->outgoing};
            adj[u.vert] = stored;               // incoming edge for v (if directed graph)

            return Edge(stored);
        } else {                                     // update existing edge
            Edge e{get_edge(u,v)};
            e.edge->weight = weight;
            e.edge->element = elem;
            return e;
        }
    }

    // Remove edge e from the graph
    void erase(Edge e) {
        // first remove the edge from the endpoint adjacencies
        ActualVertex *u{e.edge->origin}, *v{e.edge->dest};
        u->outgoing.erase(v);
        IncidenceMap& adj{directed ? v->incoming : v->outgoing};
        adj.erase(u);

        // now remove the edge from the edge list
        edge_list.erase(e.edge->pos);
    }

    
    // Remove vertex v, and all its incident edges, from the graph
    void erase(Vertex v) {
        for (auto p : v.vert->outgoing) {         // p is {ActualVertex*,ActualEdge*} pair
            IncidenceMap& adj{directed ? p.first->incoming : p.first->outgoing};
            adj.erase(v.vert);                    // remove edge from opposite vertex's map
            edge_list.erase(p.second->pos);       // remove edge from overall edge_list
        }
        for (auto p : v.vert->incoming) {         // for undirected graph, incoming is empty
            p.first->outgoing.erase(v.vert);
            edge_list.erase(p.second->pos);
        }
        
        // now remove the vertex from the vertex list
        vertex_list.erase(v.vert->pos);
    }
    
};