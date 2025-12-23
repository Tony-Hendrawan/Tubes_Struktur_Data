# Toko Gadget - Aplikasi Manajemen Produk Berbasis Tree

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

Repositori ini dibuat untuk memenuhi Tugas Besar Mata Kuliah Struktur Data.

---

## Daftar Isi

- [Deskripsi Program](#deskripsi-program)
- [Struktur Data yang Digunakan](#struktur-data-yang-digunakan)
- [Fitur Program](#fitur-program)
- [Struktur File](#struktur-file)
- [Cara Menjalankan Program](#cara-menjalankan-program)
- [Screenshot Program](#screenshot-program)
- [Akun Default](#akun-default)
- [Teknologi yang Digunakan](#teknologi-yang-digunakan)

---

## Deskripsi Program

Program ini adalah aplikasi toko gadget berbasis console yang menggunakan struktur data Tree untuk mengelola hierarki produk. Aplikasi ini mensimulasikan sistem e-commerce sederhana dimana terdapat dua jenis pengguna:

1. **Pembeli** - Dapat melihat katalog produk, mencari produk, dan melakukan pembelian
2. **Admin** - Dapat mengelola data produk seperti menambah, mengedit, dan menghapus data

Data produk disimpan secara permanen dalam file CSV sehingga tidak hilang saat program ditutup.

---

## Struktur Data yang Digunakan

Program menggunakan struktur data **General Tree (N-ary Tree)** dimana setiap node dapat memiliki banyak anak. Struktur hierarki produk terdiri dari 5 level:

```
[ROOT] Gadget
+-- [Kategori Utama] Smartphone
|   +-- [Sub-Kategori] Android
|   |   +-- [Brand] Samsung Phone
|   |   |   +-- [PRODUK] Samsung Galaxy A54 (Rp 4500000, Stok: 15)
|   |   |   +-- [PRODUK] Samsung Galaxy A15 (Rp 2999000, Stok: 20)
|   |   +-- [Brand] Xiaomi
|   |       +-- [PRODUK] Xiaomi Redmi Note 13 (Rp 2600000, Stok: 30)
|   +-- [Sub-Kategori] iOS
|       +-- [Brand] Apple iPhone
|           +-- [PRODUK] iPhone 13 (Rp 8999000, Stok: 10)
|           +-- [PRODUK] iPhone 15 (Rp 12999000, Stok: 7)
+-- [Kategori Utama] Laptop
|   +-- [Sub-Kategori] Gaming
|   |   +-- [Brand] Asus
|   |   |   +-- [PRODUK] Asus ROG Strix G15 (Rp 18999000, Stok: 5)
|   |   +-- [Brand] MSI
|   |       +-- [PRODUK] MSI Katana 15 (Rp 15999000, Stok: 6)
|   +-- [Sub-Kategori] Office
|       +-- [Brand] Lenovo Laptop
|           +-- [PRODUK] Lenovo ThinkPad L14 (Rp 10500000, Stok: 8)
+-- [Kategori Utama] Tablet
    +-- [Sub-Kategori] Android Tablet
    |   +-- [Brand] Samsung Tablet
    |   |   +-- [PRODUK] Samsung Galaxy Tab A9 (Rp 3500000, Stok: 12)
    |   +-- [Brand] Lenovo Tablet
    |       +-- [PRODUK] Lenovo Tab M10 (Rp 2800000, Stok: 18)
    +-- [Sub-Kategori] iPad
        +-- [Brand] Apple iPad
            +-- [PRODUK] iPad Air 5 (Rp 9999000, Stok: 9)
            +-- [PRODUK] iPad Pro 11 (Rp 13999000, Stok: 6)
```

### Penjelasan Struktur Node

Setiap node dalam tree memiliki atribut:

| Atribut | Tipe Data | Keterangan |
|---------|-----------|------------|
| data | string | Nama kategori/brand |
| tipe_simpul | string | Jenis node (Root, Kategori Utama, Sub-Kategori, Brand, Produk) |
| data_produk | struct | Informasi produk (nama, harga, stok, spesifikasi) |
| anak | vector | Daftar node anak |
| induk | pointer | Pointer ke node parent |

---

## Fitur Program

### Fitur Pembeli

| No | Fitur | Keterangan |
|----|-------|------------|
| 1 | Login | Masuk ke akun yang sudah terdaftar |
| 2 | Signup | Membuat akun baru |
| 3 | Lihat Kategori | Menelusuri produk berdasarkan hierarki kategori |
| 4 | Cari Produk | Mencari produk berdasarkan keyword |
| 5 | Lihat Detail | Melihat informasi lengkap produk |
| 6 | Beli Produk | Melakukan pembelian dan mengurangi stok |

### Fitur Admin

| No | Fitur | Keterangan |
|----|-------|------------|
| 1 | Login Admin | Masuk dengan akun admin |
| 2 | Lihat Tree | Menampilkan seluruh struktur tree |
| 3 | Tambah Data | Menambah Kategori Utama, Sub-Kategori, Brand, atau Produk |
| 4 | Edit Data | Mengubah data yang sudah ada |
| 5 | Hapus Data | Menghapus data beserta seluruh anak-anaknya |

### Fitur Keamanan

- Password disembunyikan dengan karakter `*` saat diketik
- Validasi input untuk mencegah error
- Validasi hierarki parent saat menambah data

---

## Struktur File

```
toko-gadget/
├── Main.cpp            # File utama program, menu pembeli dan admin
├── TreeManager.cpp     # Implementasi fungsi-fungsi manajemen tree
├── TreeManager.h       # Deklarasi fungsi TreeManager
├── Auth.cpp            # Implementasi autentikasi (login, signup)
├── Auth.h              # Deklarasi fungsi dan struct Auth
├── Data.h              # Definisi struct Simpul dan InfoProduk
├── CSV/
│   └── tree_data.csv   # File penyimpanan data tree
├── toko_gadget.exe     # File executable hasil kompilasi
└── README.md           # Dokumentasi program
```

### Penjelasan File

| File | Fungsi |
|------|--------|
| Main.cpp | Berisi fungsi main(), menu pembeli, menu admin, dan alur program utama |
| TreeManager.cpp | Berisi implementasi operasi tree seperti tambah, hapus, edit, cari, dan tampilkan |
| TreeManager.h | Berisi deklarasi fungsi-fungsi yang ada di TreeManager.cpp |
| Auth.cpp | Berisi implementasi login, signup, dan input password tersembunyi |
| Auth.h | Berisi deklarasi struct Pengguna dan enum PeranPengguna |
| Data.h | Berisi definisi struct Simpul (node tree) dan InfoProduk |
| tree_data.csv | Menyimpan data tree dalam format CSV dengan delimiter titik koma (;) |

---

## Cara Menjalankan Program

### Prasyarat

- Compiler C++ yang mendukung C++17 (MinGW, GCC, atau MSVC)
- Sistem operasi Windows

### Langkah Kompilasi

1. Buka terminal atau command prompt
2. Masuk ke direktori project
3. Jalankan perintah kompilasi:

```bash
g++ -o toko_gadget.exe Main.cpp TreeManager.cpp Auth.cpp -std=c++17
```

### Langkah Menjalankan

```bash
./toko_gadget.exe
```

atau double-click file `toko_gadget.exe`

---

## Screenshot Program

### Menu Utama
```
SELAMAT DATANG DI TOKO GADGET

Masuk sebagai:
1. Pembeli
2. Admin
Pilih (1/2):
```

### Menu Pembeli
```
MENU PEMBELI
Pilih kategori utama:
1. Smartphone
2. Laptop
3. Tablet
4. Cari Produk
0. Logout
Pilih menu:
```

### Menu Admin
```
MENU ADMIN
1. Lihat Tree
2. Edit
3. Hapus
4. Tambah
0. Logout
Pilih menu:
```

### Tampilan Tree
```
[ROOT] Gadget
+-- [Kategori Utama] Smartphone
|   +-- [Sub-Kategori] Android
|   |   +-- [Brand] Samsung Phone
|   |   |   +-- [PRODUK] Samsung Galaxy A54 (Rp 4500000, Stok: 15, Spec: RAM 8/256)
```

---

## Akun Default

### Admin
| Username | Password |
|----------|----------|
| admin | admin123 |

### Pembeli
Buat akun baru melalui menu **Signup** saat memilih masuk sebagai Pembeli.

---

## Teknologi yang Digunakan

| Komponen | Teknologi |
|----------|-----------|
| Bahasa Pemrograman | C++ |
| Standard | C++17 |
| Compiler | MinGW GCC |
| Penyimpanan Data | File CSV |
| Memory Management | Smart Pointer (shared_ptr) |

---

## Kontributor

Dibuat untuk memenuhi Tugas Besar Mata Kuliah Struktur Data.
