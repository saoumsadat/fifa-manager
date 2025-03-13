#ifndef NATIONAL_TEAM_HPP
#define NATIONAL_TEAM_HPP

#include <iostream>
#include "../include/team.hpp"
#include "../include/fifa.hpp"

// Forward declarations
// class Player;
// class Coach;

class NationalTeam : public Team
{
private:
  int world_cup;
  std::vector<Player> reserve;
  static int national_teams_count;
  static std::vector<NationalTeam> all_national_teams;

public:
  static void LoadNationalTeamsFromFile();

  NationalTeam(std::string team_name);

  void set_world_cup(int new_world_cup_count);
  void add_to_res(Player p);

  int get_world_cup() const;
  const std::vector<Player> &get_reserve() const;

  // Operator overloading as member functions
  bool operator>(const NationalTeam &other) const;
  bool operator<(const NationalTeam &other) const;
  bool operator==(const NationalTeam &other) const;

  // Static function to sort national teams using selection sort
  static void SortNationalTeams();

  // overriding getclassname from display
  std::string GetClassName() const override;

  friend void rank_mode();
};

#endif