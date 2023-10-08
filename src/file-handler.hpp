#pragma once
#include <fstream>
class FileRoutine {
  // public fileds!
public:
  FileRoutine();
  FileRoutine(FileRoutine &&) = default;
  ~FileRoutine();
  // private fields
private:
};

inline FileRoutine::FileRoutine() {}

inline FileRoutine::~FileRoutine() {}
