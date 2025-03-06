#include "../include/person.hpp"

Person::Person(std::string name, int age) : name(name), age(age) {}

std::string Person::get_name() {
  return this->name;
}

int Person::get_age() {
  return this->age;
}

void Person::display_info() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Age: " << age << std::endl;
}



