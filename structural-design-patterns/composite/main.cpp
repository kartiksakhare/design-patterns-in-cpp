/*
 * Composite Pattern Example: Representing a filesystem hierarchy (directories and files).
 *
 * - Component: FilesystemComponent (interface for files and directories)
 * - Leaf: File (represents a single file)
 * - Composite: Directory (can contain files and/or other directories)
 *
 * This demonstrates how the Composite pattern allows you to treat individual objects (files)
 * and compositions of objects (directories) uniformly. You can build complex tree structures
 * and perform operations (like showDetails) recursively on the whole structure.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Component interface: FilesystemComponent
class FilesystemComponent {
public:
    // Method to display the component's name (with indentation for hierarchy)
    virtual void showDetails(int indent = 0) const = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~FilesystemComponent() = default;
};

// Leaf: File
class File : public FilesystemComponent {
private:
    std::string name;
public:
    explicit File(std::string name) : name(std::move(name)) {}
    // Displays the file's name with indentation
    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "File: " << name << std::endl;
    }
};

// Composite: Directory
class Directory : public FilesystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FilesystemComponent>> children;
public:
    explicit Directory(std::string name) : name(std::move(name)) {}
    // Adds a child component (file or directory)
    void add(const std::shared_ptr<FilesystemComponent>& component) {
        children.push_back(component);
    }
    // Removes a child component (removes all occurrences)
    void remove(const std::shared_ptr<FilesystemComponent>& component) {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }
    // Displays the directory's name and its children with indentation
    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "Directory: " << name << std::endl;
        for (const auto& child : children) {
            child->showDetails(indent + 2);
        }
    }
};

// Main function to demonstrate the Composite pattern
int main() {
    // Create files (leaves)
    auto file1 = std::make_shared<File>("Document.txt");
    auto file2 = std::make_shared<File>("Photo.jpg");
    auto file3 = std::make_shared<File>("Presentation.pptx");

    // Create directories (composites)
    auto dir1 = std::make_shared<Directory>("Documents");
    auto dir2 = std::make_shared<Directory>("Photos");
    auto rootDir = std::make_shared<Directory>("Root");

    // Add files to directories
    dir1->add(file1);
    dir2->add(file2);
    dir2->add(file3);

    // Add directories to the root directory
    rootDir->add(dir1);
    rootDir->add(dir2);

    // Display the filesystem structure
    std::cout << "Filesystem Structure:" << std::endl;
    rootDir->showDetails();
    std::cout << std::endl;

    // Remove a file and display the updated structure
    dir2->remove(file2);
    std::cout << "Updated Filesystem Structure after removing Photo.jpg:" << std::endl;
    rootDir->showDetails();
    std::cout << std::endl;

    // Add a new file to the root directory
    auto file4 = std::make_shared<File>("Readme.txt");
    rootDir->add(file4);
    std::cout << "Updated Filesystem Structure after adding Readme.txt:" << std::endl;
    rootDir->showDetails();
    std::cout << std::endl;

    // Clean up is handled by smart pointers
    return 0;
}