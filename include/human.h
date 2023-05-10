#ifndef HUMAN_H
#define HUMAN_H

#include <string>

using std::string;

class Human {
private:
    string name, surname;
protected:
    inline void setName(string name) { this->name = name; }
    inline void setSurname(string surname) { this->surname = surname; }
public:
    Human() : name(""), surname("") {}
    Human(string name, string surname) : name(name), surname(surname) {}

    inline string getName() const { return name; }
    inline string getSurname() const { return surname; }

    virtual ~Human() = default;
    virtual void sayHello() = 0;
};

#endif