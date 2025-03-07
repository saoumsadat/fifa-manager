#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>
#include "../include/fifa.hpp"
#include "../include/market.hpp"

using namespace std;
using namespace Fifa;
using namespace Market;


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

void market_mode() {
  int choice;
  while (true) {
    cout << "\n1. List Available Players" << endl;
    cout << "2. Search Player by Name" << endl;
    cout << "3. Buy Player" << endl;
    cout << "4. Sell Player" << endl;
    cout << "0. Go Back" << endl;
    cin >> choice;

    if (choice == 0) break;
    if (choice == 1) {
      string player_name;
      cout << "Enter Player Name: ";
      cin >> player_name;
      
    }
  }
}


int main() {
  int option;
  while (true) {
    cout << "\n1. Enter Coach Mode" << endl;
    cout << "2. Enter Market" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
    cin >> option;
    
    if (option == 0) break;
    if (option == 1) coach_mode();
    if (option == 2) market_mode();
  }
  return 0;
}
