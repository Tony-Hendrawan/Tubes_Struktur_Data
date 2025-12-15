// TreeManager.cpp
#include "TreeManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

// Menambah anak ke simpul
void tambahAnak(SimpulPtr induk, SimpulPtr anak)
{
    if (induk && anak)
    {
        anak->induk = induk;
        induk->anak.push_back(anak);
    }
}

// Menampilkan Tree
void tampilkanTree(SimpulPtr simpul, int level)
{
    if (!simpul)
        return;

    std::string spasi(level * 4, ' ');

    if (simpul->tipe_simpul == "Produk")
    {
        std::cout << spasi << "- [PRODUK] " << simpul->data_produk.nama
                  << " (Rp " << simpul->data_produk.harga
                  << ", Stok: " << simpul->data_produk.stok
                  << ") Spec: " << simpul->data_produk.spesifikasi << "\n";
    }
    else
    {
        std::cout << spasi << "[" << simpul->tipe_simpul << "] " << simpul->data << "\n";
    }

    for (auto &anakSimpul : simpul->anak)
        tampilkanTree(anakSimpul, level + 1);
}

// Mencari Simpul
SimpulPtr cariSimpul(SimpulPtr akar, const std::string &target)
{
    if (!akar)
        return nullptr;

    std::string saatIni =
        (akar->tipe_simpul == "Produk") ? akar->data_produk.nama : akar->data;

    std::string saatIniKecil = saatIni;
    std::string targetKecil = target;

    std::transform(saatIniKecil.begin(), saatIniKecil.end(), saatIniKecil.begin(), ::tolower);
    std::transform(targetKecil.begin(), targetKecil.end(), targetKecil.begin(), ::tolower);

    if (saatIniKecil == targetKecil)
        return akar;

    for (auto &anakSimpul : akar->anak)
        if (auto ditemukan = cariSimpul(anakSimpul, target))
            return ditemukan;

    return nullptr;
}

// Menghapus Simpul
bool hapusSimpul(SimpulPtr akar, const std::string &target)
{
    if (!akar)
        return false;

    SimpulPtr simpulTarget = cariSimpul(akar, target);
    if (!simpulTarget)
    {
        std::cout << "Simpul tidak ditemukan.\n";
        return false;
    }

    if (!simpulTarget->induk)
    {
        std::cout << "Tidak bisa hapus root.\n";
        return false;
    }

    auto indukSimpul = simpulTarget->induk;
    auto &daftarAnak = indukSimpul->anak;

    daftarAnak.erase(
        std::remove_if(daftarAnak.begin(), daftarAnak.end(),
                       [&](SimpulPtr s)
                       {
                           std::string namaSimpul =
                               (s->tipe_simpul == "Produk") ? s->data_produk.nama : s->data;
                           std::string namaKecil = namaSimpul, targetKecil = target;
                           std::transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);
                           std::transform(targetKecil.begin(), targetKecil.end(), targetKecil.begin(), ::tolower);
                           return namaKecil == targetKecil;
                       }),
        daftarAnak.end());

    std::cout << "Simpul berhasil dihapus.\n";
    return true;
}

// Edit Simpul
void editSimpul(SimpulPtr simpul)
{
    if (!simpul)
        return;

    if (simpul->tipe_simpul == "Produk")
    {
        std::string namaBaru;
        std::cout << "Nama baru (kosong = skip): ";
        std::getline(std::cin, namaBaru);
        if (!namaBaru.empty())
            simpul->data_produk.nama = namaBaru;

        long long hargaBaru;
        std::cout << "Harga baru (0 skip): ";
        std::cin >> hargaBaru;
        if (hargaBaru > 0)
            simpul->data_produk.harga = hargaBaru;
        std::cin.ignore();

        int stokBaru;
        std::cout << "Stok baru (-1 skip): ";
        std::cin >> stokBaru;
        if (stokBaru >= 0)
            simpul->data_produk.stok = stokBaru;
        std::cin.ignore();

        std::string specBaru;
        std::cout << "Spec baru (kosong skip): ";
        std::getline(std::cin, specBaru);
        if (!specBaru.empty())
            simpul->data_produk.spesifikasi = specBaru;
    }
    else
    {
        std::string namaBaru;
        std::cout << "Nama baru: ";
        std::getline(std::cin, namaBaru);
        if (!namaBaru.empty())
            simpul->data = namaBaru;
    }

    std::cout << "Data berhasil diperbarui.\n";
}

