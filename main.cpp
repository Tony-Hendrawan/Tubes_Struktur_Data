#include "TreeManager.h"
#include "Auth.h"
#include <iostream>
#include <limits>
#include <cctype>

void tampilkanMenuAnak(SimpulPtr induk)
{
    if (!induk)
        return;

    int indeks = 1;
    for (auto &anakSimpul : induk->anak)
    {
        std::string nama =
            (anakSimpul->tipe_simpul == "Produk") ? anakSimpul->data_produk.nama : anakSimpul->data;

        std::cout << indeks++ << ". " << nama << "\n";
    }
}

SimpulPtr pilihAnak(SimpulPtr induk)
{
    if (!induk)
        return nullptr;

    tampilkanMenuAnak(induk);

    int pilihan;
    std::cout << "Pilih nomor: ";
    if (!(std::cin >> pilihan))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (pilihan < 1 || pilihan > induk->anak.size())
    {
        std::cout << "Pilihan tidak ada\n";
        return nullptr;
    }

    return induk->anak[pilihan - 1];
}

// Menu
SimpulPtr akar_global = nullptr;

void jelajahiHierarki(SimpulPtr mulai)
{
    SimpulPtr saatIni = mulai;
    SimpulPtr akar = akar_global;

    while (saatIni)
    {
        SimpulPtr berikutnya = pilihAnak(saatIni);
        if (!berikutnya)
            return;

        if (berikutnya->tipe_simpul == "Produk")
        {
            std::cout << "\nDETAIL PRODUK \n";
            std::cout << "Nama  : " << berikutnya->data_produk.nama << "\n";
            std::cout << "Harga : Rp " << berikutnya->data_produk.harga << "\n";
            std::cout << "Stok  : " << berikutnya->data_produk.stok << "\n";
            std::cout << "Spec  : " << berikutnya->data_produk.spesifikasi << "\n";

            std::cout << "\n1. Beli Produk\n0. Kembali\nPilih: ";
            int beli;
            std::cin >> beli;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (beli == 1)
            {
                if (beliProduk(berikutnya))
                    simpanTreeKeCSV(akar, "CSV/tree_data.csv");
            }
            return;
        }

        saatIni = berikutnya;
    }
}

// pilih level untuk admin
int pilihLevel()
{
    std::cout << "\nPilih level:\n";
    std::cout << "1. Kategori Utama\n";
    std::cout << "2. Sub-Kategori\n";
    std::cout << "3. Brand\n";
    std::cout << "4. Produk\n";
    std::cout << "0. Kembali\n";
    std::cout << "Pilih: ";

    int pilihan;
    if (!(std::cin >> pilihan))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return pilihan;
}

std::string dapatkanTipeLevel(int level)
{
    switch (level)
    {
    case 1:
        return "Kategori Utama";
    case 2:
        return "Sub-Kategori";
    case 3:
        return "Brand";
    case 4:
        return "Produk";
    default:
        return "";
    }
}

// Mendapatkan tipe parent yang valid untuk setiap level
std::string dapatkanTipeParentValid(int level)
{
    switch (level)
    {
    case 1:
        return "Root";
    case 2:
        return "Kategori Utama";
    case 3:
        return "Sub-Kategori";
    case 4:
        return "Brand";
    default:
        return "";
    }
}

// Validasi apakah parent sesuai dengan hierarki
bool validasiParent(SimpulPtr simpulParent, int levelAnak)
{
    if (!simpulParent)
        return false;

    std::string tipeParentValid = dapatkanTipeParentValid(levelAnak);
    return simpulParent->tipe_simpul == tipeParentValid;
}

