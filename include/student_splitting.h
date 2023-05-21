#ifndef STUDENT_SPLITTING_H
#define STUDENT_SPLITTING_H

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include "student.h"
#include "Vector.h"

int selectStudentSplittingMethod();
void splitStudents1(Vector<Student> &students, Vector<Student> &passedStudents, Vector<Student> &failedStudents);
void splitStudents1(vector<Student> &students, vector<Student> &passedStudents, vector<Student> &failedStudents);
void splitStudents1(list<Student> &students, list<Student> &passedStudents, list<Student> &failedStudents);
void splitStudents1(deque<Student> &students, deque<Student> &passedStudents, deque<Student> &failedStudents);
void splitStudents2(Vector<Student> &students, Vector<Student> &failedStudents);
void splitStudents2(vector<Student> &students, vector<Student> &failedStudents);
void splitStudents2(list<Student> &students, list<Student> &failedStudents);
void splitStudents2(deque<Student> &students, deque<Student> &failedStudents);
void splitStudents3(vector<Student> &students, vector<Student> &passedStudents, vector<Student> &failedStudents);
void splitStudents3(list<Student> &students, list<Student> &passedStudents, list<Student> &failedStudents);
void splitStudents3(deque<Student> &students, deque<Student> &passedStudents, deque<Student> &failedStudents);

#endif