#include "Auth.h"
#include <iostream>
#include <map>
#include <limits>
#include <string>

#include <conio.h>
static std::map<std::string, std::string> USERS = {};

std::string inputPasswordMasked()
{
    std::string password;
    char ch;

    while (true)
    {
        ch = _getch(); // tidak menampilkan input ke layar

        if (ch == 13)
        {
            std::cout << std::endl;
            break;
        }
        else if (ch == 8)
        {
            if (!password.empty())
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    return password;
}

// Memilih role awal
int selectInitialRole()
{
    int choice = 0;
    while (choice != 1 && choice != 2)
    {
        std::cout << "\nSELAMAT DATANG DI TOKO GADGET\n\n";
        std::cout << "Masuk sebagai:\n";
        std::cout << "1. Pembeli\n";
        std::cout << "2. Admin\n";
        std::cout << "Pilih (1/2): ";

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return choice;
}

// Login User
User loginUser(UserRole role)
{
    User current_user;
    std::string username, password;
    std::string role_str = (role == ADMIN) ? "Admin" : "Pembeli";

    while (true)
    {
        std::cout << "\n--- Login " << role_str << " ---\n";

        // Username
        while (true)
        {
            std::cout << "Username: ";
            std::getline(std::cin, username);
            if (!username.empty())
                break;
        }

        // Password
        while (true)
        {
            std::cout << "Password: ";
            password = inputPasswordMasked();
            if (!password.empty())
                break;
        }

        // login admin
        if (role == ADMIN)
        {
            if (username == "admin" && password == "admin123")
            {
                current_user.username = username;
                current_user.role = ADMIN;
                std::cout << "Login Berhasil sebagai Admin\n";
                return current_user;
            }

            std::cout << "Admin salah. Coba lagi.\n";
            continue;
        }

        // login oembveli
        auto it = USERS.find(username);

        if (it != USERS.end() && it->second == password)
        {
            current_user.username = username;
            current_user.role = PEMBELI;
            std::cout << "Login Berhasil sebagai Pembeli\n";
            return current_user;
        }

        std::cout << "Username atau Password salah. Coba lagi.\n";
    }
}

// signup pembeli
User signupUser()
{
    User current_user;
    std::string new_username, new_password;

    std::cout << "\n--- Pendaftaran Akun Pembeli ---\n";

    // Username baru
    while (true)
    {
        std::cout << "Masukkan Username Baru: ";
        std::getline(std::cin, new_username);

        if (new_username.empty())
        {
            continue;
        }

        break;
    }

    // Password baru
    while (true)
    {
        std::cout << "Masukkan Password Baru: ";
        new_password = inputPasswordMasked();

        if (!new_password.empty())
            break;
    }

    // Simpan ke map
    USERS[new_username] = new_password;

    current_user.username = new_username;
    current_user.role = PEMBELI;

    return current_user;
}
