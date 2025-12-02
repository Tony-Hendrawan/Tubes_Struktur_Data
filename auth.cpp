#include <iostream>
#include "TOKO_GADGET.h"

using namespace std;

bool loginUser(User users[], int jumlahUser, const string& uname, const string& pw, User &hasil) {
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].username == uname && users[i].password == pw) {
            hasil = users[i];
            return true;
        }
    }
    return false;
}

bool signupUser(User users[], int &jumlahUser, const string& uname, const string& pw) {
    if (jumlahUser >= MAX_USER) {
        cout << "Registrasi gagal: jumlah user telah mencapai batas maksimal." << endl;
        return false; // Tidak bisa tambah user, sudah mencapai batas maksimal
    }

    for (int i = 0 ; i < jumlahUser; i++) {
        if (users[i].username == uname) {
            cout << "Registrasi gagal: username sudah digunakan." << endl;
            return false;
        }
    }


    users[jumlahUser].username = uname;
    users[jumlahUser].password = pw;
    users[jumlahUser].isAdmin = false; // Default bukan admin
    jumlahUser++;
    return true;

    cout << "Registrasi berhasil!" << endl;
    return true;
}