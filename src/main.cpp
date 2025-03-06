#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// #include "team.hpp"
#include "../include/national_team.hpp"
#include "../include/player.hpp"
#include "../include/coach.hpp"

using namespace std;

// vector<NationalTeam> teams;

template <typename T>
T extractInfo(const std::string& line) {
    T info;
    std::istringstream iss(line);
    std::string label;
    iss >> label >> info;  // Extract label and value into the template variable
    return info;
}

Person* load_person(ifstream& file, const string& person_name) {

  //finding if person exists
  string line;
  bool person_found = false;

  while (getline(file, line)) {
    if (line.find("Name:") != string::npos) {
      // Extract person name
      string current_person_name = extractInfo<string>(line);
      
      if (current_person_name == person_name) {
        person_found = true;
        break; // Person found, no need to check further
      }
    }
  }

  if (!(person_found)) {
    cout << "Person not found" << endl;
  } else {
    int person_age;
    if (getline(file, line)) {
      person_age = extractInfo<int>(line);
    }

    return new Person(person_name, person_age);
  }
}

Player load_player(const string& player_name) {

  ifstream file("../data/players.txt");
  if (!file.is_open()) {
    cerr << "Error opening file!" << endl;
    return;
  }
  
  Person* person = load_person(file, player_name);

  Player player("", 0); //Dummy player declared first
  if (person) {
    player = Player(person->get_name(), person->get_age());
    delete person;
  } else {
    cout << "Player not found" << endl;
    return;
  }
  
}

Coach load_coach(const string& coach_name) {

  ifstream file("../data/coaches.txt");
  if (!file.is_open()) {
    cerr << "Error opening file!" << endl;
    return;
  }
  
  Person* person = load_person(file, coach_name);

  Coach coach("", 0); //Dummy coach declared first
  if (person) {
    coach = Coach(person->get_name(), person->get_age());
    delete person;
  } else {
    cout << "Coach not found" << endl;
    return;
  }

  //loading additional info
  string line;

  string team;
  int tactics = 0;
  double salary = 0;

  //getting info
  if (getline(file, line)) {  // Extract "Team: ..."
      team = extractInfo<string>(line);
  }
  if (getline(file, line)) {  // Extract "Tactics: ..."
      tactics = extractInfo<int>(line);
  }

  //setting info
  coach.set_info(team);
  coach.set_info(tactics);
  coach.set_info(salary);

  return coach;
}

void load_team_data(const string& team_name) {
  ifstream file("../data/national_teams.txt");
  if (!file.is_open()) {
    cerr << "Error opening file!" << endl;
    return;
  }
  
  //finding if team exists
  string line;
  bool team_found = false;

  while (getline(file, line)) {
    if (line.find("Name:") != string::npos) {
      // Extract team name
      string current_team_name = extractInfo<string>(line);
      
      if (current_team_name == team_name) {
        team_found = true;
        break; // Team found, no need to check further
      }
    }
  }

  if (not(team_found)) {
    cout << "Team not found" << endl;
  } else {
    //team found, create object
    NationalTeam national_team(team_name);
    //set info
    while (getline(file, line)) {
      //set rank
      if (line.find("Rank:") != std::string::npos) {
        int rank = extractInfo<int>(line);
        national_team.set_rank(rank);

      } else if (line.find("WorldCup:") != std::string::npos){
        int world_cup_won = extractInfo<int>(line);
        national_team.set_world_cup(world_cup_won);

      } else  if (line.find("Coach:") != std::string::npos) {
        string coach_name = extractInfo<string>(line);

        //create & set coach
        Coach loaded_coach = load_coach(coach_name);
        national_team.set_coach(loaded_coach);

      } else if (line.find("Squad:") != std::string::npos) {
        std::vector<Player> squad_players;
        string squad_str = extractInfo<string>(line);
        std::stringstream ss(squad_str);
        std::string player_name;
        while (getline(ss, player_name, ',')) {
            squad_players.push_back(Player(player_name));
        }
      }
    }
  }

  file.close();
}

// void display_players(const NationalTeam& team) {
//     cout << "Squad: \n";
//     for (const auto& player : team.getSquad()) {
//         player.display_info();
//     }
//     cout << "Substitutes: \n";
//     for (const auto& player : team.getSubstitutes()) {
//         player.display_info();
//     }
//     cout << "Reserves: \n";
//     for (const auto& player : team.getReserves()) {
//         player.display_info();
//     }
// }

void coach_mode() {
  string team_name;
  cout << "\nEnter Team Name:" << endl;
  cin >> team_name;

  load_team_data(team_name);
  // int choice;
  // while (true) {
  //   cout << "\n1. Display Players" << endl;
  //   cout << "0. Exit" << endl;
  //   cout << "Enter choice: ";
  //   cin >> choice;
    
  //   if (choice == 0) break;
  //   if (teams.empty()) {
  //     cout << "No teams loaded!" << endl;
  //     continue;
  //   }
    
  //   NationalTeam& team = teams[0]; // Example: Select first team
    
  //   if (choice == 1) {
  //     display_players(team);
  //   } else {
  //     cout << "Invalid choice!" << endl;
  //   }
  // }
}

int main() {
    int option;
    while (true) {
        cout << "\n1. Enter Coach Mode" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> option;
        
        if (option == 0) break;
        if (option == 1) coach_mode();
    }
    return 0;
}
