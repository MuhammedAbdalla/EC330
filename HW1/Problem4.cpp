// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <iostream>
#include <fstream>
#include <string>

using std::string;

static int occurances = 0;

int StringSearch (string filename, string pattern){
  std::ifstream inputFile(filename);
  string line;
  while (std::getline(inputFile, line)) {
    if (line.size() > pattern.size()) {
      for (int i = 0; i < line.size()-pattern.size(); i++) {
        if (line.substr(i, pattern.size()) == pattern) {
          occurances++;
        }
      }
    }
  }
  inputFile.close(); // always close
  return occurances;
}

int main(int argc, char** argv){
  if (argc != 3) 
    return 1;
  string filename = string(argv[1]);
  string pattern = string(argv[2]);

  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) 
    return 1;
  std::cout << "# occurances for " << filename << ": " << StringSearch(filename,pattern);
  return 0;
}
