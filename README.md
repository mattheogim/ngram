# untitled1 - Trial and Error Log

## 1. hello.c not included in project target
- IDE showed "this file does not belong to any project target" warning
- **Cause:** `hello.c` was not registered in `CMakeLists.txt`
- **Fix:** Added the following to `CMakeLists.txt`
  ```cmake
  set(CMAKE_C_STANDARD 11)
  add_executable(hello hello.c)
  ```

## 2. Compiling C vs C++
- C++ uses `g++`, but C requires `gcc`
  ```bash
  gcc hello.c -o hello    # Compile C
  g++ main.cpp -o main    # Compile C++
  ```

## 3. Redirecting output to a file
- Use the `>` operator to save program output to a file
  ```bash
  ./hello > output.txt    # Overwrite
  ./hello >> output.txt   # Append
  ```