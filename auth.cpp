#include <iostream>
#include "TOKO_GADGET.h"

using namespace std;

//  login user
bool loginUser(User users[], int jumlahUser, const string& uname, const string& pw, User &hasil) {
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].username == uname && users[i].password == pw) {
            hasil = users[i];
            return true;
        }
    }
    return false;
}

// registrasi user
bool signupUser(User users[], int &jumlahUser, const string& uname, const string& pw) {
    for (int i = 0 ; i < jumlahUser; i++) {
        if (users[i].username == uname) {
            cout << "Registrasi gagal: username sudah digunakan." << endl;
            return false;
        }
    }

// nambah user
    users[jumlahUser].username = uname;
    users[jumlahUser].password = pw;
    users[jumlahUser].isAdmin = false; // user bukan admin
    jumlahUser++;
    cout << "Registrasi berhasil!" << endl;
    return true;
}