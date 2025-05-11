#include "CUser.hpp"

CUser::CUser(std::string u, std::string p, bool s, bool priv)
        : username(u), password(p), isLoggedIn(s), privilages(priv) {}

CUser::~CUser() {
    if (isLoggedIn) {
        std::ifstream inFile("users.txt");
        std::ofstream tempFile("temp.txt");
        
        if (inFile.is_open() && tempFile.is_open()) {
            std::string line;
            bool found = false;
            
            while (std::getline(inFile, line)) {
                size_t firstSpace = line.find(' ');
                size_t secondSpace = line.find(' ', firstSpace + 1);
                
                std::string fileUsername = line.substr(0, firstSpace);
                std::string filePassword = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
                
                if (fileUsername == username && filePassword == password) {
                    // Write updated user information
                    tempFile << username << " " << password << " " << points << std::endl;
                    found = true;
                } else {
                    // Copy the line as is
                    tempFile << line << std::endl;
                }
            }
            
            inFile.close();
            tempFile.close();
            
            // Remove the original file and rename the temp file
            std::remove("users.txt");
            std::rename("temp.txt", "users.txt");
        } else {
            std::cerr << "Unable to open files for updating" << std::endl;
        }
    }
}

void CUser::loginFromFile(std::string u, std::string p) {
    std::ifstream file("users.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Find positions of spaces
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            size_t thirdSpace = line.find(' ', secondSpace + 1);

            // Extract username and password
            std::string fileUsername = line.substr(0, firstSpace);
            std::string filePassword = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            int filePoints = std::stoi(line.substr(secondSpace + 1, thirdSpace - secondSpace - 1));

            if (fileUsername == u && filePassword == p) {
                username = u;
                password = p;
                isLoggedIn = true;
                points = filePoints;
                std::cout << "Login successful!" << std::endl;
                break;
            }
        }
        if (!isLoggedIn) {
            std::cout << "Login failed!" << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

void CUser::logout() {
  username = "Unknown Customer";
  password = "";
  isLoggedIn = false;
  privilages = false;
  std::cout << "Logged out successfully!" << std::endl;
}

std::string CUser::getUsername() const {
    return username;
}

bool CUser::getLoggedIn() const {
    return isLoggedIn;
}

bool CUser::getPrivilages() const {
    return privilages;
}

int CUser::getPoints() const {
    return points;
}

void CUser::setPoints(int value) {
  points = value;
}

void CUser::registerIntoFile(std::string u, std::string p) {
  std::ofstream file("users.txt", std::ios::app);
  if (file.is_open()) {
    file << u << " " << p << "" << 0 << std::endl;
    file.close();
    std::cout << "User registered successfully!" << std::endl;
  } else {
    std :: cerr << "Unable to open file";
  }
}

