#include <iostream>
#include "../include/fifa.hpp"

using namespace std;

void Fifa::remove_player_from_market(const std::string &player_name)
{
  std::ifstream infile("../data/market.txt");
  std::ofstream tempfile("../data/temp_market.txt");

  if (!infile.is_open() || !tempfile.is_open())
  {
    std::cerr << "Error opening market file!" << std::endl;
    return;
  }

  std::string line;
  bool skip = false;

  while (std::getline(infile, line))
  {
    if (line.find("Name: ") == 0)
    {
      std::string name = Fifa::extractInfo<std::string>(line);
      if (name == player_name)
      {
        skip = true; // Skip the player's data
        continue;
      }
      else
      {
        skip = false;
      }
    }

    if (!skip)
    {
      tempfile << line << "\n"; // Write the line to the temp file
    }
  }

  infile.close();
  tempfile.close();

  // Replace the original file with the temp file
  std::remove("../data/market.txt");
  std::rename("../data/temp_market.txt", "../data/market.txt");
}

void Fifa::add_player_to_market(const std::string &player_name, int price)
{
  ofstream file("../data/market.txt", ios::app);
  if (!file.is_open())
  {
    cerr << "Error opening market file to add player!" << endl;
    return;
  }

  file << "\nName: " << player_name << endl;
  file << "Price: " << price << endl;

  file.close();
}

Player Fifa::create_player_obj(const string &name, int age, const string &nationality, const string &type, double atk, double def)
{
  // Create the Player object
  Player player(name, age);
  player.set_info(nationality);
  player.set_info("type", type);
  player.set_info("atk", atk);
  player.set_info("def", def);

  return player;
}

Coach Fifa::create_coach_obj(const string &name, int age, const string &nationality, const string &team, double tactics)
{

  // Create the Coach object
  Coach coach(name, age);
  coach.Person::set_info(nationality); // explicitly mentioned as team is also a string
  coach.set_info(team);
  coach.set_info(tactics);

  return coach;
}

Team *Fifa::create_team_obj(const std::string &team_name, const std::string &team_type)
{
  Team *team = nullptr;

  if (team_type == "national_team")
  {
    team = new NationalTeam(team_name);
  }
  else if (team_type == "club_team")
  {
    team = new ClubTeam(team_name);
  }
  else
  {
    throw std::invalid_argument("Invalid team type");
  }

  // Set dummy coach
  team->set_coach(Coach());

  // Add dummy squad players
  for (int i = 0; i < 11; ++i)
  {
    team->add_to_squad(Player(), i);
  }

  return team;
}

void Fifa::write_player(const Player &player, const std::string &file_to_write)
{
  std::ofstream outfile(file_to_write, std::ios::app);
  if (outfile.is_open())
  {
    outfile << "\nName: " << player.get_name() << "\n";
    outfile << "Age: " << player.get_age() << "\n";
    outfile << "Nationality: " << player.get_nationality() << "\n";
    outfile << "Salary: " << player.get_salary() << "\n";
    outfile << "Type: " << player.get_type() << "\n";
    outfile << "NationalTeam: " << player.get_national_team() << "\n";
    outfile << "ClubTeam: " << player.get_club_team() << "\n";
    outfile << "Goals: " << player.get_goals() << "\n";
    outfile << "Attack: " << player.get_atk() << "\n";
    outfile << "Defense: " << player.get_def() << "\n";
    outfile.close();
  }
  else
  {
    std::cerr << "Unable to open players.txt for writing.\n";
  }
}

void Fifa::write_coach(const Coach &coach, const std::string &file_to_write)
{
  std::ofstream outfile(file_to_write, std::ios::app);
  if (outfile.is_open())
  {
    outfile << "\nName: " << coach.get_name() << "\n";
    outfile << "Age: " << coach.get_age() << "\n";
    outfile << "Nationality: " << coach.get_nationality() << "\n";
    outfile << "Salary: " << coach.get_salary() << "\n";
    outfile << "Team: " << coach.get_team() << "\n";
    outfile << "Tactics: " << coach.get_tactics() << "\n";
    outfile.close();
  }
  else
  {
    std::cerr << "Unable to open coaches.txt for writing.\n";
  }
}

