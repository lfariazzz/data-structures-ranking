#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "atleta.h"

typedef int (*CmpFn)(const Atleta*, const Atleta*);

long bubble_sort    (Atleta *v, int n, CmpFn cmp);
long insertion_sort (Atleta *v, int n, CmpFn cmp);
long selection_sort (Atleta *v, int n, CmpFn cmp);
long quick_sort     (Atleta *v, int n, CmpFn cmp);
long merge_sort     (Atleta *v, int n, CmpFn cmp);

long _quick_sort_rec(Atleta *v, int esq, int dir, CmpFn cmp);
long _merge_sort_rec(Atleta *v, Atleta *aux, int esq, int dir, CmpFn cmp);

#endif