// Tambah Simpul
bool tambahSimpul(SimpulPtr akar, const std::string &namaInduk, const std::string &tipeSimpul)
{
    SimpulPtr induk = cariSimpul(akar, namaInduk);
    if (!induk)
    {
        std::cout << "Parent tidak ditemukan.\n";
        return false;
    }

    if (tipeSimpul == "Produk")
    {
        std::string nama, spec;
        long long harga;
        int stok;

        std::cout << "Nama produk: ";
        std::getline(std::cin, nama);
        if (nama.empty())
            return false;

        std::cout << "Harga: ";
        std::cin >> harga;
        std::cin.ignore();

        std::cout << "Stok: ";
        std::cin >> stok;
        std::cin.ignore();

        std::cout << "Spesifikasi: ";
        std::getline(std::cin, spec);

        SimpulPtr simpulBaru = std::make_shared<Simpul>(nama, harga, stok, spec);
        tambahAnak(induk, simpulBaru);
    }
    else
    {
        std::string nama;
        std::cout << "Nama " << tipeSimpul << ": ";
        std::getline(std::cin, nama);
        if (nama.empty())
            return false;

        SimpulPtr simpulBaru = std::make_shared<Simpul>(nama, tipeSimpul);
        tambahAnak(induk, simpulBaru);
    }

    std::cout << tipeSimpul << " berhasil ditambahkan.\n";
    return true;
}

// Cari Produk
void cariProduk(SimpulPtr akar, const std::string &katakunci)
{
    if (!akar)
        return;

    std::string kunciKecil = katakunci;
    std::transform(kunciKecil.begin(), kunciKecil.end(), kunciKecil.begin(), ::tolower);

    std::vector<SimpulPtr> hasil;
    std::vector<SimpulPtr> semua;
    kumpulkanSemuaSimpul(akar, semua);

    for (auto &s : semua)
    {
        if (s->tipe_simpul != "Produk")
            continue;

        std::string nama = s->data_produk.nama;
        std::string namaKecil = nama;
        std::transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);

        if (namaKecil.find(kunciKecil) != std::string::npos)
            hasil.push_back(s);
    }

    if (hasil.empty())
    {
        std::cout << "Produk tidak ditemukan.\n";
        return;
    }

    std::cout << "\nHasil pencarian:\n";
    int idx = 1;
    for (auto &p : hasil)
    {
        std::cout << idx++ << ". " << p->data_produk.nama
                  << " - Rp " << p->data_produk.harga
                  << " (Stok: " << p->data_produk.stok << ")\n";
    }
}

// Beli Produk
bool beliProduk(SimpulPtr produk)
{
    if (!produk || produk->tipe_simpul != "Produk")
        return false;

    if (produk->data_produk.stok <= 0)
    {
        std::cout << "Stok habis.\n";
        return false;
    }

    int jumlah;
    std::cout << "Jumlah beli: ";
    std::cin >> jumlah;
    std::cin.ignore();

    if (jumlah <= 0)
    {
        std::cout << "Jumlah tidak valid.\n";
        return false;
    }

    if (jumlah > produk->data_produk.stok)
    {
        std::cout << "Stok tidak cukup. Tersedia: " << produk->data_produk.stok << "\n";
        return false;
    }

    produk->data_produk.stok -= jumlah;
    long long total = produk->data_produk.harga * jumlah;

    std::cout << "\nPembelian berhasil!\n";
    std::cout << "Produk: " << produk->data_produk.nama << "\n";
    std::cout << "Jumlah: " << jumlah << "\n";
    std::cout << "Total : Rp " << total << "\n";

    return true;
}

