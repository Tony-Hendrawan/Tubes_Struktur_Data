#include "TreeManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <limits>
#include <vector>

// =========================================================
// BAGIAN INTERNAL: LOGIKA TAMPILAN TABEL
// =========================================================

void cetakGarisTabel(int lebarKolom[])
{
    std::cout << "+";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < lebarKolom[i] + 2; j++)
            std::cout << "-";
        std::cout << "+";
    }
    std::cout << "\n";
}

void prosesTampilanTabel(SimpulPtr s, std::vector<std::string> path, int lebarKolom[])
{
    if (!s)
        return;

    std::string namaData = (s->tipe_simpul == "Produk") ? s->data_produk.nama : s->data;

    // Update path silsilah (Root, Utama, Sub, Brand)
    if (s->tipe_simpul == "Root")
    {
        path[0] = (s->data.empty()) ? "GADGET" : s->data;
    }
    else if (s->tipe_simpul == "Kategori Utama")
    {
        path[1] = namaData;
    }
    else if (s->tipe_simpul == "Sub-Kategori")
    {
        path[2] = namaData;
    }
    else if (s->tipe_simpul == "Brand")
    {
        path[3] = namaData;
    }

    if (s->tipe_simpul == "Produk")
    {
        std::cout << "| " << std::left << std::setw(lebarKolom[0]) << path[0]
                  << " | " << std::left << std::setw(lebarKolom[1]) << path[1]
                  << " | " << std::left << std::setw(lebarKolom[2]) << path[2]
                  << " | " << std::left << std::setw(lebarKolom[3]) << path[3]
                  << " | " << std::left << std::setw(lebarKolom[4]) << s->data_produk.nama
                  << " | " << std::right << std::setw(lebarKolom[5]) << s->data_produk.harga
                  << " |\n";
    }
    else if (s->anak.empty() && s->tipe_simpul != "Root")
    {
        // Cetak kategori meskipun kosong (belum ada produk)
        std::cout << "| " << std::left << std::setw(lebarKolom[0]) << path[0]
                  << " | " << std::left << std::setw(lebarKolom[1]) << path[1]
                  << " | " << std::left << std::setw(lebarKolom[2]) << path[2]
                  << " | " << std::left << std::setw(lebarKolom[3]) << path[3]
                  << " | " << std::left << std::setw(lebarKolom[4]) << "(Belum ada produk)"
                  << " | " << std::right << std::setw(lebarKolom[5]) << "-"
                  << " |\n";
    }
    else
    {
        for (auto &anakSimpul : s->anak)
        {
            prosesTampilanTabel(anakSimpul, path, lebarKolom);
        }
    }
}

// =========================================================
// IMPLEMENTASI FUNGSI PUBLIC
// =========================================================

void tambahAnak(SimpulPtr induk, SimpulPtr anak)
{
    if (induk && anak)
    {
        anak->induk = induk;
        induk->anak.push_back(anak);
    }
}

void tampilkanTree(SimpulPtr simpul, int levelIgnore)
{
    if (!simpul)
        return;

    int lebarKolom[] = {10, 15, 15, 12, 22, 12};
    std::vector<std::string> path(4, " - ");

    std::cout << "\n"
              << std::setw(50) << "--- DAFTAR INVENTARIS TOKO GADGET ---" << "\n";
    cetakGarisTabel(lebarKolom);
    std::cout << "| " << std::left << std::setw(lebarKolom[0]) << "ROOT"
              << " | " << std::left << std::setw(lebarKolom[1]) << "KATEGORI"
              << " | " << std::left << std::setw(lebarKolom[2]) << "SUB-KAT"
              << " | " << std::left << std::setw(lebarKolom[3]) << "BRAND"
              << " | " << std::left << std::setw(lebarKolom[4]) << "NAMA PRODUK"
              << " | " << std::left << std::setw(lebarKolom[5]) << "HARGA (Rp)" << " |\n";
    cetakGarisTabel(lebarKolom);

    prosesTampilanTabel(simpul, path, lebarKolom);

    cetakGarisTabel(lebarKolom);
    std::cout << std::endl;
}

SimpulPtr cariSimpul(SimpulPtr akar, const std::string &target)
{
    if (!akar)
        return nullptr;

    std::string saatIni = (akar->tipe_simpul == "Produk") ? akar->data_produk.nama : akar->data;
    std::string s1 = saatIni, s2 = target;
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    if (s1 == s2)
        return akar;

    for (auto &a : akar->anak)
    {
        SimpulPtr res = cariSimpul(a, target);
        if (res)
            return res;
    }
    return nullptr;
}

bool hapusSimpul(SimpulPtr akar, const std::string &target)
{
    if (!akar)
        return false;
    SimpulPtr targetS = cariSimpul(akar, target);
    if (!targetS || !targetS->induk)
    {
        std::cout << "Gagal: Data tidak ditemukan atau tidak bisa hapus root.\n";
        return false;
    }

    auto &v = targetS->induk->anak;
    v.erase(std::remove_if(v.begin(), v.end(), [&](SimpulPtr s)
                           {
        std::string n = (s->tipe_simpul == "Produk") ? s->data_produk.nama : s->data;
        return n == targetS->data || n == targetS->data_produk.nama; }),
            v.end());

    std::cout << "Data berhasil dihapus.\n";
    return true;
}

