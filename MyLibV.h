#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::setprecision;
using std::fixed;
using std::copy;
using std::sort;
using std::streamsize;
using std::numeric_limits;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::accumulate;
using std::vector;

struct Student {
    string name, surname;
    vector<int> homeworkGrades;
    int examGrade;
    double finalGradeAverage = 0, finalGradeMedian = 0;
};

void AddStudents(vector<Student> &students);
void enterStudentData(Student &student);
void generateGrades(Student &student);
void calculateFinalGrade(Student &student);
void printResults(vector<Student> students);
void printStudentData(Student student, bool useAverage);