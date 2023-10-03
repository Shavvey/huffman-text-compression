#pragma once
#include <fstream>
class FileRoutine {
public:
  FileRoutine();
  FileRoutine(FileRoutine &&) = default;
  FileRoutine(const FileRoutine &) = default;
  FileRoutine &operator=(FileRoutine &&) = default;
  FileRoutine &operator=(const FileRoutine &) = default;
  ~FileRoutine();

private:
};

inline FileRoutine::FileRoutine() {}

inline FileRoutine::~FileRoutine() {}
