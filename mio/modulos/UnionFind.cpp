struct nodo{
    int elem;
    nodo* parent;
    int hijos;
};
typedef nodo* UnionFind;

//ConjuntoNodos puede ser una lista de nodos

void crearUF(ConjuntoNodos S){
    UnionFind nuevo = new nodo;
    For each node in S 
        nuevo -> elem = S -> elem;
        nuevo -> parent = nuevo;
        nuevo -> hijos = 0;
}

UnionFind Find(UnionFind A){
    if (A -> parent == A) return A;
    else 
        UnionFind padre = Find(A);
        A -> parent = padre;
        return padre;
}

void Union(UnionFind A, UnionFind B){
    If (A -> hijos < B -> hijos){
        Find(A) -> parent = Find(B) -> parent;
        B -> hijos += A -> hijos + 1;
    } else {
        Find(B) -> parent = Find(A) -> parent;
        A -> hijos += B -> hijos + 1;
    }
}
