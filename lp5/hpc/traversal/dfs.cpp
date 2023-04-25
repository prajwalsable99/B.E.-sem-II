#include <iostream>
#include <stack>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// function to perform DFS in sequential
void dfs_sequential(vector<vector<int>> adj_list, int start_node) {
    int n = adj_list.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start_node);
    visited[start_node] = true;

    while (!s.empty()) {
        int curr_node = s.top();
        s.pop();
        cout << curr_node << " ";

        for (int neighbor : adj_list[curr_node]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// function to perform DFS in parallel
void dfs_parallel(vector<vector<int>> adj_list, int start_node) {
    int n = adj_list.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start_node);
    visited[start_node] = true;

    while (!s.empty()) {
        int size = s.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int curr_node;

            #pragma omp critical
            {
                curr_node = s.top();
                s.pop();
            }

            cout << curr_node << " ";

            for (int neighbor : adj_list[curr_node]) {
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        s.push(neighbor);
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

    // starting node for DFS
    int start_node = 0;

    // measure the execution time of DFS in sequential
    auto start_time = chrono::high_resolution_clock::now();
    dfs_sequential(adj_list, start_node);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration_seq = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Sequential DFS execution time: " << duration_seq.count() << " ms" << endl;

    // measure the execution time of DFS in parallel
    start_time = chrono::high_resolution_clock::now();
    dfs_parallel(adj_list, start_node);
    end_time = chrono::high_resolution_clock::now();
    auto duration_par = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Parallel DFS execution time: " << duration_par.count() << " ms" << endl;

    // calculate the speedup
    double speedup = static_cast<double>(duration_seq.count()) / duration_par.count();
    cout << "Speedup: " << speedup << endl;

    return 0;
}

