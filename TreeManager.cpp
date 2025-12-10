// TreeManager.cpp
#include "TreeManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

// Membangun Tree Awal

void addChild(NodePtr parent, NodePtr child)
{
    if (parent && child)
    {
        child->parent = parent;
        parent->children.push_back(child);
    }
}

// Menampilkan Tree
void displayTree(NodePtr node, int level)
{
    if (!node)
        return;

    std::string indent(level * 4, ' ');

    if (node->node_type == "Produk")
    {
        std::cout << indent << "- [PRODUK] " << node->product_data.name
                  << " (Rp " << node->product_data.price
                  << ", Stok: " << node->product_data.stock
                  << ") Spec: " << node->product_data.specification << "\n";
    }
    else
    {
        std::cout << indent << "[" << node->node_type << "] " << node->data << "\n";
    }

    for (auto &child : node->children)
        displayTree(child, level + 1);
}

// Mencari Node
NodePtr findNode(NodePtr root, const std::string &target)
{
    if (!root)
        return nullptr;

    std::string current =
        (root->node_type == "Produk") ? root->product_data.name : root->data;

    std::string lcur = current;
    std::string ltar = target;

    std::transform(lcur.begin(), lcur.end(), lcur.begin(), ::tolower);
    std::transform(ltar.begin(), ltar.end(), ltar.begin(), ::tolower);

    if (lcur == ltar)
        return root;

    for (auto &child : root->children)
        if (auto f = findNode(child, target))
            return f;

    return nullptr;
}

// Menghapus Node
bool deleteNode(NodePtr root, const std::string &target)
{
    if (!root)
        return false;

    NodePtr targetNode = findNode(root, target);
    if (!targetNode)
    {
        std::cout << "Node tidak ditemukan.\n";
        return false;
    }

    if (!targetNode->parent)
    {
        std::cout << "Tidak bisa hapus root.\n";
        return false;
    }

    auto parent = targetNode->parent;
    auto &kids = parent->children;

    kids.erase(
        std::remove_if(kids.begin(), kids.end(),
                       [&](NodePtr n)
                       {
                           std::string nm =
                               (n->node_type == "Produk") ? n->product_data.name : n->data;
                           std::string ln = nm, lt = target;
                           std::transform(ln.begin(), ln.end(), ln.begin(), ::tolower);
                           std::transform(lt.begin(), lt.end(), lt.begin(), ::tolower);
                           return ln == lt;
                       }),
        kids.end());

    std::cout << "Node berhasil dihapus.\n";
    return true;
}

// Edit Node
void editNode(NodePtr node)
{
    if (!node)
        return;

    if (node->node_type == "Produk")
    {
        std::string nm;
        std::cout << "Nama baru (kosong = skip): ";
        std::getline(std::cin, nm);
        if (!nm.empty())
            node->product_data.name = nm;

        long long pr;
        std::cout << "Harga baru (0 skip): ";
        std::cin >> pr;
        if (pr > 0)
            node->product_data.price = pr;
        std::cin.ignore();

        int st;
        std::cout << "Stok baru (-1 skip): ";
        std::cin >> st;
        if (st >= 0)
            node->product_data.stock = st;
        std::cin.ignore();

        std::string sp;
        std::cout << "Spec baru (kosong skip): ";
        std::getline(std::cin, sp);
        if (!sp.empty())
            node->product_data.specification = sp;
    }
    else
    {
        std::string nm;
        std::cout << "Nama baru: ";
        std::getline(std::cin, nm);
        if (!nm.empty())
            node->data = nm;
    }

    std::cout << "Data berhasil diperbarui.\n";
}

// Menyimpan tree ke CSV
void collectAllNodes(NodePtr n, std::vector<NodePtr> &out)
{
    if (!n)
        return;
    out.push_back(n);
    for (auto &c : n->children)
        collectAllNodes(c, out);
}

void saveTreeToCSV(NodePtr root, const std::string &filename)
{
    std::ofstream f(filename);
    if (!f.is_open())
    {
        std::cout << "Gagal membuka CSV.\n";
        return;
    }

    f << "Level;Nama;Parent;Harga;Stok;Spesifikasi\n";

    std::vector<NodePtr> all;
    collectAllNodes(root, all);

    for (auto &n : all)
    {
        std::string type = n->node_type;
        std::string nama =
            (type == "Produk") ? n->product_data.name : n->data;

        std::string parent = "NULL";
        if (n->parent)
            parent = (n->parent->node_type == "Produk")
                         ? n->parent->product_data.name
                         : n->parent->data;

        std::string price = (type == "Produk") ? std::to_string(n->product_data.price) : "";
        std::string stock = (type == "Produk") ? std::to_string(n->product_data.stock) : "";
        std::string spec = (type == "Produk") ? n->product_data.specification : "";

        f << type << ";" << nama << ";" << parent << ";"
          << price << ";" << stock << ";" << spec << "\n";
    }
}

// Load Tree dari CSV
void loadTreeFromCSV(NodePtr root, const std::string &filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
    {
        std::cout << "(INFO) CSV tidak ditemukan.\n";
        return;
    }

    std::string line;
    std::getline(f, line); // header

    std::vector<NodePtr> allNodes;
    allNodes.push_back(root);

    while (std::getline(f, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string level, name, parent, price, stock, spec;

        std::getline(ss, level, ';');
        std::getline(ss, name, ';');
        std::getline(ss, parent, ';');
        std::getline(ss, price, ';');
        std::getline(ss, stock, ';');
        std::getline(ss, spec, ';');

        NodePtr parentNode = nullptr;
        if (parent == "NULL")
        {
            parentNode = root;
        }
        else
        {
            for (auto it = allNodes.rbegin(); it != allNodes.rend(); ++it)
            {
                std::string nodeName = ((*it)->node_type == "Produk") 
                    ? (*it)->product_data.name 
                    : (*it)->data;
                
                std::string lnodeName = nodeName;
                std::string lparent = parent;
                std::transform(lnodeName.begin(), lnodeName.end(), lnodeName.begin(), ::tolower);
                std::transform(lparent.begin(), lparent.end(), lparent.begin(), ::tolower);
                
                if (lnodeName == lparent)
                {
                    parentNode = *it;
                    break;
                }
            }
            
            if (!parentNode)
                parentNode = root;
        }

        if (level == "Root")
        {
            root->data = name;
        }
        else if (level == "Produk")
        {
            NodePtr newNode = std::make_shared<Node>(name,
                                            std::stoll(price),
                                            std::stoi(stock),
                                            spec);
            addChild(parentNode, newNode);
            allNodes.push_back(newNode);
        }
        else
        {
            NodePtr newNode = std::make_shared<Node>(name, level);
            addChild(parentNode, newNode);
            allNodes.push_back(newNode);
        }
    }
}
