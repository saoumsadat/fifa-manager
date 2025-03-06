#include "../include/person.hpp"

Person::Person(std::string name, int age) : name(name), age(age) {
  this->salary = 50;
}

std::string Person::get_name() {
  return this->name;
}

std::string Person::get_nationality() {
  return this->nationality;
}

int Person::get_age() {
  return this->age;
}

int Person::get_salary() {
  return this->salary;
}

void Person::set_info(int salary) {
  this->salary = salary;
}

void Person::set_info(std::string nationality) {
  this->nationality = nationality;
}

void Person::display_info() {
  std::cout << "\nName: " << name << std::endl;
  std::cout << "Age: " << age << std::endl;
}