void Fifa::write_national_team(const NationalTeam &team, const std::string &file_to_write)
{
  std::ofstream outfile(file_to_write, std::ios::app);
  if (outfile.is_open())
  {
    outfile << "\nName: " << team.get_name() << "\n";
    outfile << "Coach: " << team.get_coach().get_name() << "\n";
    outfile << "Squad: ";
    for (int i = 0; i < 11; ++i)
    {
      outfile << team.get_squad()[i].get_name();
      if (i < 10)
        outfile << ",";
    }
    outfile << "\nSubstitutes: ";
    for (size_t i = 0; i < team.get_sub().size(); ++i)
    {
      outfile << team.get_sub()[i].get_name();
      if (i < team.get_sub().size() - 1)
        outfile << ",";
    }
    outfile << "\nWorldCup: " << team.get_world_cup() << "\n";
    outfile << "Reserves: ";
    for (size_t i = 0; i < team.get_reserve().size(); ++i)
    {
      outfile << team.get_reserve()[i].get_name();
      if (i < team.get_reserve().size() - 1)
        outfile << ",";
    }
    outfile << "\n";
    outfile.close();
  }
  else
  {
    std::cerr << "Unable to open national_teams.txt for writing.\n";
  }
}

void Fifa::write_club_team(const ClubTeam &team, const std::string &file_to_write)
{
  std::ofstream outfile(file_to_write, std::ios::app);
  if (outfile.is_open())
  {
    outfile << "\nName: " << team.get_name() << "\n";
    outfile << "Coach: " << team.get_coach().get_name() << "\n";
    outfile << "Squad: ";
    for (int i = 0; i < 11; ++i)
    {
      outfile << team.get_squad()[i].get_name();
      if (i < 10)
        outfile << ",";
    }
    outfile << "\nSubstitutes: ";
    for (size_t i = 0; i < team.get_sub().size(); ++i)
    {
      outfile << team.get_sub()[i].get_name();
      if (i < team.get_sub().size() - 1)
        outfile << ",";
    }
    outfile << "\nUCL: " << team.get_ucl() << "\n";
    outfile << "TransferList: ";
    for (size_t i = 0; i < team.get_transfer_list().size(); ++i)
    {
      outfile << team.get_transfer_list()[i].get_name();
      if (i < team.get_transfer_list().size() - 1)
        outfile << ",";
    }
    outfile << "\nFunds: " << team.get_funds() << "\n";
    outfile.close();
  }
  else
  {
    std::cerr << "Unable to open club_teams.txt for writing.\n";
  }
}

void Fifa::update_player(const Player &player)
{
  std::ifstream infile("../data/players.txt");
  std::ofstream tempfile("../data/temp_players.txt");

  if (!infile.is_open() || !tempfile.is_open())
  {
    std::cerr << "Error opening files!" << std::endl;
    return;
  }

  std::string line;
  bool skip = false;

  while (std::getline(infile, line))
  {
    if (line.find("Name: ") == 0)
    {
      std::string name = Fifa::extractInfo<std::string>(line); // Use extractInfo
      if (name == player.get_name())
      {
        skip = true; // Skip the next lines for this player
      }
      else
      {
        skip = false;
      }
    }

    if (!skip)
    {
      tempfile << line << "\n"; // Write the line to the temp file
    }
  }

  infile.close();
  tempfile.close();

  // Replace the original file with the temp file
  std::remove("../data/players.txt");
  std::rename("../data/temp_players.txt", "../data/players.txt");
  Fifa::write_player(player); // Write the updated player
}

void Fifa::update_coach(const Coach &coach)
{
  std::ifstream infile("../data/coaches.txt");
  std::ofstream tempfile("../data/temp_coaches.txt");

  if (!infile.is_open() || !tempfile.is_open())
  {
    std::cerr << "Error opening files!" << std::endl;
    return;
  }

  std::string line;
  bool skip = false;

  while (std::getline(infile, line))
  {
    if (line.find("Name: ") == 0)
    {
      std::string name = Fifa::extractInfo<std::string>(line); // Use extractInfo
      if (name == coach.get_name())
      {
        skip = true; // Skip the next lines for this coach
      }
      else
      {
        skip = false;
      }
    }

    if (!skip)
    {
      tempfile << line << "\n"; // Write the line to the temp file
    }
  }

  infile.close();
  tempfile.close();

  // Replace the original file with the temp file
  std::remove("../data/coaches.txt");
  std::rename("../data/temp_coaches.txt", "../data/coaches.txt");
  Fifa::write_coach(coach); // Write the updated coach
}

void Fifa::update_national_team(const NationalTeam &team)
{
  std::ifstream infile("../data/national_teams.txt");
  std::ofstream tempfile("../data/temp_national_teams.txt");

  if (!infile.is_open() || !tempfile.is_open())
  {
    std::cerr << "Error opening files!" << std::endl;
    return;
  }

  std::string line;
  bool skip = false;

  while (std::getline(infile, line))
  {
    if (line.find("Name: ") == 0)
    {
      std::string name = Fifa::extractInfo<std::string>(line); // Use extractInfo
      if (name == team.get_name())
      {
        skip = true; // Skip the next lines for this team
      }
      else
      {
        skip = false;
      }
    }

    if (!skip)
    {
      tempfile << line << "\n"; // Write the line to the temp file
    }
  }

  infile.close();
  tempfile.close();

  // Replace the original file with the temp file
  std::remove("../data/national_teams.txt");
  std::rename("../data/temp_national_teams.txt", "../data/national_teams.txt");
  Fifa::write_national_team(team); // Write the updated team
}

