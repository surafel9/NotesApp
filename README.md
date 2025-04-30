# 📒 Simple Note-Taking Program (C++)

A beginner-friendly, console-based **note-taking app** written in C++!
It lets you add, view, delete, get statistics, and search through your notes — all stored as plain text files.

---

## 🚀 Features

- ✅ **Add Notes** — Create and save notes easily
- ✅ **View Notes** — Read your saved notes
- ✅ **Delete Notes** — Clear out notes you no longer need
- ✅ **Note Stats** — Get lines, words, characters count
- ✅ **Search** — Find text across all notes
- ✅ **Help** — See how the program works

---

## 💻 How to Run

### 1. Compile
```bash
g++ NotesApp.cpp -o NotesApp
```

### 2. Run
```bash
./NotesApp
```

### 3. Use the Menu
Just enter numbers `1` to `7` based on what you want to do!

---

## 📝 Usage Guide

### ➕ Add a Note
- Choose **Option 1**
- Enter a unique title (without `.txt`, it'll be added automatically)
- Type your note
- When done, enter `$` on a new line to save and exit

### 👀 View a Note
- Choose **Option 2**
- Select from the listed note titles
- See your note displayed in the console

### 🗑️ Delete a Note
- Choose **Option 3**
- Select the note
- Note: this clears the content and removes it from the list — but the file stays on disk

### 📊 Note Statistics
- Choose **Option 4**
- Select a note
- View:
  - ✅ Lines count
  - ✅ Words count
  - ✅ Characters (without spaces/newlines)
  - ✅ Total characters (including spaces/newlines)

### 🔍 Search Notes
- Choose **Option 5**
- Enter your keyword
- Matches across **all notes** will be displayed with note name & line numbers

### ❓ Help
- Choose **Option 6** to learn about the program

---

## 📂 Files Created

- **`NoteList.txt`**  ➡️ Tracks all your note titles
- **`<note_name>.txt`** ➡️ Stores your actual note

Example:
```plaintext
NoteList.txt
MyFirstNote.txt
ShoppingList.txt
```

---

## ⚠️ Important Notes

- Notes are saved in the **current directory** where you run the program
- Deleting a note clears its content but doesn't remove the `.txt` file physically
- Uses only **standard C++ file handling** (`fstream`, `ifstream`, `ofstream`)

---

## 👨‍💻 Author
- Made for educational purposes and practice with C++ file I/O and menus.
- Feel free to fork and improve!
- GitHub: surafel9

---

## ⭐️ Like it?
If you find this useful, star ⭐ this repo and share it with your fellow C++ learners!

---


