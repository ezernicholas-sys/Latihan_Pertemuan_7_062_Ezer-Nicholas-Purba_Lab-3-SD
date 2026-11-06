
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 6;
const int INF = INT_MAX;

// Menyimpan graf
int matrix[N][N] = {0};
vector<pair<int, int>> graph[N];

// Mengubah angka menjadi huruf A-F
char vertex(int x) {
    return char(x + 'A');
}

// ===============================
// BAGIAN 1: INPUT GRAF UNTUK BFS
// ===============================

void inputBFS() {
    int jumlahEdge;
    char asal, tujuan;

    cout << "\n=== INPUT GRAF BFS ===\n";
    cout << "Vertex tersedia: A, B, C, D, E, F\n";
    cout << "Masukkan jumlah edge: ";
    cin >> jumlahEdge;

    for (int i = 0; i < jumlahEdge; i++) {
        cout << "Edge ke-" << i + 1 << " (A B): ";
        cin >> asal >> tujuan;

        asal = toupper(asal);
        tujuan = toupper(tujuan);

        int u = asal - 'A';
        int v = tujuan - 'A';

        if (u >= 0 && u < N && v >= 0 && v < N && u != v) {
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        } else {
            cout << "Vertex tidak valid!\n";
            i--;
        }
    }
}

// ===============================
// BAGIAN 2: ALGORITMA BFS
// ===============================

void BFS(int start) {
    bool visited[N] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nUrutan vertex BFS: ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << vertex(current) << " ";

        for (int i = 0; i < N; i++) {
            if (matrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    cout << endl;
}

// ===============================
// BAGIAN 3: GRAF NAVIGASI
// ===============================

void buatGrafNavigasi() {
    // A - B : 4
    graph[0].push_back({1, 4});
    graph[1].push_back({0, 4});

    // A - C : 2
    graph[0].push_back({2, 2});
    graph[2].push_back({0, 2});

    // B - C : 1
    graph[1].push_back({2, 1});
    graph[2].push_back({1, 1});

    // B - D : 5
    graph[1].push_back({3, 5});
    graph[3].push_back({1, 5});

    // B - E : 3
    graph[1].push_back({4, 3});
    graph[4].push_back({1, 3});

    // C - D : 8
    graph[2].push_back({3, 8});
    graph[3].push_back({2, 8});

    // C - E : 6
    graph[2].push_back({4, 6});
    graph[4].push_back({2, 6});

    // D - E : 2
    graph[3].push_back({4, 2});
    graph[4].push_back({3, 2});

    // D - F : 4
    graph[3].push_back({5, 4});
    graph[5].push_back({3, 4});

    // E - F : 3
    graph[4].push_back({5, 3});
    graph[5].push_back({4, 3});
}

// ===============================
// BAGIAN 4: ALGORITMA DIJKSTRA
// ===============================

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

    for (int i = tujuan; i != -1; i = parent[i]) {
        path.push_back(i);
    }

    reverse(path.begin(), path.end());

    cout << "Rute tercepat: ";

    for (int i = 0; i < path.size(); i++) {
        cout << vertex(path[i]);

        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal jarak: " << dist[tujuan] << " km\n";
}

// ===============================
// BAGIAN 5: MENU DIJKSTRA
// ===============================

void menuDijkstra() {
    cout << "\n=== SISTEM NAVIGASI KOTA ===\n";

    cout << "\nRUTE TERPENDEK DARI A KE SEMUA LOKASI:\n";

    for (int i = 0; i < N; i++) {
        cout << "\nTujuan " << vertex(i) << ":\n";
        dijkstra(0, i);
    }

    char awal, tujuan;

    cout << "\n=== CARI RUTE BERDASARKAN INPUT ===\n";

    cout << "Masukkan lokasi awal (A-F): ";
    cin >> awal;

    cout << "Masukkan lokasi tujuan (A-F): ";
    cin >> tujuan;

    awal = toupper(awal);
    tujuan = toupper(tujuan);

    int start = awal - 'A';
    int end = tujuan - 'A';

    if (start >= 0 && start < N &&
        end >= 0 && end < N) {
        dijkstra(start, end);
    } else {
        cout << "Lokasi tidak valid!\n";
    }
}

// ===============================
// BAGIAN 6: PROGRAM UTAMA
// ===============================

int main() {
    int pilihan;
    char awal;

    do {
        cout << "\n================================\n";
        cout << "       PROGRAM GRAF C++\n";
        cout << "================================\n";
        cout << "1. Breadth First Search (BFS)\n";
        cout << "2. Sistem Navigasi (Dijkstra)\n";
        cout << "3. Keluar\n";
        cout << "================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {

            case 1:
                inputBFS();

                cout << "\nMasukkan vertex awal (A-F): ";
                cin >> awal;

                awal = toupper(awal);

                if (awal >= 'A' && awal <= 'F') {
                    BFS(awal - 'A');
                } else {
                    cout << "Vertex awal tidak valid!\n";
                }
                break;

            case 2:
                menuDijkstra();
                break;

            case 3:
                cout << "\nProgram selesai. Terima kasih!\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 3);

    return 0;
}
