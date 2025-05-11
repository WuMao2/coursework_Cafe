#include <iostream>
#include <fstream>
#include <string>

class CUser {
  private:
    std::string username;
    std::string password;
    bool isLoggedIn;
    bool privilages;

    int points;

  public:
    CUser(std::string u, std::string p, bool s = false, bool priv = false);

    virtual ~CUser();

    virtual void loginFromFile(std::string u, std::string p);
    void logout();
    std::string getUsername() const;
    bool getLoggedIn() const;
    bool getPrivilages() const;
    int getPoints() const;
    void setPoints(int value);

    virtual void registerIntoFile(std::string u, std::string p);
};