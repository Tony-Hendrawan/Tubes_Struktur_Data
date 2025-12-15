#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include "Data.h"
#include <string>

// Manajemen tree
void tambahAnak(SimpulPtr induk, SimpulPtr anak);
void tampilkanTree(SimpulPtr simpul, int level = 0);
SimpulPtr cariSimpul(SimpulPtr akar, const std::string &target);
bool hapusSimpul(SimpulPtr akar, const std::string &target);
void editSimpul(SimpulPtr simpul);
bool tambahSimpul(SimpulPtr akar, const std::string &namaInduk, const std::string &tipeSimpul);
void cariProduk(SimpulPtr akar, const std::string &katakunci);
bool beliProduk(SimpulPtr produk);
void kumpulkanSemuaSimpul(SimpulPtr s, std::vector<SimpulPtr> &hasil);

// load/save seluruh tree
void muatTreeDariCSV(SimpulPtr akar, const std::string &namaFile);
void simpanTreeKeCSV(SimpulPtr akar, const std::string &namaFile);

// menu
void tampilkanMenuAnak(SimpulPtr induk);
SimpulPtr pilihAnak(SimpulPtr induk);
void jelajahiHierarki(SimpulPtr akar);

#endif
