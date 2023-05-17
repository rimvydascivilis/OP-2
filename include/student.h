#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <numeric>
#include <list>
#include <deque>
#include <iomanip>

using std::vector;
using std::string;
using std::sort;
using std::accumulate;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::list;
using std::deque;
using std::ostream;
using std::istream;
using std::stringstream;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;
using std::move;

class Student {
private:
    string name, surname;
    vector<float> homeworkGrades;
    int examGrade;
    double finalGrade;

    void calculateFinalGradeAverage();
    void calculateFinalGradeMedian();

public:
    Student(): name(""), surname(""), homeworkGrades(), examGrade(0), finalGrade(0.0) {}
    Student(string name, string surname) : name(name), surname(surname), homeworkGrades(), examGrade(0), finalGrade(0.0) {}
    Student(string name, string surname, vector<float> homeworkGrades, int examGrade) : name(name), surname(surname), homeworkGrades(homeworkGrades), examGrade(examGrade), finalGrade(0.0) {}
    Student(const Student &s) : name(s.name), surname(s.surname), homeworkGrades(s.homeworkGrades), examGrade(s.examGrade), finalGrade(s.finalGrade) {}
    Student(Student &&s);
    ~Student() { homeworkGrades.clear(); }

    inline string getName() const { return name; }
    inline string getSurname() const { return surname; }
    inline vector<float> getHomeworkGrades() const { return homeworkGrades; }
    inline int getExamGrade() const { return examGrade; }
    inline double getFinalGrade() const { return finalGrade; }
    inline int getHomeworkCount() const { return homeworkGrades.size(); };
    
    void generateGrades(int gradesToGenerate, mt19937 *gen = nullptr);
    void calculateFinalGrade(bool useAverage);

    friend ostream& operator<<(ostream &os, const Student &s);
    friend istream& operator>>(istream &is, Student &s);
    Student &operator=(const Student &s);
    Student &operator=(Student &&s);
};

bool compareFinalGradeAscending(const Student &a, const Student &b);
bool compareFinalGradeDescending(const Student &a, const Student &b);

#endif