#include "TreeManager.h"
#include "Auth.h"
#include <iostream>
#include <limits>
#include <cctype>

void showChildrenMenu(NodePtr parent)
{
    if (!parent)
        return;

    int index = 1;
    for (auto &child : parent->children)
    {
        std::string name =
            (child->node_type == "Produk") ? child->product_data.name : child->data;

        std::cout << index++ << ". " << name << "\n";
    }
}

NodePtr chooseChild(NodePtr parent)
{
    if (!parent)
        return nullptr;

    showChildrenMenu(parent);

    int choice;
    std::cout << "Pilih nomor: ";
    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > parent->children.size())
    {
        std::cout << "Pilihan tidak ada\n";
        return nullptr;
    }

    return parent->children[choice - 1];
}

// Menu
void browseByHierarchy(NodePtr start)
{
    NodePtr current = start;

    while (current)
    {
        NodePtr next = chooseChild(current);
        if (!next)
            return;

        if (next->node_type == "Produk")
        {
            std::cout << "\nDETAIL PRODUK \n";
            std::cout << "Nama  : " << next->product_data.name << "\n";
            std::cout << "Harga : " << next->product_data.price << "\n";
            std::cout << "Stok  : " << next->product_data.stock << "\n";
            std::cout << "Spec  : " << next->product_data.specification << "\n";
            return;
        }

        current = next;
    }
}

// menu pembeli
void showBuyerMenu(NodePtr root)
{
    while (true)
    {
        std::cout << "\nMENU PEMBELI\n";
        std::cout << "Pilih kategori utama:\n";

        int index = 1;
        for (auto &child : root->children)
        {
            std::cout << index << ". " << child->data << "\n";
            index++;
        }

        // cari produk
        std::cout << index << ". Cari Produk\n";
        int searchMenu = index;

        std::cout << "0. Logout\n";
        std::cout << "Pilih menu: ";

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            return;

        if (choice == searchMenu)
        {
            continue;
        }

        if (choice >= 1 && choice < searchMenu)
        {
            NodePtr kategori = root->children[choice - 1];
            browseByHierarchy(kategori);
            continue;
        }

        std::cout << "Pilihan tidak valid.\n";
    }
}

int main()
{
    NodePtr root = std::make_shared<Node>("", "Root");
    loadTreeFromCSV(root, "CSV/tree_data.csv");

    while (true)
    {
        int role = selectInitialRole();
        // pembeli
        if (role == 1)
        {
            int sub;
            std::cout << "1. Login\n2. Signup\nPilih: ";
            std::cin >> sub;
            std::cin.ignore();

            if (sub == 1)
                loginUser(PEMBELI);
            else
                signupUser();

            showBuyerMenu(root);
        }

        // admin
        else if (role == 2)
        {
            loginUser(ADMIN);
        }
    }

    return 0;
}
