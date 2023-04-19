#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include "student.h"

int selectStudentSplittingMethod();
void splitStudents1(vector<Student> &students, vector<Student> &passedStudents, vector<Student> &failedStudents);
void splitStudents1(list<Student> &students, list<Student> &passedStudents, list<Student> &failedStudents);
void splitStudents1(deque<Student> &students, deque<Student> &passedStudents, deque<Student> &failedStudents);
void splitStudents2(vector<Student> &students, vector<Student> &failedStudents);
void splitStudents2(list<Student> &students, list<Student> &failedStudents);
void splitStudents2(deque<Student> &students, deque<Student> &failedStudents);