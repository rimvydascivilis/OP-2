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

struct Student {
    string name, surname;
    vector<float> homeworkGrades;
    int examGrade;
    double finalGrade;
};
void generateGrades(Student& student, int gradesToGenerate, mt19937 *gen = nullptr);
void calculateFinalGrade(Student& student, bool useAverage);

#endif