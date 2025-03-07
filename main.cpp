#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>
#include "include/national_team.hpp"
#include "include/club_team.hpp"
#include "include/player.hpp"
#include "include/coach.hpp"
#include "include/fifa.hpp"

using namespace std;
using namespace Fifa;

// template <typename T>
// T extractInfo(const string& line) {
//   T info;
//   istringstream iss(line);
//   string label;
//   iss >> label >> info;  // Extract label and value into the template variable
//   return info;
// }


// Person* load_person(ifstream& file, const string& person_name) {
  
//   //finding if person exists
//   string line;
//   bool person_found = false;
  
//   string person_nation;
//   int person_age, person_salary;
  
//   while (getline(file, line)) {
//     if (line.find("Name:") != string::npos) {
//       // Extract person name
//       string current_person_name = extractInfo<string>(line);
      
//       if (current_person_name == person_name) {
//         person_found = true;
//         break; // Person found, no need to check further
//       }
//     }
//   }
  
//   //getting info
//   if (!(person_found)) {
//     cout << "Person not found" << endl;
//     return nullptr;
//   } 
  
//   if (getline(file, line)) {  // Age: ..
//     person_age = extractInfo<int>(line);
//   }
//   if (getline(file, line)) {  // Nationality: ..
//     person_nation = extractInfo<string>(line);
//   }
//   if (getline(file, line)) {  // Salary: ..
//     person_salary = extractInfo<int>(line);
//   }
  
//   Person* person = new Person(person_name, person_age);
  
//   //setting info
//   person->set_info(person_nation);
//   person->set_info(person_salary);
  
//   return person;
  
// }


// template <typename T>
// T load_entity(ifstream& file, const string& name) {

//   Person* person = load_person(file, name);

//   if (!person) {
//     cout << name << " not found" << endl;
//     return T("", 0);
//   }

//   T entity(person->get_name(), person->get_age());
//   entity.set_info(person->get_nationality()); // Using base class getters
//   entity.set_info(person->get_salary());
//   delete person;

//   return entity;
// }


// Player load_player(const string& player_name) {
  
//   ifstream file("data/players.txt");
//   if (!file.is_open()) {
//     cerr << "Error opening players file!" << endl;
//     return Player("", 0);
//   }
  
//   Player player = load_entity<Player>(file, player_name);
  
//   //loading addition info
//   string line;

//   int price, goals;
//   double atk, def;
//   string national_team, club_team, type;

//   //getting info
//   if (getline(file, line)) {  // Extract "Type: ..."
//     type = extractInfo<int>(line);
//   }
//   if (getline(file, line)) {  // Extract "NationalTeam: ..."
//     national_team = extractInfo<string>(line);
//   }
//   if (getline(file, line)) {  // Extract "ClubTeam: ..."
//     club_team = extractInfo<string>(line);
//   }
//   if (getline(file, line)) {  // Extract "Goals: ..."
//     goals = extractInfo<int>(line);
//   }
//   if (getline(file, line)) {  // Extract "Attack: ..."
//     atk = extractInfo<double>(line);
//   }
//   if (getline(file, line)) {  // Extract "Defense: ..."
//     def = extractInfo<double>(line);
//   }

//   //setting info
//   player.set_info("type", type);
//   player.set_info("national_team", national_team);
//   player.set_info("club_team", club_team);
//   player.set_info("goals", goals);
//   player.set_info("atk", atk);
//   player.set_info("def", def);

//   return player;
// }


// Coach load_coach(const string& coach_name) {

//   ifstream file("data/coaches.txt");
//   if (!file.is_open()) {
//     cerr << "Error opening coaches file!" << endl;
//     return Coach("", 0);
//   }
  
//   Coach coach = load_entity<Coach>(file, coach_name);

//   //loading additional info
//   string line;

//   string team;
//   double tactics = 0;