void Fifa::update_club_team(const ClubTeam &team)
{
  std::ifstream infile("../data/club_teams.txt");
  std::ofstream tempfile("../data/temp_club_teams.txt");

  if (!infile.is_open() || !tempfile.is_open())
  {
    std::cerr << "Error opening files!" << std::endl;
    return;
  }

  std::string line;
  bool skip = false;

  while (std::getline(infile, line))
  {
    if (line.find("Name: ") == 0)
    {
      std::string name = Fifa::extractInfo<std::string>(line); // Use extractInfo
      if (name == team.get_name())
      {
        skip = true; // Skip the next lines for this team
      }
      else
      {
        skip = false;
      }
    }

    if (!skip)
    {
      tempfile << line << "\n"; // Write the line to the temp file
    }
  }

  infile.close();
  tempfile.close();

  // Replace the original file with the temp file
  std::remove("../data/club_teams.txt");
  std::rename("../data/temp_club_teams.txt", "../data/club_teams.txt");
  Fifa::write_club_team(team); // Write the updated team
}

Person *Fifa::load_person(ifstream &file, const string &person_name)
{

  // finding if person exists
  string line;
  bool person_found = false;

  string person_nationality;
  int person_age, person_salary;

  while (getline(file, line))
  {
    if (line.find("Name:") != string::npos)
    {
      // Extract person name
      string current_person_name = extractInfo<string>(line);

      if (current_person_name == person_name)
      {
        person_found = true;
        break; // Person found, no need to check further
      }
    }
  }

  // getting info
  if (!(person_found))
  {
    cout << "Person not found" << endl;
    return nullptr;
  }

  if (getline(file, line))
  { // Age: ..
    person_age = extractInfo<int>(line);
  }
  if (getline(file, line))
  { // Nationality: ..
    person_nationality = extractInfo<string>(line);
  }
  if (getline(file, line))
  { // Salary: ..
    person_salary = extractInfo<int>(line);
  }

  Person *person = new Person(person_name, person_age);

  // setting info
  person->set_info(person_nationality);
  person->set_info(person_salary);

  return person;
}

Player Fifa::load_player(const string &player_name)
{

  ifstream file("../data/players.txt");
  if (!file.is_open())
  {
    cerr << "Error opening players file!" << endl;
    return Player("", 0);
  }

  Player player = load_entity<Player>(file, player_name);

  // loading addition info
  string line;

  int price, goals;
  double atk, def;
  string national_team, club_team, type;

  // getting info
  if (getline(file, line))
  { // Extract "Type: ..."
    type = extractInfo<string>(line);
  }
  if (getline(file, line))
  { // Extract "NationalTeam: ..."
    national_team = extractInfo<string>(line);
  }
  if (getline(file, line))
  { // Extract "ClubTeam: ..."
    club_team = extractInfo<string>(line);
  }
  if (getline(file, line))
  { // Extract "Goals: ..."
    goals = extractInfo<int>(line);
  }
  if (getline(file, line))
  { // Extract "Attack: ..."
    atk = extractInfo<double>(line);
  }
  if (getline(file, line))
  { // Extract "Defense: ..."
    def = extractInfo<double>(line);
  }

  // setting info
  player.set_info("type", type);
  player.set_info("national_team", national_team);
  player.set_info("club_team", club_team);
  player.set_info("goals", goals);
  player.set_info("atk", atk);
  player.set_info("def", def);

  return player;
}

Coach Fifa::load_coach(const string &coach_name)
{

  ifstream file("../data/coaches.txt");
  if (!file.is_open())
  {
    cerr << "Error opening coaches file!" << endl;
    return Coach("", 0);
  }

  Coach coach = load_entity<Coach>(file, coach_name);

  // loading additional info
  string line;

  string team;
  double tactics = 0;

  // getting info
  if (getline(file, line))
  { // Extract "Team: ..."
    team = extractInfo<string>(line);
  }
  if (getline(file, line))
  { // Extract "Tactics: ..."
    tactics = extractInfo<double>(line);
  }

  // setting info
  coach.set_info(team);
  coach.set_info(tactics);

  return coach;
}

