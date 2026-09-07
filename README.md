# Library Management System

A console-based Library Management System written in C++ for the **Data Structures and Algorithms** course project.

The program lets a library employee manage books and sections entirely in memory, using linked structures instead of arrays or containers from the STL:

- **Books** are stored in a **doubly linked list** (`NodeBook` / `DoublyLinkedList`).
- **Sections** are stored in a **singly linked list** (`NodeSection` / `LinkedList`).
- **Sorting** is done with an in-place **merge sort** on the books list.
- **Searching** is a linear, case-insensitive substring scan over the list.

## Group E

- Reda Alqatifi
- Ali Alburahim
- Mohammed Aljasem
- Mahdi Alhashim

## Features

| Menu | What it does |
| --- | --- |
| **Add** | Add a new book (title, author, code, section, price, quantity) or a new section. Titles and codes are checked for duplicates; a book with no section is filed under `Neither`. |
| **Remove** | Remove a book by code, or remove a whole section (its books are removed with it). The default `Neither` section is protected and cannot be deleted. |
| **Update** | Edit any field of a book (title, author, code, section, price, quantity) or rename a section. |
| **Sort** | Merge-sort the books by title, code, author, section, price, or quantity. |
| **Search** | Search books by title, code, author, or section, or search sections by name. Matching is case-insensitive and partial. |
| **Display** | Print all books or all sections in a formatted table. |
| **Total** | Total number of books, total number of sections, and a detailed library summary. |

Four sections exist when the program starts: `Neither`, `Fiction`, `Acadimic`, and `Business`.

## Project layout

```
.
├── code/
│   ├── DSAProject_Main.c++     # Entire program (single source file)
│   ├── DSAProject_Main.exe     # Prebuilt Windows executable
│   └── .vscode/settings.json
├── Project description.docx    # Assignment requirements
├── Project description.pdf
├── DSAGE.pptx                  # Presentation slides
└── DSAGER.pdf                  # Project report
```

## Build and run

The project is a single self-contained source file with no dependencies beyond the standard library.

**Windows (PowerShell):**

```powershell
g++ "code/DSAProject_Main.c++" -o "code/DSAProject_Main.exe"
.\code\DSAProject_Main.exe
```

**Linux / macOS:**

```bash
g++ code/DSAProject_Main.c++ -o DSAProject_Main
./DSAProject_Main
```

A prebuilt `DSAProject_Main.exe` is already included for Windows, so you can run it directly without compiling.

## Usage

Run the program and navigate with numbers. The main menu is:

```
============================================================
|                        Main Menu                         |
------------------------------------------------------------
| 1 - Add a new ( book / section ).                        |
| 2 - Remove a ( book / section ).                         |
| 3 - Update a ( book / section ).                         |
| 4 - Sort the books.                                      |
| 5 - Search a ( book / section ).                         |
| 6 - display ( books / sections ).                        |
| 7 - Total ( books / sections ).                          |
| 8 - Exit.                                                |
============================================================

> Enter your choice :
```

Every submenu has a "Back to the Main Menu" option. Invalid or non-numeric input is caught and the prompt is repeated. On exit, all allocated nodes are freed before the program ends.

## Code organisation

The source file groups related functions into `struct`s that act as namespaces, each with a single global instance:

| Struct | Responsibility |
| --- | --- |
| `GeneralFunctions` | Shared helpers: input error handling, lowercasing, line/centred-text printing, pausing, node renumbering, freeing memory. |
| `AddFunctions` | Node creation and insertion for books and sections, input prompts and validation. |
| `RemoveFunctions` | Deletion of book and section nodes, with pointer relinking. |
| `UpdateFunctions` | Field-by-field editing of an existing book or section. |
| `SortFunctions` | `splitList`, `sortedMerge`, and `mergeSort` over the books list. |
| `SearchFunctions` | Case-insensitive linear search for books and sections. |
| `DisplayFunctions` | Table headers and row printing. |
| `TotalFunctions` | Counts and the detailed library summary. |
| `Menues` | The main menu and dispatch to every other menu. |

## Notes

- Data is held in memory only — nothing is saved to disk, so the library resets on every run.