//   //getting info
//   if (getline(file, line)) {  // Extract "Team: ..."
//     team = extractInfo<string>(line);
//   }
//   if (getline(file, line)) {  // Extract "Tactics: ..."
//     tactics = extractInfo<double>(line);
//   }

//   //setting info
//   coach.set_info(team);
//   coach.set_info(tactics);

//   return coach;
// }


// Team* load_team_data(ifstream& file, const string& team_name) {

//   //finding if team exists
//   string line;
//   bool team_found = false;

//   while (getline(file, line)) {
//     if (line.find("Name:") != string::npos) {
//       // Extract team name
//       string current_team_name = extractInfo<string>(line);
      
//       if (current_team_name == team_name) {
//         team_found = true;
//         break; // Team found, no need to check further
//       }
//     }
//   }

//   if (!(team_found)) {
//     cout << "Team not found" << endl;
//     return nullptr;
//   }

//   //team found, create object
//   Team* team = new Team(team_name);

//   //getting & setting info
  
//   //coach
//   if (getline(file, line)) {
//     string coach_name = extractInfo<string>(line);
//     Coach loaded_coach = load_coach(coach_name);
//     team->set_coach(loaded_coach);
    
//   }
  
//   //squad
//   if (getline(file, line)) {
//     string squad_str = extractInfo<string>(line);
//     stringstream ss(squad_str);
//     string player_name;
//     int i = 0; //fixed 11 players
//     while (getline(ss, player_name, ',')) {
//       Player squad_player = load_player(player_name);
//       team->add_to_squad(squad_player, i);
//       i++;
//     }
//   }
  
//   //subs
//   if (getline(file, line)) {
//     string subs_str = extractInfo<string>(line);
//     stringstream ss(subs_str);
//     string player_name;
//     while (getline(ss, player_name, ',')) {
//       Player sub_player = load_player(player_name);
//       team->add_to_sub(sub_player);
//     }
//   }
  

//   return team;
  
// }


// template <typename T>
// T load_team_base_data(ifstream& file, const string& team_name) {
//   Team* team = load_team_data(file, team_name);

//   T entity("");

//   if (team) {
//     // Set the coach
//     entity.set_coach(team->get_coach());

//     // Add squad players
//     const Player* squad = team->get_squad();
//     for (int i = 0; i < 11; i++) {
//       entity.add_to_squad(squad[i], i);
//     }

//     // Add substitute players
//     const std::vector<Player>& subs = team->get_sub();
//     for (const Player& p : subs) {
//       entity.add_to_sub(p);
//     }

//     // Free the dynamically allocated Team object
//     delete team;
//   } else {
//     cout << team_name << " not found" << endl;
//     return T("");
//   }

//   return entity;
// }


// NationalTeam load_national_team_data(const string& national_team_name) {
  
//   ifstream file("data/national_teams.txt");
//   if (!file.is_open()) {
//     cerr << "Error opening national_teams file!" << endl;
//     return NationalTeam("");
//   }

//   NationalTeam national_team = load_team_base_data<NationalTeam>(file, national_team_name);

//   //loading additional info
//   string line;
  
//   //world_cup
//   if (getline(file, line)){
//     int world_cup_won = extractInfo<int>(line);
//     national_team.set_world_cup(world_cup_won);
//   } 

//   //res
//   if (getline(file, line)) {
//     string res_str = extractInfo<string>(line);
//     stringstream ss(res_str);
//     string player_name;
//     while (getline(ss, player_name, ',')) {
//       Player res_player = load_player(player_name);
//       national_team.add_to_res(res_player);
//     }
    
//   }  

//   file.close();

//   return national_team;
  
// }


// ClubTeam load_club_team_data(const string& club_team_name) {
//   ifstream file("data/club_teams.txt");
//   if (!file.is_open()) {
//     cerr << "Error opening club_teams file!" << endl;
//     return ClubTeam("");
//   }

//   ClubTeam club_team = load_team_base_data<ClubTeam>(file, club_team_name);

