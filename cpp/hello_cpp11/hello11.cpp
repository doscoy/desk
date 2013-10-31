
// clang++ -std=c++11 -stdlib=libc++ hello11.cpp

#include <array>
#include <iostream>
#include <algorithm>


int main()
{

  std::array<char, 5> hello = {'H','E','L','L','O'};
  std::for_each(
      hello.begin(),
      hello.end(),
      [](char c){ std::cout << c; }
  );
  std::cout << std::endl;
  return 0;
}
 
