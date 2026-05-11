// Short OpenMP BFS and DFS Program
// Compile: g++ -fopenmp assi1.cpp -o assi1
// Run: .\assi1.exe

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

vector<vector<int>> g;

void seqBFS(int s)
{
    vector<int> vis(g.size(), 0);
    queue<int> q;

    q.push(s);
    vis[s] = 1;

    cout << "\nSequential BFS: ";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << u << " ";

        for (int v : g[u])
        {
            if (!vis[v])
            {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
}

void parBFS(int s)
{
    vector<int> vis(g.size(), 0);
    queue<int> q;

    q.push(s);
    vis[s] = 1;

    cout << "\nParallel BFS: ";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << u << " ";

        #pragma omp parallel for
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i];

            if (!vis[v])
            {
                vis[v] = 1;

                #pragma omp critical
                q.push(v);
            }
        }
    }
}

void seqDFS(int s)
{
    vector<int> vis(g.size(), 0);
    stack<int> st;

    st.push(s);

    cout << "\nSequential DFS: ";

    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        if (!vis[u])
        {
            vis[u] = 1;
            cout << u << " ";

            for (int v : g[u])
                st.push(v);
        }
    }
}

void parDFS(int s)
{
    vector<int> vis(g.size(), 0);
    stack<int> st;

    st.push(s);

    cout << "\nParallel DFS: ";

    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        if (!vis[u])
        {
            vis[u] = 1;
            cout << u << " ";

            #pragma omp parallel for
            for (int i = 0; i < g[u].size(); i++)
            {
                #pragma omp critical
                st.push(g[u][i]);
            }
        }
    }
}

int main()
{
    int n, e;

    cout << "Enter nodes and edges: ";
    cin >> n >> e;

    g.resize(n);

    cout << "Enter edges:\n";

    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
    }

    int start;

    cout << "Enter starting node: ";
    cin >> start;

    double t1, t2;

    t1 = omp_get_wtime();
    seqBFS(start);
    t2 = omp_get_wtime();
    cout << "\nTime: " << t2 - t1 << " sec\n";

    t1 = omp_get_wtime();
    parBFS(start);
    t2 = omp_get_wtime();
    cout << "\nTime: " << t2 - t1 << " sec\n";

    t1 = omp_get_wtime();
    seqDFS(start);
    t2 = omp_get_wtime();
    cout << "\nTime: " << t2 - t1 << " sec\n";

    t1 = omp_get_wtime();
    parDFS(start);
    t2 = omp_get_wtime();
    cout << "\nTime: " << t2 - t1 << " sec\n";

    return 0;
}