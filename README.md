# untitled1 - 시행착오 기록

## 1. hello.c가 프로젝트 타겟에 포함되지 않음
- IDE에서 "this file does not belong to any project target" 경고 발생
- **원인:** `CMakeLists.txt`에 `hello.c`가 등록되지 않았음
- **해결:** `CMakeLists.txt`에 아래 내용 추가
  ```cmake
  set(CMAKE_C_STANDARD 11)
  add_executable(hello hello.c)
  ```

## 2. C 컴파일 방법
- C++은 `g++`을 사용하지만, C는 `gcc`를 사용해야 함
  ```bash
  gcc hello.c -o hello    # C 컴파일
  g++ main.cpp -o main    # C++ 컴파일
  ```

## 3. 출력을 파일로 저장 (리다이렉션)
- `>` 연산자를 사용하면 프로그램 출력을 파일로 저장할 수 있음
  ```bash
  ./hello > output.txt    # 덮어쓰기
  ./hello >> output.txt   # 이어쓰기 (append)
  ```