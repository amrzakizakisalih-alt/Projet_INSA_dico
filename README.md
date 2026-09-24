# Advanced Dictionary Management System in C

## Overview
This project is an advanced, robust command-line dictionary management system implemented entirely in **C**. It enables users to create, load, manipulate, and cross-reference multiple dictionaries simultaneously using complex dynamic data structures (nested linked lists and alphabetical hash-like indexed arrays). 

Designed with a strong focus on rigorous memory management, low-level string parsing, and structured data processing, the program also features unique cross-dictionary linking mechanisms to track relationships and term occurrences across independent datasets.

---

## Features
- **Dynamic Dictionary Creation:** Build custom alphabetical dictionaries interactively or import existing datasets seamlessly from text files.
- **Advanced CRUD Operations:** Insert, search, modify, and delete words, supporting multiple distinct definitions per single entry.
- **Cross-Dictionary Linking:** Automatically analyze definitions within one dictionary to map, extract words, and establish interactive references to entries in another dictionary.
- **Data Persistence:** Save dictionary states directly to disk and reload them at any time during future sessions.
- **Interactive CLI Menu:** A fully featured, user-friendly menu-driven interface guiding the user through multi-dictionary orchestration and error-handling.

---

## Project Architecture & Data Structures
The project is cleanly modularized into header and source files:
* **`dico.h`**: Header file containing global macros, core structure definitions (`DICO`, `MOTS`, `DEFS`, `LIEN`), and function prototypes.
* **`fct.c`**: Core logic implementation (dictionary initialization, robust memory allocation, custom tokenization/string parsing, alphabetical sorting, file I/O, and cross-referencing algorithms).
* **`main.c`**: Interactive CLI loop managing user choices, multi-dictionary state tracking, and exception handling.

### Core Structures:
- **`DICO`**: An array representing the 26 letters of the alphabet (`a-z`), each pointing to a sorted singly-linked list of words.
- **`MOTS`**: Linked list nodes containing the target word and a pointer to a secondary linked list of definitions (`DEFS`).
- **`DEFS`**: Structure holding definition strings and a pointer to a sub-list of parsed cross-references (`LIEN`).
- **`LIEN`**: Sub-structure tracking words extracted from definitions and their direct pointers to matching entries in secondary dictionaries.

---

## Prerequisites & Compilation
To compile and run this project locally, you will need a standard C compiler (such as `gcc`).

1. Clone the repository:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git)
   cd YOUR_REPOSITORY_NAME
2. Compile the source files together:
    ```bash
    gcc main.c fct.c -o dictionary_app
3. Run the compiled executable:
    ```bash
   ./dictionary_app
---
    
## How to Use & Program Workflow

Once you launch the program, the main menu dynamically updates based on your available data:

   **`Manual Entry (1)`** : Create new dictionaries by specifying the number of entries, words, and definitions. Files are automatically saved to disk.

  **`Dictionary Manipulation (2)`**: Load an existing dictionary file or manage an active one (search, add, modify, or delete entries, and view summaries).

  **`Cross-Linking (3)`**: Select two distinct dictionaries to analyze text definitions and build interactive term-to-term links.

  **`Display Links (4)`**: Inspect the relationships and cross-references generated between dictionaries.

  **`List Saved Files (5)`**: View all active dictionary files currently stored or loaded in the session.

  **`Exit (6)`**: Safely release all dynamically allocated memory and terminate the program.

---

## Technical skills & Concepts Demonstrated


  **Low-Level Memory Management**: Custom allocation (malloc) and recursive freeing algorithms (free) designed specifically to prevent memory leaks across deeply nested multi-level dynamic structures.

  **String Manipulation & Parsing**: Custom pointer arithmetic (liremot) for text tokenization, combined with case-insensitive comparisons (strcasecmp) and character validation filters (char_permis).

  **Relational Data Modeling**: Implementation of multi-level pointers to model complex lexical graphs and relational data structures entirely in standard C.

## Future Improvements / Roadmap

  [ ] Implement a graphical user interface (GUI) or web interface using a lightweight C framework or Python binding.

  [ ] Add support for export formats such as JSON or XML.

  [ ] Optimize search performance using balanced binary search trees (AVL/Red-Black trees) or hash tables instead of linear linked lists.

--- 

## Authors & Acknowledgments

  Developed collaboratively by MSD and AZS.

---
