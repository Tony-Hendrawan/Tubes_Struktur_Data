#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <memory>

struct InfoProduk
{
    std::string nama;
    long long harga = 0;
    int stok = 0;
    std::string spesifikasi;
};

struct Simpul;
typedef std::shared_ptr<Simpul> SimpulPtr;

struct Simpul
{
    std::string data;
    std::string tipe_simpul;
    InfoProduk data_produk;
    std::vector<SimpulPtr> anak;
    SimpulPtr induk;

    Simpul(const std::string &nilai = "", const std::string &tipe = "Kategori")
        : data(nilai), tipe_simpul(tipe), induk(nullptr) {}

    Simpul(const std::string &nama, long long harga, int stok, const std::string &spec = "")
        : data(""), tipe_simpul("Produk"), induk(nullptr)
    {
        data_produk.nama = nama;
        data_produk.harga = harga;
        data_produk.stok = stok;
        data_produk.spesifikasi = spec;
    }
};

#endif
