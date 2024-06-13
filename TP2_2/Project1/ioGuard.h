#ifndef IO_GUARD
#define IO_GUARD

#include <ios>

class iofmtguard {
public:
  iofmtguard(std::basic_ios< char >& s);
  ~iofmtguard();
private:
  std::basic_ios< char >& s_;
  char fill_;
  std::basic_ios< char >::fmtflags fmt_;
};

#endif