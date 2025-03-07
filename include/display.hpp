#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>

class Display {
public:
  virtual std::string GetClassName() const = 0;
};

#endif