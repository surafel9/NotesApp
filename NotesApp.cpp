#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

struct Note {
    string title;
    string path;
};

void help();
void takeNote(Note *note);
void viewNote();
void deleteNote();
void noteStats();
void searchIn();
string listNotes();
void searchFor(const string &title, const string &searchString);
bool nameTaken(const string &name);

int main() {
    Note note;
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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0; 
        }
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
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 7);

    return 0;
}

void help() {
    cout << "-------------------------------------------------------------------------------------------------------\n"
            "HELP!\n"
            "-------------------------------------------------------------------------------------------------------\n"
            "---------------- Description: ----------------\n"
            "This is a menu driven, modular note-taking program.\n"
            "It can Add, View, Delete, Search through and also calculate note contents.\n"
            "---------------- How it works: ----------------\n"
            "The takeNote function creates the notes as .txt files and accepts input including new line\ncharacters "
            "until it encounters the character '$' on a new line at which point it stops and that's the whole note.\n"
            "It also creates a NoteList.txt file in order to track the notes created so far.\n"
            "The NoteList.txt is also used for choosing a note in the other functions.\n"
            "-------------------------------------------------------------------------------------------------------\n";
}

void takeNote(Note *note) {
    cout << "Enter the title of the note:\n";
    getline(cin, note->title);
    note->title += ".txt";
    
    if (nameTaken(note->title)) {
        cout << "Note name already taken. Choose another name.\n";
        return;
    }

    ofstream list_fout("NoteList.txt", ios::app);
    if (!list_fout.is_open()) {
        cout << "Unable to open 'NoteList.txt' in takeNote\n";
    } else {
        list_fout << note->title << '\n';
    }
    list_fout.close();

    cout << "Enter the note. End with a '$' on a new line.\n";
    ofstream note_fout(note->title);
    if (!note_fout.is_open()) {
        cout << "Unable to open " + note->title + " in takeNote\n";
        return;
    }

    string line;
    while (getline(cin, line)) {
        if (line == "$") {
            break;
        }
        note_fout << line << "\n";
    }
    note_fout.close();
}

bool nameTaken(const string &name) {
    ifstream fin("NoteList.txt");
    if (!fin.is_open()) {
        return false;
    }
    string line;
    while (getline(fin, line)) {
        if (line == name) {
            return true;
        }
    }
    return false;
}

void viewNote() {
    string title = listNotes();
    if (title.empty()) {
        return;
    }

    cout << "------------------------------------------------\n";
    cout << title << '\n';
    cout << "------------------------------------------------\n";

    ifstream fin(title);
    if (!fin.is_open()) {
        cout << "Unable to open '" + title + "' in viewNote.\n";
    } else {
        string line;
        while (getline(fin, line)) {
            cout << line << "\n";
        }
    }
    cout << "------------------------------------------------\n";
}

void deleteNote() {
    string title = listNotes();
    if (title.empty()) {
        return;
    }

    if (remove(title.c_str()) != 0) {
        cout << "Error deleting note file: " << title << "\n";
    }

    ifstream fin("NoteList.txt");
    ofstream fout("NoteList.tmp");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Error opening note list files for modification.\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line != title) {
            fout << line << '\n';
        }
    }

    fin.close();
    fout.close();

    remove("NoteList.txt");
    rename("NoteList.tmp", "NoteList.txt");

    cout << "File '" << title << "' deleted successfully.\n";
}

string listNotes() {
    ifstream fin("NoteList.txt");
    if (!fin.is_open()) {
        cout << "No notes found or 'NoteList.txt' is missing.\n";
        return "";
    }

    vector<string> notes;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            notes.push_back(line);
        }
    }
    fin.close();

    if (notes.empty()) {
        cout << "No notes found.\n";
        return "";
    }

    for (size_t i = 0; i < notes.size(); ++i) {
        cout << i + 1 << ": " << notes[i] << "\n";
    }

    int choice = 0;
    while (true) {
        cout << "Enter your choice number:\n";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();
        if (choice >= 1 && choice <= static_cast<int>(notes.size())) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return notes[choice - 1];
}

void noteStats() {
    string title = listNotes();
    if (title.empty()) {
        return;
    }

    ifstream fin(title);
    if (!fin.is_open()) {
        cout << "Unable to open '" << title << "'\n";
        return;
    }

    int wordCount = 0;
    int lineCount = 0;
    int charCount = 0;
    
    string line;
    while(getline(fin, line)) {
        lineCount++;
        charCount += line.length();
        
        bool inWord = false;
        for(char c : line) {
            if (isspace(c)) {
                inWord = false;
            } else if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
    }

    cout << "------------------------------------------------\n";
    cout << title << '\n';
    cout << "------------------------------------------------\n";
    cout << "Lines: " << lineCount << '\n';
    cout << "Words: " << wordCount << '\n';
    cout << "Characters (no newlines): " << charCount << '\n';
    cout << "------------------------------------------------\n";
}

void searchIn() {
    cout << "What are you searching for:\n";
    string searchString;
    getline(cin, searchString);

    if (searchString.empty()) {
        cout << "Search string cannot be empty.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "Searching for '" << searchString << "'\n";
    cout << "------------------------------------------------\n";

    ifstream fin("NoteList.txt");
    if (!fin.is_open()) {
        cout << "Unable to open 'NoteList.txt' in searchIn.\n";
        return;
    }

    string title;
    bool anyResult = false;
    while (getline(fin, title)) {
        if (title.empty()) continue;
        
        ifstream note_fin(title);
        if (!note_fin.is_open()) continue;

        string line;
        int lineNum = 1;
        while(getline(note_fin, line)) {
            if (line.find(searchString) != string::npos) {
                cout << "Found in '" << title << "' on line " << lineNum << ": " << line << '\n';
                anyResult = true;
            }
            lineNum++;
        }
    }
    if (!anyResult) {
        cout << "No results found.\n";
    }
}
