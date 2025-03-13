#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../include/person.hpp"
// #include "../include/fifa.hpp"

// Forward declarations
// class Team;
// class NationalTeam;
// class ClubTeam;

class Player : public Person
{
private:
  int goals;
  double atk, def;
  std::string national_team, club_team, type;

  // Static vector to store all Player objects
  static std::vector<Player> all_players;

  // Static counter for the number of players
  static int players_count;

public:
  Player() : Person("NoName", 0) {
    this->salary = 0;
    this->type = "Unknown";
    this->national_team = "None";
    this->club_team = "None";
    this->goals = 0;
    this->atk = 0;
    this->def = 0;
  } // Default constructor

  Player(const std::string &name, int age);

  using Person::set_info; // Bring back base class methods

  void set_info(std::string title, std::string info); // national_team, club_team, type
  void set_info(std::string title, int num);          // goals
  void set_info(std::string title, double num);       // atk, def

  std::string get_type() const;
  std::string get_national_team() const;
  std::string get_club_team() const;
  int get_goals() const;
  double get_atk() const;
  double get_def() const;

  // Static function to load players from file
  static void LoadPlayersFromFile();

  // Operator overloading as member functions
  bool operator>(const Player &other) const;
  bool operator<(const Player &other) const;
  bool operator==(const Player &other) const;

  // Helper function to calculate strength based on player type
  double get_strength() const;

  // Static function to sort players using selection sort
  static void SortPlayers();

  void display_info() override;

  friend void rank_mode();
};

#endif