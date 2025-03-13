#ifndef COACH_HPP
#define COACH_HPP

#include "../include/person.hpp"


// Forward declarations
// class Team;
// class NationalTeam;
// class ClubTeam;

class Coach : public Person {
private:
  int age;
  double tactics;
  std::string team;

  // Static vector to store all Coach objects
  static std::vector<Coach> all_coaches;

  // Static counter for the number of coaches
  static int coaches_count;

public:
  Coach() : Person("NotAssigned", 0) {}  // Default constructor
  Coach(const std::string& name, int age);

  // Bring the set_info(int) method from the Person class into scope
  using Person::set_info;

  void set_info(std::string team);
  void set_info(double tactics);

  std::string get_team() const;
  double get_tactics() const;

  // Static function to load coaches from file
  static void LoadCoachesFromFile();

  // Operator overloading as member functions
  bool operator>(const Coach& other) const;
  bool operator<(const Coach& other) const;
  bool operator==(const Coach& other) const;

  // Static function to sort coaches using selection sort
  static void SortCoaches();

  void display_info() override;
  friend void register_mode();
  friend void rank_mode();
};

#endif