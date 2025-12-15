#include "Auth.h"
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <conio.h>

static std::map<std::string, std::string> DAFTAR_PENGGUNA = {};

// Input password
std::string inputKataSandi()
{
    std::string kataSandi;
    char karakter;

    while ((karakter = _getch()) != '\r')
    {
        if (karakter == '\b')
        {
            if (!kataSandi.empty())
            {
                kataSandi.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            kataSandi += karakter;
            std::cout << '*';
        }
    }
    std::cout << "\n";
    return kataSandi;
}

// Memilih peran awal
int pilihPeranAwal()
{
    int pilihan = 0;
    while (pilihan != 1 && pilihan != 2)
    {
        std::cout << "\nSELAMAT DATANG DI TOKO GADGET\n\n";
        std::cout << "Masuk sebagai:\n";
        std::cout << "1. Pembeli\n";
        std::cout << "2. Admin\n";
        std::cout << "Pilih (1/2): ";

        if (!(std::cin >> pilihan))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pilihan = 0;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return pilihan;
}

// Login Pengguna
Pengguna loginPengguna(PeranPengguna peran)
{
    Pengguna penggunaSaatIni;
    std::string namaPengguna, kataSandi;
    std::string strPeran = (peran == ADMIN) ? "Admin" : "Pembeli";

    while (true)
    {
        std::cout << "\n--- Login " << strPeran << " ---\n";

        // Nama Pengguna
        while (true)
        {
            std::cout << "Username: ";
            std::getline(std::cin, namaPengguna);
            if (!namaPengguna.empty())
                break;
        }

        // Kata Sandi
        while (true)
        {
            std::cout << "Password: ";
            kataSandi = inputKataSandi();
            if (!kataSandi.empty())
                break;
        }

        // login admin
        if (peran == ADMIN)
        {
            if (namaPengguna == "admin" && kataSandi == "admin123")
            {
                penggunaSaatIni.nama_pengguna = namaPengguna;
                penggunaSaatIni.peran = ADMIN;
                std::cout << "Login Berhasil sebagai Admin\n";
                return penggunaSaatIni;
            }

            std::cout << "Admin salah. Coba lagi.\n";
            continue;
        }

        // login pembeli
        auto it = DAFTAR_PENGGUNA.find(namaPengguna);

        if (it != DAFTAR_PENGGUNA.end() && it->second == kataSandi)
        {
            penggunaSaatIni.nama_pengguna = namaPengguna;
            penggunaSaatIni.peran = PEMBELI;
            std::cout << "Login Berhasil sebagai Pembeli\n";
            return penggunaSaatIni;
        }

        std::cout << "Username atau Password salah. Coba lagi.\n";
    }
}

// Daftar pembeli
Pengguna daftarPengguna()
{
    Pengguna penggunaSaatIni;
    std::string namaBaru, kataSandiBaru;

    std::cout << "\n--- Pendaftaran Akun Pembeli ---\n";

    // Nama pengguna baru
    while (true)
    {
        std::cout << "Masukkan Username Baru: ";
        std::getline(std::cin, namaBaru);

        if (namaBaru.empty())
        {
            continue;
        }

        break;
    }

    // Kata sandi baru
    while (true)
    {
        std::cout << "Masukkan Password Baru: ";
        kataSandiBaru = inputKataSandi();

        if (!kataSandiBaru.empty())
            break;
    }

    // Simpan ke map
    DAFTAR_PENGGUNA[namaBaru] = kataSandiBaru;

    penggunaSaatIni.nama_pengguna = namaBaru;
    penggunaSaatIni.peran = PEMBELI;

    return penggunaSaatIni;
}
