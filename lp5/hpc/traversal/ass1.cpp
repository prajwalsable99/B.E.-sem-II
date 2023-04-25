#include <iostream>
#include <stack>
#include<queue>
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
    // ask the user for the number of nodes in the graph
//    int n;
//    cout << "Enter the number of nodes: ";
//    cin >> n;
//
//    // initialize an empty adjacency list for the graph
//    vector<vector<int>> adj_list(n);
//
//    // ask the user to input the neighbors of each node
//    for (int i = 0; i < n; i++) {
//        int num_neighbors;
//        cout << "Enter the number of neighbors of node " << i << ": ";
//        cin >> num_neighbors;
//
//        cout << "Enter the neighbors of node " << i << ": ";
//        for (int j = 0; j < num_neighbors; j++) {
//            int neighbor;
//            cin >> neighbor;
//            adj_list[i].push_back(neighbor);
//        }
//    }
//
//    // starting node for DFS
//    int start_node;
//    cout << "Enter the starting node for DFS: ";
//    cin >> start_node;
    
    
    vector<vector<int>> adj_list =
//     {{1, 2}, {0, 3}, {0}, {1}};
//      {{1, 2}, {0, 3, 4}, {0, 5, 6}, {1, 7}, {1}, {2}, {2}, {3}};
//		 {{1, 2}, {0, 3, 4}, {0, 5, 6}, {1, 7, 8}, {1, 9, 10}, {2, 11, 12}, {2, 13, 14}, {3, 15},
//                            {3}, {4}, {4}, {5}, {5}, {6}, {6}, {7}};


    int start_node=0;
    
    
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
    
    
     start_time = chrono::high_resolution_clock::now();
    dfs_sequential(adj_list, start_node);
     end_time = chrono::high_resolution_clock::now();
     duration_seq = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Sequential DFS execution time: " << duration_seq.count() << " ms" << endl;

    // measure the execution time of DFS in parallel
    start_time = chrono::high_resolution_clock::now();
    dfs_parallel(adj_list, start_node);
    end_time = chrono::high_resolution_clock::now();
    duration_par = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "Parallel DFS execution time: " << duration_par.count() << " ms" << endl;

    // calculate the speedup
     speedup = static_cast<double>(duration_seq.count()) / duration_par.count();
    cout << "Speedup: " << speedup << endl;
    
 	return 0;   
}

