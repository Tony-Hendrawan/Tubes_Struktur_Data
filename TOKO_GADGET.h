#ifndef TOKO_GADGET_TUBES_H
#define TOKO_GADGET_TUBES_H

#include <string>
#include <vector>
#include <memory> 

using namespace std;

const string ADMIN_UNAME = "admin";
const string ADMIN_PASS = "admin123";

// user
struct User {
    string username;
    string password;
    bool isAdmin = false;
};

// -produk disini guys
struct ProductDetails {
    string spesifikasi;
    int harga = 0; 
    int stok = 0; 
};

/**
 *Node tunggal merepresentasikan Kategori, Sub-Kategori, Brand, atau Produk.
 */
struct Node {
    int id; 
    string data; // Nama Kategori atau Produk
    ProductDetails details; // Diisi hanya jika ini adalah Produk akhir
    
    // Vektor dari Smart Pointer untuk implementasi Recursive Tree
    vector<shared_ptr<Node>> children; 
    
    Node(int newId, const string& d) : id(newId), data(d) {}
};


class ProductTreeManager {
private:
    shared_ptr<Node> root; 
    int nextId; // Counter untuk ID unik produk/kategori
    
public:
    ProductTreeManager();

    // AUTHENTIKASI (Hardcoded)
    bool loginUser(const string& uname, const string& pw, User &hasil);

    //  CSV
    bool loadProdukCSV();
    bool saveProdukCSV();

    // CRUD (Operasi pada Tree)
    // Penambahan node (Kategori/Produk) ke jalur hierarki
    bool tambahNode(const string& parentPath, const string& nama, bool isProduct, const ProductDetails& details = {}); 
    
    // Mencari node/produk berdasarkan keyword
    shared_ptr<Node> cariNode(const string& keyword);
    
    // Memperbarui data pada node
    bool editNode(const string& targetPath, const string& newName, const ProductDetails& newDetails = {});
    
    // Menghapus node dan semua turunannya (recursive delete)
    bool hapusNode(const string& targetPath);

    // Memproses pembelian langsung dan mengurangi stok
    bool beliProduk(int productId, int jumlah);
    
    // Menampilkan seluruh hierarki
    void displayHierarchy() const;

private:
    // Fungsi pembantu untuk navigasi internal tree
    shared_ptr<Node> findNodeByPath(shared_ptr<Node> current, const vector<string>& pathSegments, size_t index);
};

void clearScreen();
void tungguEnter();

#endif 
