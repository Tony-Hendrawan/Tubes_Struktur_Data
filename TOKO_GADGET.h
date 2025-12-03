#ifndef TOKO_GADGET_TUBES_H
#define TOKO_GADGET_TUBES_H

#include <string>
using namespace std;

// batas maksimalnya disini guys
#define MAX_PRODUK 100
#define MAX_USER 50
#define MAX_KATEGORI 100
#define MAX_PRODUK_DI_KAT 50
#define MAX_ANAK_KAT 20

// user
struct User {
    string username;
    string password;
    bool isAdmin;
};

// -produk disini guys
struct Product {
    int id;
    string nama;
    string spesifikasi;
    int harga;
    int stok;
};

// disini kategori hp ny
struct Category {
    int id;
    string nama;

    int parentId; // -1 jika root

    int anakId[MAX_ANAK_KAT];
    int jumlahAnak;

    int produkId[MAX_PRODUK_DI_KAT];
    int jumlahProduk;
};

// keranjang pke linked list ajah biar gmpang
struct CartItem {
    int productId;
    int jumlah;
    int hargaSatuan;
    CartItem* next;
};
 // auth
bool loginUser(User users[], int jumlahUser, const string& uname, const string& pw, User &hasil);
bool signupUser(User users[], int &jumlahUser, const string& uname, const string& pw);

// disini buat crud nya
Product* cariProduk(Product produk[], int jumlahProduk, int id);
bool tambahProduk(Product produk[], int &jumlahProduk, const Product& p);
bool editProduk(Product produk[], int jumlahProduk, const Product &p);
bool hapusProduk(Product produk[], int &jumlahProduk, int id);

// disini manajemen katgori
bool tambahKategori(Category kategori[], int &jumlahKategori, int id, const string& nama, int parentId);
Category* cariKategori(Category kategori[], int jumlahKategori, int id);
bool hapusKategori(Category kategori[], int &jumlahKategori, int id);

// hubungkan produk ke kategori
bool tambahProdukKeKategori(Category kategori[], int jumlahKategori, int kategoriId, int productId);

// ambil produk dalam kategori
int ambilProdukDariKategori(Category* kat, int outProdukId[], int maxOut);

int cariProdukKeyword(Product produk[], int jumlahProduk, const string& key, int hasilId[], int maxHasil);

void tambahKeKeranjang(CartItem*& head, int productId, int jumlah, int harga);
void tampilkanKeranjang(CartItem* head);
bool checkout(CartItem*& head, Product produk[], int jumlahProduk);
void hapusKeranjang(CartItem*& head);

// buat database csv nya ini
bool loadProdukCSV(const string& filename, Product produk[], int &jumlahProduk);
bool saveProdukCSV(const string& filename, Product produk[], int jumlahProduk);

void clearScreen();
void tungguEnter();

#endif
