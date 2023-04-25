#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// function to perform BFS in sequential
void bfs_sequential(vector<vector<int>> adj_list, int start_node) {
    int n = adj_list.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        cout << curr_node << " ";

        for (int neighbor : adj_list[curr_node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// function to perform BFS in parallel
void bfs_parallel(vector<vector<int>> adj_list, int start_node) {
    int n = adj_list.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int curr_node = q.front();

            #pragma omp critical
            {
                q.pop();
            }

            cout << curr_node << " ";

            for (int neighbor : adj_list[curr_node]) {
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        q.push(neighbor);
                    }
                    visited[neighbor] = true;
                }
            }
        }
    }
}

int main() {
    // adjacency list representation of a graph
    vector<vector<int>> adj_list = {
        {1, 2},     // neighbors of node 0
        {0, 3, 4},  // neighbors of node 1
        {0, 5},     // neighbors of node 2
        {1},        // neighbors of node 3
        {1, 5},     // neighbors of node 4
        {2, 4}      // neighbors of node 5
    };

    // starting node for BFS
    int start_node = 0;

    // measure the execution time of BFS in sequential
    auto start_time = chrono::high_resolution_clock::now();
    bfs_sequential(adj_list, start_node);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration_seq = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Sequential BFS execution time: " << duration_seq.count() << " ms" << endl;

    // measure the execution time of BFS in parallel
    start_time = chrono::high_resolution_clock::now();
    bfs_parallel(adj_list, start_node);
    end_time = chrono::high_resolution_clock::now();
    auto duration_par = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Parallel BFS execution time: " << duration_par.count() << " ms" << endl;

    // calculate the speedup
    double speedup = static_cast<double>(duration_seq.count()) / duration_par.count();
    cout << "Speedup: " << speedup << endl;

    return 0;
}

