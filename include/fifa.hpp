#ifndef FIFA_HPP
#define FIFA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>
#include "../include/player.hpp"
#include "../include/coach.hpp"
#include "../include/national_team.hpp"
#include "../include/club_team.hpp"

// Forward declaration of NationalTeam
class Player;
class Coach;
class NationalTeam;
class ClubTeam;

using namespace std;

namespace Fifa {
  void remove_player_from_market(const std::string &player_name);
  void add_player_to_market(const std::string &player_name, int price);

  void write_player(const Player &player, const std::string &file_to_write = "../data/players.txt");
  void write_coach(const Coach &coach, const std::string &file_to_write = "../data/coaches.txt");
  void write_national_team(const NationalTeam &team, const std::string &file_to_write = "../data/national_teams.txt");
  void write_club_team(const ClubTeam &team, const std::string &file_to_write = "../data/club_teams.txt");
  
  void update_player(const Player& player);
  void update_coach(const Coach& coach);
  void update_national_team(const NationalTeam& team);
  void update_club_team(const ClubTeam& team);
  
  Player create_player_obj(const string& name, int age, const string& nationality, const string& type, double atk, double def);
  Coach create_coach_obj(const string& name, int age, const string& nationality, double tactics);
  Team* create_team_obj(const std::string& team_name, const std::string& team_type);

  Person* load_person(ifstream& file, const string& person_name);
  Player load_player(const string& player_name);
  Coach load_coach(const string& coach_name);
  Team* load_team_data(ifstream& file, const string& team_name);
  NationalTeam load_national_team_data(const string& national_team_name);
  ClubTeam load_club_team_data(const string& club_team_name);
  unique_ptr<Team> check_return_team_type(const string& team_name);

  template <typename T>
  T extractInfo(const string& line) {
    T info;
    istringstream iss(line);
    string label;
    iss >> label >> info;  // Extract label and value into the template variable
    return info;
  }

  template <typename T>
  T load_entity(ifstream& file, const string& name) {

    Person* person = load_person(file, name);
    
    if (!person) {
      cout << name << " not found" << endl;
      return T("", 0);
    }

    T entity(person->get_name(), person->get_age());
    entity.Person::set_info(person->get_nationality()); // for coach, both team and nationality are string so explicitly mentioning
    entity.set_info(person->get_salary());
    delete person;
    
    return entity;
  }

  template <typename T>
  T load_team_base_data(ifstream& file, const string& team_name) {
    
    Team* team = load_team_data(file, team_name);
    
    T entity(team->get_name());
  
    if (team) {
      // Set the coach
      entity.set_coach(team->get_coach());
  
      // Add squad players
      const Player* squad = team->get_squad();
      for (int i = 0; i < 11; i++) {
        entity.add_to_squad(squad[i], i);
      }
  
      // Add substitute players
      const std::vector<Player>& subs = team->get_sub();
      for (const Player& p : subs) {
        entity.add_to_sub(p);
      }
  
      // Free the dynamically allocated Team object
      delete team;
    } else {
      cout << team_name << " not found" << endl;
      return T("");
    }
    
    return entity;
  }

}

#endif