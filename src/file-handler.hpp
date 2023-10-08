#pragma once
#include <fstream>
namespace FileRoutine {
class FileHandler {
  // public fileds!
public:
  std::string filePath;
  // default constructor and destructor are being used for now
  FileHandler();
  ~FileHandler();
  // private fields
private:
#define LIMIT 26
  int size;
  char fileChars[LIMIT];
  int fileFreq[];
};

void writeFile(std::string, char *, int);
/*FUNCTION PROTOTYPING*/
} // namespace FileRoutine
