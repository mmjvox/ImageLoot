#include <fstream>
#include <iostream>
#include <sstream>
#include "lz4.h"
using namespace std;

u_int64_t  nInputSize      = 0;
u_int64_t  nCompressedSize = 0;

void  compress()
{
  std::ifstream  inFile;
  inFile.open("./vvv2.mp4");
  std::stringstream  strStream;
  strStream << inFile.rdbuf();

  std::string  str = strStream.str();
  nInputSize = (u_int64_t)str.length();
// cout << "size of input " << std::numeric_limits<int>::max() << " " << nInputSize << " " << (std::numeric_limits<int>::max() > nInputSize) << endl;
  u_int64_t  max_dst_size = LZ4_compressBound(nInputSize);
// cout << "max_dst_size " << max_dst_size << endl;

  // compress szSource into pchCompressed
  char *pchCompressed = new char[nInputSize];
  nCompressedSize = LZ4_compress_default((const char *)(str.c_str()), pchCompressed, nInputSize, max_dst_size);
// cout << "pchCompressed " << pchCompressed << endl;

  // write pachCompressed to binary lz4.dat
  ofstream  outBinaryFile("lz4.dat", ofstream::binary);
  outBinaryFile << nInputSize << endl;
  outBinaryFile << nCompressedSize << endl;
  outBinaryFile.write(pchCompressed, nCompressedSize);
  outBinaryFile.close();
  delete[] pchCompressed;
  pchCompressed = 0;
}

void  decomp()
{
  ifstream  infCompressedBinaryFile("lz4.dat", ifstream::binary);
  string    line;

  getline(infCompressedBinaryFile, line);
  cout << "nInputSize " << line << endl;
  nInputSize = stoi(line);

  if (nInputSize == 0)
  {
    throw (nInputSize);
  }

  infCompressedBinaryFile.ignore(0, '\n');

  getline(infCompressedBinaryFile, line);
  cout << "nCompressedSize " << line << endl;
  nCompressedSize = stoi(line);

  if (nCompressedSize == 0)
  {
    throw (nCompressedSize);
  }

  infCompressedBinaryFile.ignore(0, '\n');

  u_int64_t  start = sizeof(nInputSize) + sizeof(nCompressedSize) + 2;

  // Get compressed file size for buffer
  infCompressedBinaryFile.seekg(start, infCompressedBinaryFile.end);
  u_int64_t  nCompressedInputSize = infCompressedBinaryFile.tellg();
  cout << "nCompressedInputSize " << nCompressedInputSize << endl;
  infCompressedBinaryFile.clear();
  infCompressedBinaryFile.seekg(start, ios::beg);

  // Read file into buffer
  char *pchCompressedInput = new char[nCompressedInputSize];
  infCompressedBinaryFile.read(pchCompressedInput, nCompressedSize);
  infCompressedBinaryFile.close();
  cout << " ccc " << start << endl;

  // Decompress buffer
  char *pchDeCompressed = new char[nInputSize]; // (nCompressedInputSize *2) +8
  LZ4_decompress_safe(pchCompressedInput, pchDeCompressed, nCompressedSize, nInputSize);
// cout << "pchDeCompressed " << pchDeCompressed << endl;
  delete[] pchCompressedInput;
  pchCompressedInput = 0;

  // write decompressed pachUnCompressed to
  ofstream  outFile("lz4.DeCompressed");
  outFile.write(pchDeCompressed, nInputSize);
  outFile.close();

  delete[] pchDeCompressed;
  pchDeCompressed = 0;
}

int  main()
{
  compress();
  try
  {
    decomp();
  }
  catch (...)
  {
  }
  cout << "Hello World!" << endl;

  return 0;
}
