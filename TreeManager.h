#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include "Data.h"
#include <string>

// Manajemen tree
void addChild(NodePtr parent, NodePtr child);
void displayTree(NodePtr node, int level = 0);
NodePtr findNode(NodePtr root, const std::string &target_name);
bool deleteNode(NodePtr root, const std::string &target_name);
void editNode(NodePtr node);

// load/save seluruh tree
void loadTreeFromCSV(NodePtr root, const std::string &filename);
void saveTreeToCSV(NodePtr root, const std::string &filename);

// menu
void showChildrenMenu(NodePtr parent);
NodePtr chooseChild(NodePtr parent);
void browseByHierarchy(NodePtr root);

#endif // TREEMANAGER_H
