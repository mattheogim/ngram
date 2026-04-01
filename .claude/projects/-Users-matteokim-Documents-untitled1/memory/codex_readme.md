# Codex README

## Purpose

- This file stores Codex-specific project notes that should not modify Claude memory files.

## Current workflow notes

- The first exported CSV result file for this workflow should use the filename `step01_result.csv`.

## Project notes mirrored from README.md

### 1. hello.c was not included in a project target

- The IDE showed the warning `this file does not belong to any project target`.
- Cause: `hello.c` was not registered in `CMakeLists.txt`.
- Fix:

```cmake
set(CMAKE_C_STANDARD 11)
add_executable(hello hello.c)
```

### 2. C compilation method

- Use `gcc` for C and `g++` for C++.

```bash
gcc hello.c -o hello
g++ main.cpp -o main
```

### 3. Redirecting output to a file

- Use `>` to overwrite and `>>` to append.

```bash
./hello > output.txt
./hello >> output.txt
```

### 4. Codex memory structure was created

- Added a Codex-specific memory index:
  - [`CODEX_MEMORY.md`](/Users/matteokim/Documents/untitled1/.claude/projects/-Users-matteokim-Documents-untitled1/memory/CODEX_MEMORY.md)
- Added Codex-specific notes files:
  - [`codex_user_language.md`](/Users/matteokim/Documents/untitled1/.claude/projects/-Users-matteokim-Documents-untitled1/memory/codex_user_language.md)
  - [`codex_session_notes.md`](/Users/matteokim/Documents/untitled1/.claude/projects/-Users-matteokim-Documents-untitled1/memory/codex_session_notes.md)
  - [`codex_readme.md`](/Users/matteokim/Documents/untitled1/.claude/projects/-Users-matteokim-Documents-untitled1/memory/codex_readme.md)
- This structure was created without modifying Claude's original `MEMORY.md`.

### 5. Codex workflow rule was saved

- For this workflow, the first exported CSV result file should use the filename `step01_result.csv`.

### 6. Google Ngram download tooling was prepared

- Added a helper script:
  - [`scripts/google_ngram_fetch.py`](/Users/matteokim/Documents/untitled1/scripts/google_ngram_fetch.py)
- Added a local note file:
  - [`data/google-ngram/README.md`](/Users/matteokim/Documents/untitled1/data/google-ngram/README.md)
- Downloaded official Google Ngram metadata files:
  - [`data/google-ngram/eng-us/1-ngrams_exports.html`](/Users/matteokim/Documents/untitled1/data/google-ngram/eng-us/1-ngrams_exports.html)
  - [`data/google-ngram/eng-us/totalcounts-1`](/Users/matteokim/Documents/untitled1/data/google-ngram/eng-us/totalcounts-1)
- A sample shard was downloaded temporarily to inspect the format; the main takeaway was that the full dataset is large.

### 7. English word list dataset was added

- Downloaded the public `dwyl/english-words` word list into the workspace.
- Original source file:
  - [`data/dwyl-english-words/words_alpha.txt`](/Users/matteokim/Documents/untitled1/data/dwyl-english-words/words_alpha.txt)
- Generated CSV output:
  - [`data/dwyl-english-words/step01_result.csv`](/Users/matteokim/Documents/untitled1/data/dwyl-english-words/step01_result.csv)
- Result size:
  - `370,105` words

### 8. CSV integrity was checked

- Verified that the CSV header is `word`.
- Verified that every data row has exactly one column.
- Verified that the CSV payload matches the original TXT file exactly.
- No malformed sample rows were found during validation.

## Reference

- Source summary mirrored from [`README.md`](/Users/matteokim/Documents/untitled1/README.md).
