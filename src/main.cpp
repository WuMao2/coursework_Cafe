#include "CUser.hpp"
#include <iostream>
#include <string>


int main() {
  CUser user("Unknown Customer", "");

  std::cout << "Login test" << std::endl;
  std::string username, password;
  std::cin >> username >> password;
  user.loginFromFile(username, password);

  std::cout << user.getPoints() << std::endl;
  user.setPoints(25);
  return 0;
}
