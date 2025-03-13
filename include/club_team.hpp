#ifndef CLUB_TEAM_HPP
#define CLUB_TEAM_HPP

#include <iostream>
#include "../include/team.hpp"
#include "../include/fifa.hpp"

// Forward declarations
// class Player;
// class Coach;

class ClubTeam : public Team
{
private:
  int ucl;
  std::vector<Player> transfer_list;
  int funds;

  // Static vector to store all ClubTeam objects
  static std::vector<ClubTeam> all_club_teams;

  // Static counter for the number of club teams
  static int club_teams_count;

public:
  // Constructor
  ClubTeam(std::string team_name);

  // check
  bool check_player_exist(const Player &player) const;

  // Setters
  void set_ucl(int new_ucl_count);
  void add_to_transfer_list(Player p);
  void set_funds(int new_funds);
  bool remove_from_transfer_list(Player p);

  // Function to remove a player from squad or substitutes
  bool remove_player(const Player &player);

  // from display
  std::string GetClassName() const override;

  // Getters
  int get_ucl() const;
  std::vector<Player> get_transfer_list() const;
  int get_funds() const;

  // Operator overloading as member functions
  bool operator>(const ClubTeam &other) const;
  bool operator<(const ClubTeam &other) const;
  bool operator==(const ClubTeam &other) const;

  // Static function to sort club teams using selection sort
  static void SortClubTeams();

  friend void rank_mode();

  // Static function to load club teams from file
  static void LoadClubTeamsFromFile();
};

#endif