Team *Fifa::load_team_data(ifstream &file, const string &team_name)
{

  // finding if team exists
  string line;
  bool team_found = false;

  while (getline(file, line))
  {
    if (line.find("Name:") != string::npos)
    {
      // Extract team name
      string current_team_name = extractInfo<string>(line);

      if (current_team_name == team_name)
      {
        team_found = true;
        break; // Team found, no need to check further
      }
    }
  }

  if (!(team_found))
  {
    cout << "Team not found" << endl;
    return nullptr;
  }

  // team found, create object
  Team *team = new Team(team_name);

  // getting & setting info

  // coach
  if (getline(file, line))
  {
    string coach_name = extractInfo<string>(line);
    if (coach_name == "NotAssigned")
    {
      team->set_coach(Coach());
    }
    else
    {
      Coach loaded_coach = Fifa::load_coach(coach_name);
      team->set_coach(loaded_coach);
    }
  }

  // squad
  if (getline(file, line))
  {
    string squad_str = extractInfo<string>(line);
    stringstream ss(squad_str);
    string player_name;
    int i = 0; // fixed 11 players
    while (getline(ss, player_name, ','))
    {
      if (player_name == "NoName")
      {
        team->add_to_squad(Player(), i);
      }
      else
      {
        Player squad_player = Fifa::load_player(player_name);
        team->add_to_squad(squad_player, i);
      }
      i++;
    }
  }

  // subs
  if (getline(file, line))
  {
    string subs_str = extractInfo<string>(line);
    stringstream ss(subs_str);
    string player_name;
    while (getline(ss, player_name, ','))
    {
      Player sub_player = Fifa::load_player(player_name);
      team->add_to_sub(sub_player);
    }
  }

  return team;
}

NationalTeam Fifa::load_national_team_data(const string &national_team_name)
{

  ifstream file("../data/national_teams.txt");
  if (!file.is_open())
  {
    cerr << "Error opening national_teams file!" << endl;
    return NationalTeam("");
  }

  NationalTeam national_team = load_team_base_data<NationalTeam>(file, national_team_name);

  // loading additional info
  string line;

  // world_cup
  if (getline(file, line))
  {
    int world_cup_won = extractInfo<int>(line);
    national_team.set_world_cup(world_cup_won);
  }

  // res
  if (getline(file, line))
  {
    string res_str = extractInfo<string>(line);
    stringstream ss(res_str);
    string player_name;
    while (getline(ss, player_name, ','))
    {
      Player res_player = Fifa::load_player(player_name);
      national_team.add_to_res(res_player);
    }
  }

  file.close();

  return national_team;
}

ClubTeam Fifa::load_club_team_data(const string &club_team_name)
{
  ifstream file("../data/club_teams.txt");
  if (!file.is_open())
  {
    cerr << "Error opening club_teams file!" << endl;
    return ClubTeam("");
  }

  ClubTeam club_team = load_team_base_data<ClubTeam>(file, club_team_name);

  // loading additional info
  string line;

  // UCL titles
  if (getline(file, line))
  {
    int ucl_won = extractInfo<int>(line);
    club_team.set_ucl(ucl_won);
  }

  // Transfer list
  if (getline(file, line))
  {
    string transfer_str = extractInfo<string>(line);
    stringstream ss(transfer_str);
    string player_name;
    while (getline(ss, player_name, ','))
    {
      Player transfer_player = Fifa::load_player(player_name);
      club_team.add_to_transfer_list(transfer_player);
    }
  }

  // Funds
  if (getline(file, line))
  {
    double funds = extractInfo<double>(line);
    club_team.set_funds(funds);
  }

  file.close();
  return club_team;
}

std::unique_ptr<Team> Fifa::check_return_team_type(const string &team_name)
{
  // Check club_teams.txt first
  ifstream club_file("../data/club_teams.txt");
  if (club_file.is_open())
  {
    string line;
    while (getline(club_file, line))
    {
      if (line.find("Name:") != string::npos)
      {
        string current_team_name = extractInfo<string>(line);
        if (current_team_name == team_name)
        {
          // Team found in club_teams.txt
          ClubTeam club_team = Fifa::load_club_team_data(team_name);
          club_file.close();
          return std::make_unique<ClubTeam>(club_team); // Return as ClubTeam
        }
      }
    }
    club_file.close();
  }

  // Check national_teams.txt if not found in club_teams.txt
  ifstream national_file("../data/national_teams.txt");
  if (national_file.is_open())
  {
    string line;
    while (getline(national_file, line))
    {
      if (line.find("Name:") != string::npos)
      {
        string current_team_name = extractInfo<string>(line);
        if (current_team_name == team_name)
        {
          // Team found in national_teams.txt
          NationalTeam national_team = Fifa::load_national_team_data(team_name);
          national_file.close();
          return std::make_unique<NationalTeam>(national_team); // Return as NationalTeam
        }
      }
    }
    national_file.close();
  }

  // Team not found in either file
  cerr << "Team not found in any file!" << endl;
  return nullptr; // Return nullptr
}
