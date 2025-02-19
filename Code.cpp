#include <iostream>
#include <string>
using namespace std;
struct FileSystemEntry {
string name;
bool isFile;
FileSystemEntry* left;
FileSystemEntry* right;
FileSystemEntry(const string& name, bool isFile) : name(name),
isFile(isFile), left(nullptr), right(nullptr) {}
};
class FileSystemExplorer {
private:
FileSystemEntry* root;
FileSystemEntry* currentDir;
public:
FileSystemExplorer() {
root = new FileSystemEntry("Root", false);
currentDir = root;
}
void insertDirectory(FileSystemEntry* parent, const string& name) {
if (parent) {
FileSystemEntry* newDir = new FileSystemEntry(name, false);
parent->right = newDir;
}
}
void insertFile(FileSystemEntry* parent, const string& name) {
if (parent) {
FileSystemEntry* newFile = new FileSystemEntry(name, true);
parent->right = newFile;
}
}
void listContents(FileSystemEntry* dir) {
if (dir) {
cout << "Contents of " << dir->name << ":\n";
if (dir->left) {
cout << (dir->left->isFile ? "File: " : "Directory: ") << dir->left->name << endl;
}
listContents(dir->right);
}
}
FileSystemEntry* findDirectory(FileSystemEntry* node, const string& name)
{
if (node) {
if (node->right && node->right->name == name && !node->right->isFile) {
}
return node->right;
FileSystemEntry* found = findDirectory(node->right, name);
if (found) return found;
return findDirectory(node->left, name);
}
return nullptr;
}
void printDirectoryStructure(FileSystemEntry* dir, int depth = 0) {
if (dir) {
for (int i = 0; i < depth; ++i) {
cout << " ";
}
cout << "|-- " << dir->name << endl;
if (!dir->isFile) {
printDirectoryStructure(dir->right, depth + 1);
}
}
}
void run() {
while (true) {
cout << "Current Directory: " << currentDir->name << endl;
cout << "Menu:\n";
cout << "1. Create Directory\n2. Create File\n3. List Contents\n4.Change Directory\n5. Print Directory Structure\n6. Exit\n";
int choice;
cin >> choice;
if (choice == 1) {
cout << "Enter directory name: ";
string name;
cin >> name;
insertDirectory(currentDir, name);
} else if (choice == 2) {
cout << "Enter file name: ";
string name;
cin >> name;
insertFile(currentDir, name);
} else if (choice == 3) {
listContents(currentDir);
} else if (choice == 4) {
cout << "Enter directory name to change to: ";
string name;
cin >> name;
FileSystemEntry* foundDir = findDirectory(root, name);
if (foundDir) {
currentDir = foundDir;
} else {
cout << "Directory not found or invalid choice." << endl;
}
} else if (choice == 5) {
cout << "Directory Structure:\n";
printDirectoryStructure(root, 0);
} else if (choice == 6) {
break;
}
}
}
};
int main() {
FileSystemExplorer explorer;
explorer.run();
return 0;
}