// menu admin
void tampilkanMenuAdmin(SimpulPtr akar)
{
    while (true)
    {
        std::cout << "\nMENU ADMIN\n";
        std::cout << "1. Lihat Tree\n";
        std::cout << "2. Edit\n";
        std::cout << "3. Hapus\n";
        std::cout << "4. Tambah\n";
        std::cout << "0. Logout\n";
        std::cout << "Pilih menu: ";

        int pilihan;
        if (!(std::cin >> pilihan))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (pilihan == 0)
            return;

        if (pilihan == 1)
        {
            std::cout << "\n--- STRUKTUR TREE ---\n";
            tampilkanTree(akar, 0);
            continue;
        }

        if (pilihan == 2)
        {
            int level = pilihLevel();
            if (level == 0 || level == -1)
                continue;

            std::string tipe = dapatkanTipeLevel(level);
            std::string nama;
            std::cout << "Masukkan nama " << tipe << " yang akan diedit: ";
            std::getline(std::cin, nama);

            SimpulPtr simpul = cariSimpul(akar, nama);
            if (!simpul)
            {
                std::cout << "Data tidak ditemukan.\n";
                continue;
            }

            if (simpul->tipe_simpul != tipe)
            {
                std::cout << "Level tidak sesuai.\n";
                continue;
            }

            editSimpul(simpul);
            simpanTreeKeCSV(akar, "CSV/tree_data.csv");
            continue;
        }

        if (pilihan == 3)
        {
            int level = pilihLevel();
            if (level == 0 || level == -1)
                continue;

            std::string tipe = dapatkanTipeLevel(level);
            std::string nama;
            std::cout << "Masukkan nama " << tipe << " yang akan dihapus: ";
            std::getline(std::cin, nama);

            SimpulPtr simpul = cariSimpul(akar, nama);
            if (!simpul)
            {
                std::cout << "Data tidak ditemukan.\n";
                continue;
            }

            if (simpul->tipe_simpul != tipe)
            {
                std::cout << "Level tidak sesuai.\n";
                continue;
            }

            if (hapusSimpul(akar, nama))
                simpanTreeKeCSV(akar, "CSV/tree_data.csv");
            continue;
        }

        if (pilihan == 4)
        {
            int level = pilihLevel();
            if (level == 0 || level == -1)
                continue;

            std::string tipe = dapatkanTipeLevel(level);
            std::string tipeParent = dapatkanTipeParentValid(level);
            std::string namaInduk;

            // Kategori Utama langsung ditambahkan ke root
            if (level == 1)
            {
                namaInduk = akar->data;
            }
            else
            {
                std::cout << "Masukkan nama parent (" << tipeParent << "): ";
                std::getline(std::cin, namaInduk);

                SimpulPtr simpulParent = cariSimpul(akar, namaInduk);
                if (!simpulParent)
                {
                    std::cout << "Parent tidak ditemukan.\n";
                    continue;
                }

                if (!validasiParent(simpulParent, level))
                {
                    std::cout << "Parent harus bertipe " << tipeParent << ".\n";
                    continue;
                }
            }

            if (tambahSimpul(akar, namaInduk, tipe))
                simpanTreeKeCSV(akar, "CSV/tree_data.csv");
            continue;
        }

        std::cout << "Pilihan tidak valid.\n";
    }
}

// menu pembeli
void tampilkanMenuPembeli(SimpulPtr akar)
{
    while (true)
    {
        std::cout << "\nMENU PEMBELI\n";
        std::cout << "Pilih kategori utama:\n";

        int indeks = 1;
        for (auto &anakSimpul : akar->anak)
        {
            std::cout << indeks << ". " << anakSimpul->data << "\n";
            indeks++;
        }

        // cari produk
        std::cout << indeks << ". Cari Produk\n";
        int menuCari = indeks;

        std::cout << "0. Logout\n";
        std::cout << "Pilih menu: ";

        int pilihan;
        if (!(std::cin >> pilihan))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (pilihan == 0)
            return;

        if (pilihan == menuCari)
        {
            std::string katakunci;
            std::cout << "Masukkan keyword: ";
            std::getline(std::cin, katakunci);
            cariProduk(akar, katakunci);
            continue;
        }

        if (pilihan >= 1 && pilihan < menuCari)
        {
            SimpulPtr kategori = akar->anak[pilihan - 1];
            jelajahiHierarki(kategori);
            continue;
        }

        std::cout << "Pilihan tidak valid.\n";
    }
}

int main()
{
    SimpulPtr akar = std::make_shared<Simpul>("", "Root");
    muatTreeDariCSV(akar, "CSV/tree_data.csv");
    akar_global = akar;

    while (true)
    {
        int peran = pilihPeranAwal();
        // pembeli
        if (peran == 1)
        {
            int sub;
            std::cout << "1. Login\n2. Signup\nPilih: ";
            std::cin >> sub;
            std::cin.ignore();

            if (sub == 1)
                loginPengguna(PEMBELI);
            else
                daftarPengguna();

            tampilkanMenuPembeli(akar);
        }

        // admin
        else if (peran == 2)
        {
            Pengguna admin = loginPengguna(ADMIN);
            if (admin.peran == ADMIN)
                tampilkanMenuAdmin(akar);
        }
    }

    return 0;
}