void editSimpul(SimpulPtr simpul)
{
    if (!simpul)
        return;
    if (simpul->tipe_simpul == "Produk")
    {
        std::string n;
        std::cout << "Nama baru (kosong skip): ";
        std::getline(std::cin, n);
        if (!n.empty())
            simpul->data_produk.nama = n;

        long long h;
        std::cout << "Harga baru (0 skip): ";
        if (std::cin >> h && h > 0)
            simpul->data_produk.harga = h;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
        std::string n;
        std::cout << "Nama baru: ";
        std::getline(std::cin, n);
        if (!n.empty())
            simpul->data = n;
    }
    std::cout << "Berhasil diperbarui.\n";
}

// FUNGSI TAMBAH SIMPUL DENGAN VALIDASI DUPLIKAT
bool tambahSimpul(SimpulPtr akar, const std::string &namaInduk, const std::string &tipeSimpul)
{
    SimpulPtr induk = cariSimpul(akar, namaInduk);
    if (!induk)
    {
        std::cout << "Gagal: Parent tidak ditemukan.\n";
        return false;
    }

    std::string namaBaru;
    std::cout << "Masukkan nama " << tipeSimpul << " baru: ";
    std::getline(std::cin, namaBaru);

    // VALIDASI DUPLIKAT: Cek apakah nama sudah ada di sistem
    if (cariSimpul(akar, namaBaru))
    {
        std::cout << "Gagal: Nama '" << namaBaru << "' sudah ada. Gunakan nama unik.\n";
        return false;
    }

    if (tipeSimpul == "Produk")
    {
        long long h;
        int st;
        std::string sp;
        std::cout << "Harga: ";
        std::cin >> h;
        std::cout << "Stok: ";
        std::cin >> st;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Spesifikasi: ";
        std::getline(std::cin, sp);

        tambahAnak(induk, std::make_shared<Simpul>(namaBaru, h, st, sp));
    }
    else
    {
        tambahAnak(induk, std::make_shared<Simpul>(namaBaru, tipeSimpul));
    }
    std::cout << "Berhasil menambahkan " << tipeSimpul << ".\n";
    return true;
}

void cariProduk(SimpulPtr akar, const std::string &katakunci)
{
    std::vector<SimpulPtr> semua;
    kumpulkanSemuaSimpul(akar, semua);
    std::string k = katakunci;
    std::transform(k.begin(), k.end(), k.begin(), ::tolower);

    bool ada = false;
    for (auto &s : semua)
    {
        if (s->tipe_simpul == "Produk")
        {
            std::string n = s->data_produk.nama;
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            if (n.find(k) != std::string::npos)
            {
                std::cout << "- " << s->data_produk.nama << " (Rp " << s->data_produk.harga << ")\n";
                ada = true;
            }
        }
    }
    if (!ada)
        std::cout << "Produk tidak ditemukan.\n";
}

bool beliProduk(SimpulPtr produk)
{
    if (!produk || produk->data_produk.stok <= 0)
        return false;
    int j;
    std::cout << "Jumlah: ";
    if (!(std::cin >> j) || j <= 0 || j > produk->data_produk.stok)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    produk->data_produk.stok -= j;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

void kumpulkanSemuaSimpul(SimpulPtr s, std::vector<SimpulPtr> &hasil)
{
    if (!s)
        return;
    hasil.push_back(s);
    for (auto &a : s->anak)
        kumpulkanSemuaSimpul(a, hasil);
}

void simpanTreeKeCSV(SimpulPtr akar, const std::string &namaFile)
{
    std::ofstream f(namaFile);
    if (!f.is_open())
        return;
    f << "Tipe;Nama;Parent;Harga;Stok;Spec\n";
    std::vector<SimpulPtr> semua;
    kumpulkanSemuaSimpul(akar, semua);
    for (auto &s : semua)
    {
        std::string p = (s->induk) ? (s->induk->tipe_simpul == "Produk" ? s->induk->data_produk.nama : s->induk->data) : "NULL";
        std::string n = (s->tipe_simpul == "Produk") ? s->data_produk.nama : s->data;
        f << s->tipe_simpul << ";" << n << ";" << p << ";"
          << (s->tipe_simpul == "Produk" ? std::to_string(s->data_produk.harga) : "") << ";"
          << (s->tipe_simpul == "Produk" ? std::to_string(s->data_produk.stok) : "") << ";"
          << (s->tipe_simpul == "Produk" ? s->data_produk.spesifikasi : "") << "\n";
    }
}

void muatTreeDariCSV(SimpulPtr akar, const std::string &namaFile)
{
    std::ifstream f(namaFile);
    if (!f.is_open())
        return;
    std::string l;
    std::getline(f, l);
    std::vector<SimpulPtr> cache = {akar};
    while (std::getline(f, l))
    {
        if (l.empty())
            continue;
        std::stringstream ss(l);
        std::string t, n, p, h, st, sp;
        std::getline(ss, t, ';');
        std::getline(ss, n, ';');
        std::getline(ss, p, ';');
        std::getline(ss, h, ';');
        std::getline(ss, st, ';');
        std::getline(ss, sp, ';');

        SimpulPtr parent = nullptr;
        for (auto it = cache.rbegin(); it != cache.rend(); ++it)
        {
            std::string nC = ((*it)->tipe_simpul == "Produk") ? (*it)->data_produk.nama : (*it)->data;
            if (nC == p)
            {
                parent = *it;
                break;
            }
        }
        if (!parent)
            parent = akar;

        if (t == "Root")
            akar->data = n;
        else if (t == "Produk")
        {
            auto sB = std::make_shared<Simpul>(n, std::stoll(h), std::stoi(st), sp);
            tambahAnak(parent, sB);
            cache.push_back(sB);
        }
        else
        {
            auto sB = std::make_shared<Simpul>(n, t);
            tambahAnak(parent, sB);
            cache.push_back(sB);
        }
    }
}
