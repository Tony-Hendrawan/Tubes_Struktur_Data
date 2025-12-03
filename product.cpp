#include <iostream>
#include "TOKO_GADGET.h"

using namespace std;

// CRUD Produk

// nyari berdasarkan id
Product* cariProduk(Product produk[], int jumlahProduk, int id) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (produk[i].id == id) {
            return &produk[i];
        }
    }
    return nullptr;
}
// nambah produk
bool tambahProduk(Product produk[], int &jumlahProduk, const Product& p) {
    // cek id udah ada apa belom
    if (cariProduk(produk, jumlahProduk, p.id) != nullptr) {
        cout << "Tambah produk gagal: ID produk sudah ada." << endl;
        return false;
    }
    // nambah produk
    produk[jumlahProduk] = p;
    jumlahProduk++;
    return true;
}

// ngedit produk
bool editProduk(Product produk[], int jumlahProduk, const Product &p) {
    // nyari produk dulu
    Product* found = cariProduk(produk, jumlahProduk, p.id);
    if (found == nullptr) {
        cout << "Edit produk gagal: Produk ID: " << p.id << ", tidak ditemukan." << endl;
        return false;
    }

    // update
    found->nama = p.nama;
    found->spesifikasi = p.spesifikasi;
    found->harga = p.harga;
    found->stok = p.stok;

    return true;
}

// hapus produk
bool hapusProduk(Product produk[], int &jumlahProduk, int id) {
    int index = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (produk[i].id == id){
            index = i;
            break;
        }
    }
    // nyari id produk
    if (index == -1) {
        cout << "Produk ID: " << id << ", tidak ditemukan." << endl;
        return false;
    }
    // nggeser elemen elemen setelah index ke kiri
    for(int i = index; i < jumlahProduk - 1; i++) {
        produk[i] = produk[i + 1];
    }
    // ngapus produk
    jumlahProduk--;
    return true;
}