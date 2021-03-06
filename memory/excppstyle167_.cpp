/* 
  what are the three forms of operator new
*/

#include "study.hpp"
#include <stdlib.h>

struct T {

  // you call them static as a reminder.  They're static anyway.
  T() { SHOW(); }
  T(const T&) { SHOW(); }
  ~T() { SHOW(); }

  // plain new
  static void* 
  operator new(std::size_t s) throw(std::bad_alloc) 
  {
    void* mem = malloc(s);
    SHOW() << mem << "\n";
    if (s == 0)
      throw std::bad_alloc();
    return mem;
  }

  static void 
  operator delete(void* p) {
    free(p);
    SHOW() << p << "\n";
  }

  // placement
  static void*
  operator new(std::size_t s, void* p) throw() {
    SHOW() << s << " " << p << "\n";
    return p;
  }

  // nothrow
  static void* 
  operator new(std::size_t s, const std::nothrow_t&) throw() 
  {
    void* mem = malloc(s);
    SHOW() << mem << "\n";
    return mem;
  }
};

struct U { };

int main() 
{
  T* t = new T;

  delete t;

  void* mem = malloc(sizeof(T));
  
  T* placed_t = new(mem) T;
  delete placed_t;
  


  U* u = new U;
  delete u;
}


