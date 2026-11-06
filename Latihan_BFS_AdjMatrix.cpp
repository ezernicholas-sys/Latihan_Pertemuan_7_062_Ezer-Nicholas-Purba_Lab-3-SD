
#include <iostream>
#include <queue>
using namespace std;

const int N = 6;

int graph[N][N] = {0};
bool visited[N] = {false};

void BFS(int start) {
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nUrutan vertex yang dikunjungi: ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << char(current + 'A') << " ";

        for (int i = 0; i < N; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    cout << endl;
}

int main() {
    int jumlahEdge;
    char asal, tujuan;

    cout << "=== PROGRAM BFS ===" << endl;
    cout << "Vertex: A, B, C, D, E, F" << endl;

    cout << "Masukkan jumlah edge: ";
    cin >> jumlahEdge;

    for (int i = 0; i < jumlahEdge; i++) {
        cout << "Edge ke-" << i + 1 << " (contoh A B): ";
        cin >> asal >> tujuan;

        int u = asal - 'A';
        int v = tujuan - 'A';

        if (u >= 0 && u < N && v >= 0 && v < N) {
            graph[u][v] = 1;
            graph[v][u] = 1;
        } else {
            cout << "Vertex tidak valid!" << endl;
            i--;
        }
    }

    char awal;
    cout << "\nMasukkan vertex awal BFS: ";
    cin >> awal;

    int start = awal - 'A';

    if (start >= 0 && start < N) {
        BFS(start);
    } else {
        cout << "Vertex awal tidak valid!" << endl;
    }

    return 0;
}
