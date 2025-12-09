#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <memory>

struct ProductInfo
{
    std::string name;
    long long price = 0;
    int stock = 0;
    std::string specification;
};

struct Node;
typedef std::shared_ptr<Node> NodePtr;

struct Node
{
    std::string data;
    std::string node_type; // semua kategori
    ProductInfo product_data;
    std::vector<NodePtr> children;
    NodePtr parent;

    Node(const std::string &val = "", const std::string &type = "Kategori")
        : data(val), node_type(type), parent(nullptr) {}

    Node(const std::string &name, long long price, int stock, const std::string &spec = "")
        : data(""), node_type("Produk"), parent(nullptr)
    {
        product_data.name = name;
        product_data.price = price;
        product_data.stock = stock;
        product_data.specification = spec;
    }
};

#endif
