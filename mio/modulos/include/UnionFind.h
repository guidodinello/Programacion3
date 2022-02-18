#ifndef _UnionFind_H
#define _UnionFind_H

#include "grafo.h"

typedef struct _rep_UnionFind *UnionFind;
typedef int TNodo;

UnionFind MakeUnionFind(TGrafo S);
TNodo Find(TNodo nodo, UnionFind S);
void Union(TNodo a, TNodo b, UnionFind S);
void showUnionFind(UnionFind S);
#endif
