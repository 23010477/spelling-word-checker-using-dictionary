# Spelling Checker using AVL Trees (C Project)

This project is a **spelling checker** built in **C**, utilizing a **self-balancing AVL tree** to store and manage a dictionary of words. It reads a list of words from a file, stores them efficiently in a balanced binary search tree, and checks if user-inputted words exist in the dictionary.

---

## 💡 Features

- Reads dictionary words from a file and stores them in an AVL tree.
- Accepts a sentence from the user and checks each word for correctness.
- Provides suggestions (successor, predecessor, and closest match) for misspelled words.
- Colored terminal output for clarity.
- Balanced insertion using AVL rotations.

---

## 📁 File Structure

- `spelling_words.c`: Main source code file.
- `Dictionary.txt`: The dictionary file (must be provided in the specified path).

---

## 🧠 Data Structure Used

- **AVL Tree**: For efficient insertion and search operations.
- Each node stores:
  - The word.
  - Pointers to left, right, and parent nodes.
  - The height of the node for balance calculation.

---

## ✅ How to Use

1. Make sure the file `Dictionary.txt` is available at:
