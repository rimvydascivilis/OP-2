#ifndef GEN_STUD_FILE_H
#define GEN_STUD_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <filesystem>

#include "student.h"
#include "timer.h"

using std::ofstream;
using std::to_string;
using std::stringstream;
using std::setw;
using std::endl;
using std::left;
using std::fixed;
using std::setprecision;
using std::random_device;

void gen_stud_file(int homeworkCount);
void createFileWithStudents(string filename, int fileSize, int homeworkCount);

#endif