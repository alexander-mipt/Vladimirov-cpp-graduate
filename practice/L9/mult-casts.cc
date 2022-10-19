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


#define DIAMOND 1  
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

struct OutputFile {
  uint64_t c{};
  OutputFile(int c) : c{c} {}
  virtual ~OutputFile() {}
};

#ifdef DIAMOND
struct IOFile : public Filler, public InputFile, public OutputFile {
  uint64_t d{};
  void filler() override { std::cout << "  " << std::endl; }
  IOFile(int d) : InputFile(d * 2), OutputFile(d * 3), d{d} {}
};
#endif

int main() {
#ifdef DIAMOND
	InputFile *dp = new InputFile{5};
	Filler *bp = dp;
	$(dp);
	$(bp);
#else
  IOFile *piof = new IOFile{5};
  std::cout << std::hex << "piof = " << piof << ": " << std::dec;
  std::cout << piof->d << std::endl;

  // OutputFile *pof = static_cast<OutputFile *>(piof);
  OutputFile *pof = piof;
  std::cout << std::hex << "pof = " << pof << ": " << std::dec;
  std::cout << pof->c << std::endl;

  InputFile *pif = static_cast<InputFile *>(piof);
  std::cout << std::hex << "pif = " << pif << ": " << std::dec;
  std::cout << pif->b << std::endl;

  piof = static_cast<IOFile *>(pif);
  std::cout << std::hex << "piof = " << piof << ": " << std::dec;
  std::cout << piof->d << std::endl;

  piof = static_cast<IOFile *>(pof);
  std::cout << std::hex << "piof = " << piof << ": " << std::dec;
  std::cout << piof->d << std::endl;
#endif
}