// Kumpulkan semua simpul
void kumpulkanSemuaSimpul(SimpulPtr s, std::vector<SimpulPtr> &hasil)
{
    if (!s)
        return;
    hasil.push_back(s);
    for (auto &anakSimpul : s->anak)
        kumpulkanSemuaSimpul(anakSimpul, hasil);
}

// Simpan tree ke CSV
void simpanTreeKeCSV(SimpulPtr akar, const std::string &namaFile)
{
    std::ofstream berkas(namaFile);
    if (!berkas.is_open())
    {
        std::cout << "Gagal membuka CSV.\n";
        return;
    }

    berkas << "Level;Nama;Parent;Harga;Stok;Spesifikasi\n";

    std::vector<SimpulPtr> semua;
    kumpulkanSemuaSimpul(akar, semua);

    for (auto &s : semua)
    {
        std::string tipe = s->tipe_simpul;
        std::string nama =
            (tipe == "Produk") ? s->data_produk.nama : s->data;

        std::string indukNama = "NULL";
        if (s->induk)
            indukNama = (s->induk->tipe_simpul == "Produk")
                            ? s->induk->data_produk.nama
                            : s->induk->data;

        std::string harga = (tipe == "Produk") ? std::to_string(s->data_produk.harga) : "";
        std::string stok = (tipe == "Produk") ? std::to_string(s->data_produk.stok) : "";
        std::string spec = (tipe == "Produk") ? s->data_produk.spesifikasi : "";

        berkas << tipe << ";" << nama << ";" << indukNama << ";"
               << harga << ";" << stok << ";" << spec << "\n";
    }
}

// Muat Tree dari CSV
void muatTreeDariCSV(SimpulPtr akar, const std::string &namaFile)
{
    std::ifstream berkas(namaFile);
    if (!berkas.is_open())
    {
        std::cout << "(INFO) CSV tidak ditemukan.\n";
        return;
    }

    std::string baris;
    std::getline(berkas, baris); // header

    std::vector<SimpulPtr> semuaSimpul;
    semuaSimpul.push_back(akar);

    while (std::getline(berkas, baris))
    {
        if (baris.empty())
            continue;

        std::stringstream ss(baris);
        std::string level, nama, induk, harga, stok, spec;

        std::getline(ss, level, ';');
        std::getline(ss, nama, ';');
        std::getline(ss, induk, ';');
        std::getline(ss, harga, ';');
        std::getline(ss, stok, ';');
        std::getline(ss, spec, ';');

        SimpulPtr simpulInduk = nullptr;
        if (induk == "NULL")
        {
            simpulInduk = akar;
        }
        else
        {
            for (auto it = semuaSimpul.rbegin(); it != semuaSimpul.rend(); ++it)
            {
                std::string namaSimpul = ((*it)->tipe_simpul == "Produk")
                                             ? (*it)->data_produk.nama
                                             : (*it)->data;

                std::string namaKecil = namaSimpul;
                std::string indukKecil = induk;
                std::transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);
                std::transform(indukKecil.begin(), indukKecil.end(), indukKecil.begin(), ::tolower);

                if (namaKecil == indukKecil)
                {
                    simpulInduk = *it;
                    break;
                }
            }

            if (!simpulInduk)
                simpulInduk = akar;
        }

        if (level == "Root")
        {
            akar->data = nama;
        }
        else if (level == "Produk")
        {
            SimpulPtr simpulBaru = std::make_shared<Simpul>(nama,
                                                           std::stoll(harga),
                                                           std::stoi(stok),
                                                           spec);
            tambahAnak(simpulInduk, simpulBaru);
            semuaSimpul.push_back(simpulBaru);
        }
        else
        {
            SimpulPtr simpulBaru = std::make_shared<Simpul>(nama, level);
            tambahAnak(simpulInduk, simpulBaru);
            semuaSimpul.push_back(simpulBaru);
        }
    }
}
