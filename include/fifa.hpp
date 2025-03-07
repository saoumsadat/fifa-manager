#ifndef FIFA_HPP
#define FIFA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>
#include "national_team.hpp"
#include "club_team.hpp"
#include "player.hpp"
#include "coach.hpp"

using namespace std;

namespace Fifa {

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
    entity.set_info(person->get_nationality()); // Using base class getters
    entity.set_info(person->get_salary());
    delete person;

    return entity;
  }

  template <typename T>
  T load_team_base_data(ifstream& file, const string& team_name) {
    Team* team = load_team_data(file, team_name);
  
    T entity("");
  
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