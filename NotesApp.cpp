#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Note {
    string title;
    string path; 

void help();

void takeNote(Note *note);

void viewNote();

void deleteNote();

void noteStats();

void searchIn();

string listNotes();

void searchFor(string &title, string &searchString);

void switchText(string &from, string &to, string &title);

bool nameTaken(string &name);

int main() {
    Note note;
    fstream file;
    int choice;
    do {
        cout << "Make a choice:\n"
             << "1: Add note\n"
             << "2: View note\n"
             << "3: Delete note\n"
             << "4: Print note stats\n"
             << "5: Search through notes\n"
             << "6: Help\n"
             << "7: Exit\n";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                takeNote(&note);
                break;
            case 2:
                viewNote();
                break;
            case 3:
                deleteNote();
                break;
            case 4:
                noteStats();
                break;
            case 5:
                searchIn();
                break;
            case 6:
                help();
                break;
            case 7:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 7);
}

void help() {
    cout << "-------------------------------------------------------------------------------------------------------\n"
            "HELP!\n"
            "-------------------------------------------------------------------------------------------------------\n"
            "---------------- Description: ----------------\n"
            "This is a menu driven, modular note-taking program.\n"
            "It can Add, View, Delete (sort of), Search through and also calculate note contents.\n"
            "---------------- How it works: ----------------\n"
            "The takeNote function creates the notes as .txt files and accepts input including new line\ncharacters "
            "until it encounters the character '$' at which point it stops and that's the whole note.\n"
            "It also creates a NoteList.txt file in order to track the notes created so far.\n"
            "The NoteList.txt is used to prevent overwriting a note (Even though it's in the PDF we did not use ios::noreplace"
            "since it's a c++23 feature and we could not make it work on everyone's device.) "
            "The NoteList.txt is also choosing a note in the other functions.\n"
            "Since we were told to avoid using things we didnt learn about. When deleting a note the .txt file IS NOT REMOVED!\n"
            "Instead its contents are cleared and it is removed from the notes list.\n"
            "This allows us to overwrite it if we want. In order to remove the specific note from "
            "the notes list file:\nWe copy the whole thing into a second notes list file except that specific note name "
            "and copy it back.\n"
}

void takeNote(Note *note) {
    cout << "Enter the title of the note:\n";
    getline(cin, note->title);
    note->title += ".txt";
    // note->path = "NoteFiles/" + note->title;
    if (nameTaken(note->title)) {
        cout << "Note name already taken.\nChoose another name.\n";
        return;
    }
    ofstream fout;
    fout.open("NoteList.txt", ios::app);
    if (!fout.is_open()) {
        cout << "Unable to open 'NoteList.txt' in takeNote\n";
    } else {
        fout << note->title << '\n';
    }
    fout.close();
    cout << "Enter the note. End with a '$'\n";
    fout.open(note->title, ios::out);
    if (!fout.is_open()) {
        cout << "Unable to open " + note->title + " in takeNote\n";
        return;
    }
    string line;
    getline(cin, line, '$');
    fout << line << "\n";
    fout.close();
}

bool nameTaken(string &name) {
    ifstream fin;
    fin.open("NoteList.txt", ios::in);
    if (!fin.is_open()) {
        return false;
    } else {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            if (line == name) {
                return true;
            }
        }
    }
    return false;
}

void viewNote() {
    string title = listNotes();
    if (title == "") {
        return;
    }
    cout << "------------------------------------------------\n";
    cout << title << '\n';
    cout << "------------------------------------------------\n";
    ifstream fin;
    fin.open(title, ios::in);
    if (!fin.is_open()) {
        cout << "Unable to open '" + title + "' in viewNote.\n";
    } else {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            cout << line << "\n";
        }
    }
    fin.close();
    cout << "------------------------------------------------\n";
}

void deleteNote() {
    string title = listNotes();
    if (title == "") {
        return;
    }
    ofstream fout;
    fout.open(title, ios::out);
    if (!fout.is_open()) {
        cout << "Unable to clear " + title + "\n";
    } else {
        fout.close();
    }
    string path1 = "NoteList.txt";
    string path2 = "NoteList2.txt";
    switchText(path1, path2, title);
    switchText(path2, path1, title);
    cout << "File deleted (cleared) successfully.\n";
}

