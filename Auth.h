#ifndef AUTH_H
#define AUTH_H

#include <string>

enum PeranPengguna
{
    TIDAK_DIKETAHUI,
    PEMBELI,
    ADMIN
};

struct Pengguna
{
    std::string nama_pengguna;
    PeranPengguna peran = TIDAK_DIKETAHUI;
};

int pilihPeranAwal();
Pengguna loginPengguna(PeranPengguna peran);
Pengguna daftarPengguna();

#endif
