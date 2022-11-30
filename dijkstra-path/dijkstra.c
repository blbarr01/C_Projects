#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* graph code */

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
} ;

typedef struct AdjListNode AdjListNode;

 struct AdjList
{
    AdjListNode *head;
};

typedef struct AdjList AdjList; 
    /* data */


// V will be # of vertecies, size of array
typedef struct
{
    int v;
    AdjList *array;
} Graph;

// function to create a new node
AdjListNode *newNode(int dest, int weight)
{
    // allocate space
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    // instantiate values
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int v)
{
    // allocate memory for the graph
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->v = v;

    // allocate memory for the adjlist
    graph->array = (AdjList *)malloc(v * sizeof(AdjList));

    // set the head of every element in the adjacency list to null
    for (int i = 0; i < v; i++)
    {
        graph->array->head = NULL;
    }

    return graph;
}

void addEdge(Graph *g, int src, int dest, int weight)
{
    // add an edge from src to dest
    // add new node to the adjaceny list of src node
    AdjListNode *node = newNode(dest, weight);
    node->next = g->array[src].head;
    g->array[src].head = node;

    // add an edge from dest to src
    node = newNode(src, weight);
    node->next = g->array[dest].head;
    g->array[dest].head = node;
}

/* heap code */

struct minHeapNode
{
    int v,
        dist;
};

typedef struct minHeapNode minHeapNode;

struct minHeap
{
    // number of nodes currently present
    int size,

        capacity;

    // for the decreaseKey()
    int *pos;
    minHeapNode **array;
};

typedef struct minHeap minHeap;

minHeapNode *newMinHeapNode(int v, int dist)
{
    minHeapNode *node = (minHeapNode *)malloc(sizeof(minHeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

minHeap *createMinHeap(int c)
{
    minHeap *heap = (minHeap *)malloc(sizeof(minHeap));
    heap->pos = (int *)malloc(c * sizeof(int));
    heap->size = 0;
    heap->capacity = c;
    heap->array = (minHeapNode **)malloc(c *sizeof(minHeapNode*));

    return heap;
}

//utility to swap npdes within heap
// neede for heapify

void swapMinHeapNode( minHeapNode **a, minHeapNode **b){
    minHeapNode *t = *a;
    // remember we are passing addresses 
    *a = *b;
    *b = t;
}

void minHeapify( minHeap *heap, int i){
    int smallest,
    left,
    right;

    smallest = i;
    left = (2*i)+1; 
    right = (2*i)+2; 

    if(left < heap->size && 
    heap->array[left]->dist < heap->array[smallest]->dist ){
        smallest = left; 
    }

    if (right < heap->size &&
    heap->array[right]->dist < heap->array[smallest]->dist){
        smallest = right; 
    }

    // in the event we need to make a swap 
    if(smallest != i){
            minHeapNode *smallestNode = heap->array[smallest];
            minHeapNode *idxNode = heap->array[i];

            // swap positions 
            heap->pos[smallestNode->v] = i;
            heap->pos[idxNode->v] = smallest; 


            //swap nodes
            swapMinHeapNode(&heap->array[smallest], &heap->array[i]);
            // recursive call 
            minHeapify(heap, smallest); 

    }
}


int isEmpty( minHeap *heap){
    return heap->size == 0; 
}

minHeapNode* extractMin(minHeap *heap){
    if(isEmpty(heap)){
        return NULL;
    }
    // store root node 
    minHeapNode *root  = heap->array[0];

    //replace root node with last node 
    minHeapNode *lastNode = heap->array[(heap->size-1)];
    heap->array[0] = lastNode; 

    //update position of last node 
    heap->pos[root->v] = heap->size-1; 
    heap->pos[lastNode->v] = 0; 

    // reduce heap size and heapify root 
    --heap->size; 
    minHeapify(heap, 0);

    return root;  
}

/**
 * 
 * function to decrease dist value  of a given vertex v
 * uses pos[] of min heapt o get the current index
 * of node in min heap
 * 
 */

void decreaseKey( minHeap *heap, int v, int dist){
    //get index of v in the array 
    int i = heap->pos[v]; 

    // get the nopde and update dist value
    heap->array[i]->dist = dist; 
    
    // travel up while the tree is not heapified 
    // if the distance of the child is less than the value of its parent
    while(i && heap->array[i]->dist < heap->array[(i-1)/2]->dist){
        //swap the node w/ its parent
        heap->pos[heap->array[i]->v] = (i -1) / 2; 
        heap->pos[heap->array[(i-1)/2]->v] = i; 

        swapMinHeapNode(&heap->array[i], &heap->array[(i-1)/2]);

        i = (i - 1) / 2; 
    }
}

bool isInMinHeap( minHeap *heap, int v){
    if(heap->pos[v] < heap->size)
    return true;
    return false;
}

void printArr(int *dist, int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function

void dijkstra( Graph *g, int src){
    
    // get the number of vertices 
    int v = g->v; 
    int dist[v];
    // initialize minheap
    minHeap *minHeap = createMinHeap(v); 

    //  load all the verticies into the min heap 
    for(int i = 0; i < v; v++){
        dist[i] = INT_MAX; 
        minHeap->array[v] = newMinHeapNode(i,dist[i]); 
        minHeap->pos[v] = v; 
    } 

    // set the distance of the src node to 0 so it extracts first
    minHeap->array[src] = newMinHeapNode(src, dist[src]); 
    minHeap->pos[src] = src; 
    dist[src] = 0; 
    decreaseKey(minHeap, src, dist[src]); 

    // set the initial size of min heap to v
    minHeap->size = v; 

    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.

    while(!isEmpty(minHeap)){

        //extract vertex with minimum distance value 
        // pick the path with the least cost
        minHeapNode *node =  extractMin(minHeap); 

        //store extracted vertex number
        int u = node->v;

        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values

        AdjListNode *pCrawl = g->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance  

            if(isInMinHeap(minHeap,v) 
            && dist[u] != INT_MAX 
            && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                //update distance value in min heap 
                decreaseKey(minHeap, v, dist[v]); 
            }  
            pCrawl = pCrawl->next; 
        }
        
    }
    //print the shortest distances
    printArr(dist, v); 
}


int main()
{
    // create the graph given in above fugure
    int V = 9;
    Graph *graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
 
    dijkstra(graph, 0);
 
    return 0;
}