void switchText(string &from, string &to, string &title) {
    ifstream fin;
    fin.open(from, ios::in);
    ofstream fout;
    fout.open(to, ios::out);
    if (!fin.is_open() || !fout.is_open()) {
        cout << "Unable to open 'NoteList.txt' or 'NoteList2.txt' in deleteNote.\n";
    } else {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            if (line == title) {
                continue;
            }
            fout << line << "\n";
        }
        fout.close();
    }
}

string listNotes() {
    ifstream fin;
    fin.open("NoteList.txt", ios::in | ios::out);
    int count = 0;
    while (!fin.eof()) {
        string line;
        getline(fin, line);
        if (line == "") {
            continue;
        }
        count++;
    }
    string *notes = new string[count];
    fin.clear();
    fin.seekg(0, ios::beg);
    int i = 0;
    string line;
    while (!fin.eof()) {
        getline(fin, line);
        if (line == "") {
            continue;
        }
        notes[i] = line;
        cout << i + 1 << ": " << notes[i] << "\n";
        i++;
    }
    fin.close();
    int choice = 0;
    if (i == 0) {
        cout << "No notes found\n";
        return "";
    }
    while (choice < 1 || choice > count) {
        cout << "Enter your choice number:\n";
        cin >> choice;
        cin.ignore();
        if (choice < 1 || choice > count) {
            cout << "Invalid choice.\n";
        }
    }
    // delete[] notes; // this causes an error when choosing the first note.
    return notes[choice - 1];
}

void noteStats() {
    string choice = listNotes();
    if (choice == "") {
        return;
    }
    ifstream fin;
    fin.open(choice, ios::in);
    if (!fin.is_open()) {
        cout << "Unable to open '" << choice << "'\n";
    } else {
        int wordCount = 0;
        int lineCount = 0;
        int charCount = 0;
        int totalChar = 0;
        while (!fin.eof()) {
            char c;
            fin.get(c);
            totalChar++;
            if (c == '\n') {
                lineCount++;
            }
            if (c == ' ' || c == '\n') {
                wordCount++;
            } else {
                charCount++;
            }
        }
        cout << "------------------------------------------------\n";
        cout << choice << '\n';
        cout << "------------------------------------------------\n";
        cout << "Lines: " << lineCount - 1 << '\n';
        cout << "Words: " << wordCount - 1 << '\n';
        cout << "Characters: " << charCount << '\n';
        cout << "Total characters: " << totalChar << '\n';
        cout << "------------------------------------------------\n";
    }
}

void searchIn() {
    cout << "What are you searching for:\n";
    string searchString;
    getline(cin, searchString);
    cout << "------------------------------------------------\n";
    cout << "Searching for '" << searchString << "'\n";
    cout << "------------------------------------------------\n";
    ifstream fin;
    fin.open("NoteList.txt", ios::in);
    if (!fin.is_open()) {
        cout << "Unable to open 'NoteList.txt' in searchIn.\n";
    } else {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            searchFor(line, searchString);
        }
    }
    cout << "------------------------------------------------\n";
}

void searchFor(string &title, string &searchString) {
    if (title == "" || searchString == "") {
        return;
    }
    bool foundResults = false;
    ifstream fin;
    fin.open(title, ios::in);
    int lineNum = 1;
    string found;
    if (!fin.is_open()) {
        cout << "Unable to open '" + title + "' in searchFor.\n";
    } else {
        while (!fin.eof()) {
            char c;
            fin.get(c);
            if (c == '\n') {
                lineNum++;
            }
            if (c == searchString[0]) {
                found += c;
                for (int i = 1; i < searchString.length(); i++) {
                    char c;
                    fin.get(c);
                    if (c == '\n') {
                        lineNum++;
                    }
                    if (c == searchString[i]) {
                        found += searchString[i];
                    } else {
                        found = "";
                    }
                }
                if (found == searchString) {
                    cout << "'" << found << "' found in '" << title << "' on line number: " << lineNum << '\n';
                    foundResults = true;
                }
                found = "";
            }
        }
    }
    if (!foundResults) {
        cout << "No results\n";
    }
}