//   //loading additional info
//   string line;

//   // UCL titles
//   if (getline(file, line)) {
//     int ucl_won = extractInfo<int>(line);
//     club_team.set_ucl(ucl_won);
//   }

//   // Transfer list
//   if (getline(file, line)) {
//     string transfer_str = extractInfo<string>(line);
//     stringstream ss(transfer_str);
//     string player_name;
//     while (getline(ss, player_name, ',')) {
//       Player transfer_player = load_player(player_name);
//       club_team.add_to_transfer_list(transfer_player);
//     }
//   }

//   // Funds
//   if (getline(file, line)) {
//     double funds = extractInfo<double>(line);
//     club_team.set_funds(funds);
//   }

//   file.close();

//   return club_team;
// }


// // Function to check and return the team type
// std::unique_ptr<Team> check_return_team_type(const string& team_name) {
//   // Check club_teams.txt first
//   ifstream club_file("data/club_teams.txt");
//   if (club_file.is_open()) {
//     string line;
//     while (getline(club_file, line)) {
//       if (line.find("Name:") != string::npos) {
//         string current_team_name = extractInfo<string>(line);
//         if (current_team_name == team_name) {
//           // Team found in club_teams.txt
//           ClubTeam club_team = load_club_team_data(team_name);
//           club_file.close();
//           return std::make_unique<ClubTeam>(club_team); // Return as ClubTeam
//         }
//       }
//     }
//     club_file.close();
//   }

//   // Check national_teams.txt if not found in club_teams.txt
//   ifstream national_file("data/national_teams.txt");
//   if (national_file.is_open()) {
//     string line;
//     while (getline(national_file, line)) {
//       if (line.find("Name:") != string::npos) {
//         string current_team_name = extractInfo<string>(line);
//         if (current_team_name == team_name) {
//           // Team found in national_teams.txt
//           NationalTeam national_team = load_national_team_data(team_name);
//           national_file.close();
//           return std::make_unique<NationalTeam>(national_team); // Return as NationalTeam
//         }
//       }
//     }
//     national_file.close();
//   }

//   // Team not found in either file
//   cerr << "Team not found in any file!" << endl;
//   return nullptr; // Return nullptr
// }


void national_coach_mode(unique_ptr<Team>& team_ptr) {

  NationalTeam* national_team = dynamic_cast<NationalTeam*>(team_ptr.get());

  int choice;
  while (true) {
    cout << "\n1. National Coach Details" << endl;
    cout << "2. Display Players" << endl;
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
      national_team->get_coach().display_info();
    } else if (choice == 2) {

      const Player* squad = national_team->get_squad();
      for (int i = 0; i < 11; i++) {
        cout << squad[i].get_name() << endl;
      }

    } else if (choice == 0) {
      break;
    } else {
      cout << "Invalid choice" << endl;
    }
  }
}

void club_coach_mode(unique_ptr<Team>& team_ptr) {

  ClubTeam* club_team = dynamic_cast<ClubTeam*>(team_ptr.get());

  int choice;
  while (true) {
    cout << "\n1. Club Coach Details" << endl;
    cout << "2. Display Players" << endl;
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
      club_team->get_coach().display_info();
    } else if (choice == 2) {

      const Player* squad = club_team->get_squad();
      for (int i = 0; i < 11; i++) {
        cout << squad[i].get_name() << endl;
      }

    } else if (choice == 0) {
      break;
    } else {
      cout << "Invalid choice" << endl;
    }
  }
}


void coach_mode() {
  string team_name;
  cout << "\nEnter Team Name:" << endl;
  cin >> team_name;

  std::unique_ptr<Team> loaded_team = check_return_team_type(team_name);

  string loaded_team_cls = loaded_team->GetClassName();

  int choice;
  
  if (loaded_team_cls == "National") {
    national_coach_mode(loaded_team);
  } else if (loaded_team_cls == "Club") {
    club_coach_mode(loaded_team);
  }

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
