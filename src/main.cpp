#include <iostream>
#include "../include/person.hpp"
#include "../include/player.hpp"

int main() {
  Player p1("Ronaldo", 34, "Striker");
  p1.display_info();

  p1.update_info("team", "Real Madrid");
  p1.update_info(59.99);
  p1.display_info();
  return 0;
}