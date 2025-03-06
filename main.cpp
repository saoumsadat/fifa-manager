#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
// #include "team.hpp"
#include "include/national_team.hpp"
#include "include/player.hpp"
#include "include/coach.hpp"

using namespace std;

// vector<NationalTeam> teams;

template <typename T>
T extractInfo(const string& line) {
    T info;
    istringstream iss(line);
    string label;
    iss >> label >> info;  // Extract label and value into the template variable
    return info;
}

Person* load_person(ifstream& file, const string& person_name) {

  //finding if person exists
  string line;
  bool person_found = false;

  string person_nation;
  int person_age, person_salary;

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

  //getting info
  if (!(person_found)) {
    cout << "Person not found" << endl;
    return nullptr;
  } else {
    
    if (getline(file, line)) {  // Age: ..
      person_age = extractInfo<int>(line);
    }
    if (getline(file, line)) {  // Nationality: ..
      person_nation = extractInfo<string>(line);
    }
    if (getline(file, line)) {  // Salary: ..
      person_salary = extractInfo<int>(line);
    }

    Person* person = new Person(person_name, person_age);
    
    //setting info
    person->set_info(person_nation);
    person->set_info(person_salary);

    return person;
  }
}

Player load_player(const string& player_name) {

  ifstream file("data/players.txt");
  if (!file.is_open()) {
    cerr << "Error opening players file!" << endl;
    return Player("", 0);
  }
  
  Person* person = load_person(file, player_name);

  Player player("", 0); //Dummy player declared first

  if (person) {
    player = Player(person->get_name(), person->get_age());
    player.set_info(person->get_nationality()); //using parents getter, so 1 parameter
    player.set_info(person->get_salary());
    delete person;
  } else {
    cout << "Player not found" << endl;
    return Player("", 0);
  }
  
  //loading addition info
  string line;

  int price, goals;
  double atk, def;
  string national_team, club_team, type;

  //getting info
  if (getline(file, line)) {  // Extract "Type: ..."
    type = extractInfo<int>(line);
  }
  if (getline(file, line)) {  // Extract "NationalTeam: ..."
    national_team = extractInfo<string>(line);
  }
  if (getline(file, line)) {  // Extract "ClubTeam: ..."
    club_team = extractInfo<string>(line);
  }
  if (getline(file, line)) {  // Extract "Goals: ..."
    goals = extractInfo<int>(line);
  }
  if (getline(file, line)) {  // Extract "Attack: ..."
    atk = extractInfo<double>(line);
  }
  if (getline(file, line)) {  // Extract "Defense: ..."
    def = extractInfo<double>(line);
  }

  //setting info
  player.set_info("type", type);
  player.set_info("national_team", national_team);
  player.set_info("club_team", club_team);
  player.set_info("goals", goals);
  player.set_info("atk", atk);
  player.set_info("def", def);

  return player;
}

Coach load_coach(const string& coach_name) {

  ifstream file("data/coaches.txt");
  if (!file.is_open()) {
    cerr << "Error opening coaches file!" << endl;
    return Coach("", 0);
  }
  
  Person* person = load_person(file, coach_name);

  Coach coach("", 0); //Dummy coach declared first
  if (person) {
    coach = Coach(person->get_name(), person->get_age());
    coach.set_info(person->get_nationality()); //using parents getter
    coach.set_info(person->get_salary());
    delete person;
  } else {
    cout << "Coach not found" << endl;
    return Coach("", 0);
  }

  //loading additional info
  string line;

  string team;
  double tactics = 0;

  //getting info
  if (getline(file, line)) {  // Extract "Team: ..."
    team = extractInfo<string>(line);
  }
  if (getline(file, line)) {  // Extract "Tactics: ..."
    tactics = extractInfo<double>(line);
  }

  //setting info
  coach.set_info(team);
  coach.set_info(tactics);

  return coach;
}

NationalTeam load_team_data(const string& team_name) {
  
  ifstream file("data/national_teams.txt");
  if (!file.is_open()) {
    cerr << "Error opening national_teams file!" << endl;
    return NationalTeam("");
  }
  
  NationalTeam national_team("");

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
    return NationalTeam("");
  } else {
    //team found, create object
    national_team = NationalTeam(team_name);

    //set info
    if (getline(file, line)){
      int world_cup_won = extractInfo<int>(line);
      national_team.set_world_cup(world_cup_won);
    } 

    if (getline(file, line)) {
      string coach_name = extractInfo<string>(line);
      //create & set coach
      Coach loaded_coach = load_coach(coach_name);
      national_team.set_coach(loaded_coach);

    }
    
    if (getline(file, line)) {
      string squad_str = extractInfo<string>(line);
      stringstream ss(squad_str);
      string player_name;
      int i = 0; //fixed 11 players
      while (getline(ss, player_name, ',')) {
        Player squad_player = load_player(player_name);
        national_team.add_to_squad(squad_player, i);
      }
    }

    if (getline(file, line)) {
      string subs_str = extractInfo<string>(line);
      stringstream ss(subs_str);
      string player_name;
      while (getline(ss, player_name, ',')) {
        Player sub_player = load_player(player_name);
        national_team.add_to_sub(sub_player);
      }
    }

    if (getline(file, line)) {
      string res_str = extractInfo<string>(line);
      stringstream ss(res_str);
      string player_name;
      while (getline(ss, player_name, ',')) {
        Player sub_player = load_player(player_name);
        national_team.add_to_res(sub_player);
      }
      
    }
  }

  file.close();

  return national_team;
  
}

void coach_mode() {
  string team_name;
  cout << "\nEnter Team Name:" << endl;
  cin >> team_name;

  NationalTeam loaded_team = load_team_data(team_name);

  int choice;
  while (true) {
    cout << "\n1. Coach Details" << endl;
    cout << "2. Display Players" << endl;
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
      loaded_team.get_coach().display_info();
    } else if (choice == 2) {
      
    } else if (choice == 0) {
      break;
    } else {
      cout << "Invalid choice" << endl;
    }
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
