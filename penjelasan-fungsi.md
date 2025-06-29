
---

### 🔹 `addTask(string name)`

**Fungsi:**
Menambahkan tugas baru ke dalam sistem.

**Yang dilakukan:**

1. Membuat node baru dari struct `Task`.
2. Mengatur `id`, `name`, dan `next = NULL`.
3. Menambahkan node ke akhir **linked list**.
4. Menyimpan `name` ke dalam array `taskNames[id]`.
5. Menambahkan node kosong ke **graf** (`adjList`) untuk persiapan relasi/dependency.

---

### 🔹 `setUrutanPengerjaan(int fromID, int toID)`

**Fungsi:**
Menentukan bahwa tugas dengan `fromID` harus dikerjakan **sebelum** `toID`.

**Yang dilakukan:**

* Menambahkan relasi di **graf (adjList)**: `adjList[fromID].push_back(toID)`
  Ini artinya, toID **bergantung** pada fromID.

---

### 🔹 `showTasks()`

**Fungsi:**
Menampilkan semua tugas yang sudah ditambahkan.

**Yang dilakukan:**

* Menelusuri **linked list** dari `head`, lalu mencetak setiap tugas (`id` dan `name`).

---

### 🔹 `searchTask(const string& keyword)`

**Fungsi:**
Mencari dan menampilkan tugas yang mengandung `keyword` dalam namanya.

**Yang dilakukan:**

* Melakukan pencarian substring (`.find(keyword)`) pada setiap nama tugas di **linked list**.

---

### 🔹 `deleteTask(int id)`

**Fungsi:**
Menghapus tugas dari **linked list** berdasarkan ID.

**Yang dilakukan:**

1. Mencari node yang ID-nya sesuai.
2. Menghapus node tersebut.
3. Graph tetap utuh (ID dan `adjList` tidak dihapus, hanya data `Task` saja).

> ⚠️ Catatan: `adjList` dan `taskNames` tidak dihapus, jadi kamu perlu hati-hati kalau banyak tugas dihapus lalu ditambah lagi, ID bisa tidak sinkron.

---

### 🔹 `showTaskOrder()`

**Fungsi:**
Menampilkan urutan tugas berdasarkan dependency (urutan kerja logis) menggunakan **Topological Sort**.

**Yang dilakukan:**

1. Hitung **indegree** (berapa banyak tugas lain yang harus dikerjakan dulu).
2. Masukkan tugas dengan `indegree == 0` ke dalam antrian manual (`queue[]`).
3. Proses antrian:

   * Cetak tugas.
   * Kurangi `indegree` dari tugas-tugas yang bergantung padanya.
   * Jika `indegree` jadi 0, masukkan ke antrian.

> Ini algoritma topological sort versi queue manual.

---

### 🔹 `main()`

**Fungsi:**
Menampilkan **menu utama** dan mengatur alur program berdasarkan input pengguna.

**Yang dilakukan:**

1. Tampilkan menu.
2. Berdasarkan pilihan user:

   * Tambahkan tugas
   * Atur urutan
   * Tampilkan tugas
   * Tampilkan urutan pengerjaan
   * Hapus tugas
   * Cari tugas
3. Gunakan `system("cls")` dan `system("pause")` agar lebih rapi saat dijalankan di Windows.

---
