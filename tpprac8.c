#include <stdio.h>
#include <stdlib.h>

// Graph data structure
struct Graph {
    int numNodes;
    int** adjacencyMatrix;
};

// Function to create a graph
struct Graph* createGraph(int numNodes) {
    int i, j;

    // Allocate memory for the graph structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;

    // Allocate memory for the adjacency matrix
    graph->adjacencyMatrix = (int**)malloc(numNodes * sizeof(int*));
    for (i = 0; i < numNodes; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(numNodes * sizeof(int));

        // Initialize the adjacency matrix with 0 (no connection)
        for (j = 0; j < numNodes; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge between two nodes in the graph
void addEdge(struct Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numNodes && dest >= 0 && dest < graph->numNodes) {
        graph->adjacencyMatrix[src][dest] = 1;
        graph->adjacencyMatrix[dest][src] = 1;
    }
}

// Function to detect a single node failure in a graph
int detectNodeFailure(struct Graph* graph) {
    int i, j;
    int failedNode = -1;
    int connectedNodes;

    // Iterate over each node
    for (i = 0; i < graph->numNodes; i++) {
        connectedNodes = 0;

        // Check the number of connections for each node
        for (j = 0; j < graph->numNodes; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                connectedNodes++;
            }
        }

        // If a node has no connections, it has failed
        if (connectedNodes == 0) {
            // If another node has already failed, it's not a single node failure
            if (failedNode != -1) {
                return -1;
            }

            failedNode = i;
        }
    }

    return failedNode;
}

// Function to free the memory allocated for the graph
void freeGraph(struct Graph* graph) {
    int i;

    if (graph != NULL) {
        for (i = 0; i < graph->numNodes; i++) {
            free(graph->adjacencyMatrix[i]);
        }

        free(graph->adjacencyMatrix);
        free(graph);
    }
}

int main() {
    struct Graph* graph;
    int numNodes, src, dest, i;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    // Create the graph
    graph = createGraph(numNodes);

    printf("Enter the edges (source destination):\n");
    while (1) {
        scanf("%d %d", &src, &dest);

        // Enter -1 -1 to stop entering edges
        if (src == -1 && dest == -1) {
            break;
        }

        // Add the edge to the graph
        addEdge(graph, src, dest);
    }

    // Detect node failure
    int failedNode = detectNodeFailure(graph);

    if (failedNode == -1) {
        printf("Multiple nodes have failed or no nodes have failed.\n");
    }
    else {
        printf("Node %d has failed.\n", failedNode);
    }

    // Free the memory allocated for the graph
    freeGraph(graph);

    return 0;
}
