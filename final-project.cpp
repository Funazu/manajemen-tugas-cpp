#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Struct untuk menyimpan data tugas
struct Task {
    int id;
    string name;
    int priority;
    Task* next;
};

Task* head = nullptr;
vector<vector<int>> adjList; // Graph adjacency list
int taskCount = 0;

// Tambah tugas ke linked list dan graph
void addTask(string name, int priority) {
    Task* newTask = new Task{taskCount, name, priority, nullptr};

    if (!head) head = newTask;
    else {
        Task* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newTask;
    }

    adjList.push_back({}); // tambahkan node di graph
    cout << "Tugas ditambahkan: ID=" << taskCount << ", Nama=" << name << endl;
    taskCount++;
}

// Tambahkan dependency antar tugas
void addDependency(int fromID, int toID) {
    if (fromID < taskCount && toID < taskCount) {
        adjList[fromID].push_back(toID);
        cout << "Dependency ditambahkan: " << fromID << " -> " << toID << endl;
    } else {
        cout << "ID tidak valid!" << endl;
    }
}

// Tampilkan semua tugas
void showTasks() {
    Task* temp = head;
    cout << "\nDaftar Tugas:\n";
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name << ", Prioritas: " << temp->priority << endl;
        temp = temp->next;
    }
}

// Cari tugas berdasarkan nama
void searchTask(const string& keyword) {
    Task* temp = head;
    bool found = false;
    cout << "\nHasil Pencarian Tugas:\n";
    while (temp) {
        if (temp->name.find(keyword) != string::npos) {
            cout << "ID: " << temp->id << ", Nama: " << temp->name << ", Prioritas: " << temp->priority << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Tidak ditemukan tugas dengan kata kunci tersebut.\n";
}

// Hapus tugas berdasarkan ID
void deleteTask(int id) {
    Task *temp = head, *prev = nullptr;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        cout << "Tugas tidak ditemukan!\n";
        return;
    }
    if (!prev) head = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Tugas ID " << id << " dihapus (data di graph tetap ada).\n";
}

// Ambil prioritas dari ID tugas
int getPriority(int id) {
    Task* temp = head;
    while (temp) {
        if (temp->id == id) return temp->priority;
        temp = temp->next;
    }
    return 1000;
}

// Topological Sort menggunakan queue manual
void showTaskOrder() {
    vector<int> indegree(taskCount, 0);
    for (auto& list : adjList)
        for (int v : list)
            indegree[v]++;

    int queue[100];
    int front = 0, rear = 0;

    for (int i = 0; i < taskCount; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    cout << "\nUrutan pengerjaan tugas (Topological Sort):\n";
    while (front < rear) {
        int u = queue[front++];

        Task* temp = head;
        while (temp && temp->id != u) temp = temp->next;
        if (temp)
            cout << temp->name << " (ID: " << u << ", Prioritas: " << temp->priority << ")\n";

        for (int v : adjList[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Menu Manajemen Tugas ===\n";
        cout << "1. Tambah Tugas\n";
        cout << "2. Tambah Dependency\n";
        cout << "3. Lihat Semua Tugas\n";
        cout << "4. Lihat Urutan Tugas (Topological Sort)\n";
        cout << "5. Hapus Tugas\n";
        cout << "6. Cari Tugas\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama;
            int prioritas;
            cout << "Masukkan nama tugas: ";
            getline(cin, nama);
            cout << "Masukkan prioritas: ";
            cin >> prioritas;
            addTask(nama, prioritas);
        }
        else if (pilihan == 2) {
            int from, to;
            cout << "Masukkan ID tugas sumber: "; cin >> from;
            cout << "Masukkan ID tugas tujuan: "; cin >> to;
            addDependency(from, to);
        }
        else if (pilihan == 3) {
            showTasks();
        }
        else if (pilihan == 4) {
            showTaskOrder();
        }
        else if (pilihan == 5) {
            int id;
            cout << "Masukkan ID tugas yang ingin dihapus: ";
            cin >> id;
            deleteTask(id);
        }
        else if (pilihan == 6) {
            string keyword;
            cout << "Masukkan kata kunci pencarian: ";
            getline(cin, keyword);
            searchTask(keyword);
        }
        else if (pilihan != 0) {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
