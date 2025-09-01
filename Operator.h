#pragma once
#include<string>
using namespace std;
class Operator {
private:
    int operatorID;
    std::string name;
    std::string password;
    std::string email;

public:
    Operator(std::string name, std::string password, std::string email)
        : name(name), password(password), email(email) {
        static int id = 1;
        operatorID = id++;
    }

    int GetOperatorID() const { return operatorID; }
    std::string GetName() const { return name; }
    std::string GetPassword() const { return password; }
    std::string GetEmail() const { return email; }

    bool Authenticate(std::string email, std::string password) const {
        return this->email == email && this->password == password;
    }

  
};
