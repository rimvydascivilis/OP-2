#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>

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
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::stof;

struct Student {
    string name, surname;
    vector<float> homeworkGrades;
    int examGrade;
    double finalGradeAverage = 0, finalGradeMedian = 0;
};

void addStudents(vector<Student> &students);
void addStudentsFromFile(string fileName, vector<Student> &students);
void addStudentsFromSTDIN(vector<Student> &students);
void enterStudentData(Student &student);
void generateGrades(Student &student);
void calculateFinalGrade(Student &student);
string getResults(vector<Student> students);
string getFormatedStudentData(Student student, bool useAverage);