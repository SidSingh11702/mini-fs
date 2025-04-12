# Filesystem Simulator

This is a C++ program that simulates a basic filesystem hierarchy using a tree data structure. It supports operations like:

- Creating directory structures from input
- Counting descendants (like counting files/folders in a directory)
- Copying and pasting directories
- Cutting and pasting directories
- Printing the entire tree structure

## 📂 Example Input Format

The first line will contain the number of directories (`n`) in the file system, followed by the number of queries (`q`) on the file system.
```
3 5
```

Then, `n` lines of input represent the directory name followed by the directories/files contained in it. 

```
root a b c
root/a d e
root/c f g
```

Following `q` lines contain the queries on the file system.
```
countDescendants root/a
cutPaste root/a/d root/b
copyPaste root/c/f root/b
countDescendants root/b
countDescendants root/c/f
```

## 🧠 Features

- **`countDescendants <path>`**: Counts all nodes under the given path.
- **`cutPaste <source> <destination>`**: Moves a directory from one place to another.
- **`copyPaste <source> <destination>`**: Copies a directory and its substructure to another location.
- **Prints the tree** after each operation for easy visualization.

## 🛠️ Technologies

- C++
- STL containers (like `vector`, `map`)

## 🏃‍♂️ How to Run

1. Clone the repo:

```bash
git clone https://github.com/SidSingh11702/filesystem-simulator.git
cd filesystem-simulator

g++ -std=c++17 main.cpp -o fs_sim


countDescendants root/s
cutPaste root/s root/x
copyPaste root/x root/s
