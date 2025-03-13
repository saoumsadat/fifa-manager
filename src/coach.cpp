#include <iostream>
#include "../include/fifa.hpp"
#include "../include/coach.hpp"

// Initialize the static vector
std::vector<Coach> Coach::all_coaches;

// Initialize the static counter
int Coach::coaches_count = 0;

// Operator overloading as member functions
bool Coach::operator>(const Coach &other) const
{
  return this->tactics > other.tactics;
}

bool Coach::operator<(const Coach &other) const
{
  return this->tactics < other.tactics;
}

bool Coach::operator==(const Coach &other) const
{
  return this->tactics == other.tactics;
}

// Static function to sort coaches using selection sort
void Coach::SortCoaches()
{
  for (size_t i = 0; i < all_coaches.size() - 1; ++i)
  {
    size_t max_index = i;
    for (size_t j = i + 1; j < all_coaches.size(); ++j)
    {
      if (all_coaches[j] > all_coaches[max_index])
      {
        max_index = j;
      }
    }
    if (max_index != i)
    {
      std::swap(all_coaches[i], all_coaches[max_index]);
    }
  }
}

void Coach::LoadCoachesFromFile()
{
  std::string filename = "../data/coaches.txt";
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.find("Name: ") != std::string::npos)
    {
      // Extract the coach name
      std::string name = Fifa::extractInfo<std::string>(line);

      // Use Fifa::load_coach() to create a Coach object
      Coach coach = Fifa::load_coach(name);

      // Add the coach to the static vector
      all_coaches.push_back(coach);

      // Increment the counter
      coaches_count++;
    }
  }

  file.close();
}

Coach::Coach(const std::string &name, int age) : Person(name, age)
{
  this->team = "None";
}

void Coach::set_info(std::string team)
{
  this->team = team;
}

void Coach::set_info(double tactics)
{
  this->tactics = tactics;
}

std::string Coach::get_team() const
{
  return this->team;
}
double Coach::get_tactics() const
{
  return this->tactics;
}

void Coach::display_info()
{
  Person::display_info(); // Call base class method first
  std::cout << "Team: " << this->team << std::endl;
  std::cout << "Tactical Power: " << this->tactics << std::endl;
}