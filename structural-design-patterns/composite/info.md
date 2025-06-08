# Composite Pattern in C++

---

## 🟦 What is the Composite Pattern?

The **Composite Pattern** is a structural design pattern that lets you compose objects into tree structures to represent part-whole hierarchies.  
It allows clients to treat individual objects and compositions of objects uniformly.

---

## 🟦 Why Use the Composite Pattern?

- To represent hierarchies of objects (like files and directories, or GUI components).
- To allow clients to treat single objects and groups of objects in the same way.
- To simplify client code by eliminating the need to distinguish between leaves and composites.

---

## 🟦 Advantages of Composite

- **Uniformity:** Treats individual objects and composites uniformly.
- **Extensibility:** Easy to add new types of components.
- **Simplicity:** Simplifies client code that uses complex tree structures.

---

## 🟦 Disadvantages of Composite

- **Overhead:** May introduce unnecessary complexity for simple structures.
- **Type Safety:** Can make it harder to restrict certain operations to specific component types.

---

## ✅ Key Features of the Composite Pattern

- **Component:**  
  An abstract base class/interface for all objects in the composition (e.g., `FilesystemComponent`).

- **Leaf:**  
  Represents individual objects in the composition (e.g., `File`).

- **Composite:**  
  Represents groups of components and implements child-related operations (e.g., `Directory`).

- **Client:**  
  Works with all components through the base interface.

---

## 🛠️ Scope for Further Modifications

- **Add More Leaf Types:**  
  Add new leaf classes for different objects.

- **Add More Composite Types:**  
  Add new composite classes for different groupings.

- **Enhanced Operations:**  
  Add more operations to the component interface as needed.

---

## ⚠️ What NOT to Do

- Do **not** duplicate code for handling single objects and groups.
- Do **not** tightly couple client code to leaf or composite classes.
- Do **not** break the uniform interface.

---

## 🟦 Interview Questions and Answers

### 1. What is the Composite pattern?
**Answer:**  
A structural pattern that lets you compose objects into tree structures and treat individual objects and groups uniformly.

**Example:**  
```cpp
class FilesystemComponent {
public:
    virtual void showDetails(int indent = 0) const = 0;
    virtual ~FilesystemComponent() = default;
};
class File : public FilesystemComponent {
public:
    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "File\n";
    }
};
class Directory : public FilesystemComponent {
    std::vector<std::shared_ptr<FilesystemComponent>> children;
public:
    void add(const std::shared_ptr<FilesystemComponent>& c) { children.push_back(c); }
    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "Directory\n";
        for (const auto& child : children) child->showDetails(indent + 2);
    }
};
```

---

### 2. When would you use the Composite pattern?
**Answer:**  
When you need to work with tree structures and want to treat individual objects and groups of objects in the same way.

---

### 3. How do you implement the Composite pattern in C++?
**Answer:**  
- Define a base component interface.
- Implement leaf classes for individual objects.
- Implement composite classes for groups, managing child components.

---

### 4. How do you use the Composite pattern in client code?
**Answer:**  
- Create leaf and composite objects.
- Build the tree structure by adding children to composites.
- Call operations (like `showDetails()`) on the root; the operation propagates through the tree.

**Example:**
```cpp
auto file1 = std::make_shared<File>("Document.txt");
auto dir = std::make_shared<Directory>("Docs");
dir->add(file1);
dir->showDetails();
```

---

## 🟦 Example Usage

```cpp
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
```

---