#include "../include/person.hpp"

Person::Person(std::string name, int age) : name(name), age(age) {}

void Person::display_info() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Age: " << age << std::endl;
}



