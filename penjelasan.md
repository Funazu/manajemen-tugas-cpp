### 1. **Struct (struktur `Task`)**

```cpp
struct Task {
    int id;
    string name;
    Task* next;
};
```

**Fungsi:**

* Menyimpan data satu tugas, yaitu:

  * `id`: nomor unik tugas
  * `name`: nama tugas
  * `next`: pointer ke tugas berikutnya

**Dipakai sebagai:**
Node dalam **linked list** agar tugas bisa disimpan dan ditelusuri satu per satu secara dinamis.

---

### 2. **Array (`taskNames[100]`)**

```cpp
string taskNames[100];
```

**Fungsi:**

* Menyimpan nama tugas berdasarkan `id` secara langsung (akses cepat via indeks)
* Digunakan saat menampilkan urutan pengerjaan (karena `graph` hanya tahu ID)

**Contoh penggunaan:**

```cpp
cout << taskNames[u] << " (ID: " << u << ")\n";
```

---

### 3. **Linked List (`Task* head`)**

```cpp
Task* head = NULL;
```

**Fungsi:**

* Menyimpan semua data tugas secara dinamis.
* Memungkinkan penambahan dan penghapusan tugas secara efisien.

**Dipakai di:**

* `addTask()`: menambahkan node baru ke akhir
* `showTasks()`, `searchTask()`, `deleteTask()`: untuk menelusuri dan memanipulasi data tugas

---

### 4. **Queue (dalam bentuk manual array `int queue[100]`)**

```cpp
int queue[100];
int front = 0, rear = 0;
```

**Fungsi:**

* Digunakan untuk menyimpan ID tugas yang bisa langsung dikerjakan (tidak punya dependency)
* Dipakai dalam algoritma **Topological Sort** (urutan pengerjaan tugas berdasarkan hubungan)

**Alasan tidak pakai `std::queue`:**
Sesuai permintaan, dibuat manual seperti materi antrian dasar.

---

### 5. **Graph (`vector<vector<int>> adjList`)**

```cpp
vector<vector<int>> adjList;
```

**Fungsi:**

* Mewakili hubungan antar tugas (dependency)
* `adjList[i]` menyimpan daftar ID tugas yang harus dikerjakan setelah tugas ke-`i`

**Dipakai di:**

* `setUrutanPengerjaan()`: menambahkan edge di graph
* `showTaskOrder()`: digunakan dalam proses topological sort

---

### Penjelasan alur kerjanya secara umum:

1. Tugas disimpan di **linked list**.
2. Nama tugas disalin juga ke **array `taskNames`** untuk akses cepat.
3. Hubungan antar tugas disimpan di **graph (`adjList`)**.
4. Untuk menampilkan urutan pengerjaan, digunakan **topological sort** memakai **manual queue array**.

---

### Contoh skenario:

Kamu ingin mengerjakan:

* "Strukdat" → duluan
* "Komdat" → setelah "Strukdat"

Langkah:

1. Tambah "Strukdat" → ID 0
2. Tambah "Komdat" → ID 1
3. Atur urutan: `0 -> 1`

Graph menjadi: `adjList[0] = {1}`, artinya "Komdat" hanya bisa dikerjakan setelah "Strukdat".

---
