#include "Graph.h"
#include "maze.h"




template<typename V,typename E>
class maze : public Graph<V, E> // char = character/ board & int is edge weight
{
    public:
    maze() : Graph<V, E>(false) {} // Explicitly call the base class constructor || There may be circles so not acycle

    private:

    typedef Graph<V,E> g;
    typedef typename g::Vertex Vertex;
    typedef typename g::Edge Edge;

    typedef std::map<typename Graph<V,E>::Vertex, typename Graph<V,E>::Edge> trial;

    
    class Position : public Graph<V,E>::Vertex
    {
        private:
        
        Vertex* Start{nullptr};
        Vertex* End{nullptr};
        std::shared_ptr<Vertex> pos{nullptr};
        Position(const typename Graph<V, E>::Vertex* v) : pos{const_cast<typename Graph<V, E>::Vertex*>(v)} {}
    
    };
    
    class Path : public Graph<V,E>::Edge
    {
        private:
        typename Graph<V,E>::Edge* edge{nullptr};
        Path(const Edge* e) : edge{const_cast<Edge*>(e)} {}
    
    };

    protected :
    std::list<Vertex> vertices;
    std::list<Edge> edges;

};

//reference table for graph 

/*
ACCESSING H IN THIS EXAMPLE 

This is the big maze index for the grid on that index
blockRow = 0 / 4 = 0
blockCol = 8 / 4 = 2

This is the narrowed index
localRow = 0 % 4 = 0
localCol = 8 % 4 = 0

      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
r0    + + + + + + + + H +  +  +  +  +  +  +
r1    +     + +     +       +  +     +
r2    +     + +     + +     +  +     +
r3    + + + + + + + + + +  +  +  +  +  +  +
r4    + + + + + + + + + +  +  +  +  +  +  +
r5    +     + +     + +     +  +     +
r6    +     + +     + +     +  +     +
r7    + + + + + + + + + +  +  +  +  +  +  +
r8    O   + + + + + + + +  +  +  +  +  +  +
r9    +     + +     + +     +  +     +
r10   +     + +     + +     +  +     +
r11   + + + + + + + + + +  +  +  +  +  +  +
r12   + + + + + + + + + +  +  +  +  +  +  +
r13   +     + +     + +     +  +     +
r14   +     + +     + +     +  +     +
r15   + + + + + + + + + +  +  +  +  +  +  +
*/