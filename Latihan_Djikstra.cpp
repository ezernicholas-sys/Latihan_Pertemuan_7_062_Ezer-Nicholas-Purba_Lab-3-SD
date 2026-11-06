
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 6;
const int INF = INT_MAX;

vector<pair<int, int>> graph[N];

char lokasi(int x) {
    return char(x + 'A');
}

void tambahEdge(int u, int v, int jarak) {
    graph[u].push_back({v, jarak});
    graph[v].push_back({u, jarak});
}

void dijkstra(int start, int tujuan) {
    vector<int> dist(N, INF);
    vector<int> parent(N, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int jarak = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (jarak > dist[u]) {
            continue;
        }

        for (auto edge : graph[u]) {
            int v = edge.first;
            int bobot = edge.second;

            if (dist[u] + bobot < dist[v]) {
                dist[v] = dist[u] + bobot;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    if (dist[tujuan] == INF) {
        cout << "Tidak ada rute yang tersedia.\n";
        return;
    }

    vector<int> path;
    int current = tujuan;

    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "Rute tercepat: ";

    for (int i = 0; i < path.size(); i++) {
        cout << lokasi(path[i]);

        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal jarak: " << dist[tujuan] << " km\n";
}

int main() {
    // Membuat graf berdasarkan soal
    tambahEdge(0, 1, 4); // A - B
    tambahEdge(0, 2, 2); // A - C
    tambahEdge(1, 2, 1); // B - C
    tambahEdge(1, 3, 5); // B - D
    tambahEdge(1, 4, 3); // B - E
    tambahEdge(2, 3, 8); // C - D
    tambahEdge(2, 4, 6); // C - E
    tambahEdge(3, 4, 2); // D - E
    tambahEdge(3, 5, 4); // D - F
    tambahEdge(4, 5, 3); // E - F

    cout << "=== SISTEM NAVIGASI KOTA ===\n";

    // Bagian 1: Rute dari A ke semua lokasi
    cout << "\nRUTE TERPENDEK DARI A:\n";

    for (int i = 0; i < N; i++) {
        cout << "\nTujuan " << lokasi(i) << ":\n";
        dijkstra(0, i);
    }

    // Bagian 2: Input lokasi pengguna
    char awal, tujuan;

    cout << "\n=== CARI RUTE TERCEPAT ===\n";

    cout << "Masukkan lokasi awal (A-F): ";
    cin >> awal;

    cout << "Masukkan lokasi tujuan (A-F): ";
    cin >> tujuan;

    int start = awal - 'A';
    int end = tujuan - 'A';

    if (start >= 0 && start < N &&
        end >= 0 && end < N) {

        cout << "\nHasil rekomendasi navigasi:\n";
        dijkstra(start, end);

    } else {
        cout << "Lokasi tidak valid!\n";
    }

    return 0;
}
