#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
using namespace std;

// Struct untuk menyimpan data tugas
struct Task {
    int id;
    string name;
    Task* next;
};

Task* head = NULL;
vector<vector<int>> adjList; // Graph adjacency list
int taskCount = 0;
string taskNames[100]; 

// Tambah tugas ke linked list dan graph
void addTask(string name) {
    Task* newTask = new Task;
    newTask->id = taskCount;
    newTask->name = name;
    newTask->next = NULL;

    if (head == NULL) head = newTask;
    else {
        Task* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newTask;
    }

    taskNames[taskCount] = name;
    adjList.push_back({});
    cout << "Tugas ditambahkan: ID=" << taskCount << ", Nama=" << name << endl;
    taskCount++;
}

// Tambahkan urutan pengerjaan antar tugas
void setUrutanPengerjaan(int fromID, int toID) {
    if (fromID < taskCount && toID < taskCount) {
        adjList[fromID].push_back(toID);
        cout << "Urutan ditambahkan: " << fromID << " -> " << toID << endl;
    } else {
        cout << "ID tidak valid!" << endl;
    }
}

// Tampilkan semua tugas
void showTasks() {
    Task* temp = head;
    cout << "\nDaftar Tugas:\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name << endl;
        temp = temp->next;
    }
}

// Cari tugas berdasarkan nama
void searchTask(const string& keyword) {
    Task* temp = head;
    bool found = false;
    cout << "\nHasil Pencarian Tugas:\n";
    while (temp != NULL) {
        if (temp->name.find(keyword) != string::npos) {
            cout << "ID: " << temp->id << ", Nama: " << temp->name << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Tidak ditemukan tugas dengan kata kunci tersebut.\n";
}

// Hapus tugas berdasarkan ID
void deleteTask(int id) {
    Task *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Tugas tidak ditemukan!\n";
        return;
    }
    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Tugas ID " << id << " dihapus (data di graph tetap ada).\n";
}

// Topological Sort menggunakan queue
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
        cout << taskNames[u] << " (ID: " << u << ")\n";

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
        system("cls");
        cout << "\n=== Menu Manajemen Tugas ===\n";
        cout << "1. Tambah Tugas\n";
        cout << "2. Atur Urutan Pengerjaan\n";
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
            cout << "Masukkan nama tugas: ";
            getline(cin, nama);
            addTask(nama);
        }
        else if (pilihan == 2) {
            int from, to;
            cout << "Masukkan ID tugas yang harus dikerjakan lebih dulu: "; cin >> from;
            cout << "Masukkan ID tugas yang dikerjakan setelahnya: "; cin >> to;
            setUrutanPengerjaan(from, to);
        }
        else if (pilihan == 3) {
            showTasks();
            system("pause");
        }
        else if (pilihan == 4) {
            showTaskOrder();
            system("pause");
        }
        else if (pilihan == 5) {
            int id;
            cout << "Masukkan ID tugas yang ingin dihapus: ";
            cin >> id;
            deleteTask(id);
            system("pause");
        }
        else if (pilihan == 6) {
            string keyword;
            cout << "Masukkan kata kunci pencarian: ";
            getline(cin, keyword);
            searchTask(keyword);
            system("pause");
        }
        else if (pilihan != 0) {
            cout << "Pilihan tidak valid!\n";
            system("pause");
        }
    } while (pilihan != 0);

    return 0;
}
