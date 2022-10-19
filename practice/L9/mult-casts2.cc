//-----------------------------------------------------------------------------
//
// Source code for MIPT ILab
// Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
//  Static casts with statically calculated offsets
//
//----------------------------------------------------------------------------

#include <iostream>
#include <cstdint>


#define $(x) do { std::cout << std::hex << #x << " = " << x << std::endl; } while(0) 

struct Filler {
  uint64_t x{};
  uint64_t y{};
  uint64_t z{};
  uint64_t zz{};
  virtual void filler() {};
  virtual ~Filler() {}
};

struct InputFile {
  uint64_t b{};
  InputFile(int b) : b{b} {}
  virtual ~InputFile() {}
};

int main() {
	InputFile *dp = new InputFile{5};
	Filler *bp = dp;
	$(dp);
	$(bp);
}
