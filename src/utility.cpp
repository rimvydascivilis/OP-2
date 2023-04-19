#include "utility.h"

int selectStudentSplittingMethod() {
    char method = 0;
    while (method != 'A' && method != 'B') {
        cout << "Pasirinkite studentu surinkimo metoda:" << std::endl;
        cout << "A pop_back()" << std::endl;
        cout << "B remove ir copy" << std::endl;
        cout << "Metodas: ";
        cin >> method;
    }
    return method;
}

void splitStudents1(vector<Student> &students, vector<Student> &passedStudents, vector<Student> &failedStudents) {
    while (students.size()) {
        Student student = students.back();
        students.pop_back();
        if (student.finalGrade < 5) {
            failedStudents.push_back(student);
        } else {
            passedStudents.push_back(student);
        }
    }
}

void splitStudents1(list<Student> &students, list<Student> &passedStudents, list<Student> &failedStudents) {
    while (students.size()) {
        Student student = students.back();
        students.pop_back();
        if (student.finalGrade < 5) {
            failedStudents.push_back(student);
        } else {
            passedStudents.push_back(student);
        }
    }
}

void splitStudents1(deque<Student> &students, deque<Student> &passedStudents, deque<Student> &failedStudents) {
    while (students.size()) {
        Student student = students.back();
        students.pop_back();
        if (student.finalGrade < 5) {
            failedStudents.push_back(student);
        } else {
            passedStudents.push_back(student);
        }
    }
}

void splitStudents2(vector<Student> &students, vector<Student> &failedStudents) {
    auto it = students.begin();
    while (it != students.end()) {
        if (it->finalGrade < 5) {
            failedStudents.push_back(*it);
            it = students.erase(it);
        }else{
            it++;
        }
    }
}

void splitStudents2(list<Student> &students, list<Student> &failedStudents) {
    auto it = students.begin();
    while (it != students.end()) {
        if (it->finalGrade < 5) {
            failedStudents.push_back(*it);
            it = students.erase(it);
        }else{
            it++;
        }
    }
}

void splitStudents2(deque<Student> &students, deque<Student> &failedStudents) {
    auto it = students.begin();
    while (it != students.end()) {
        if (it->finalGrade < 5) {
            failedStudents.push_back(*it);
            it = students.erase(it);
        }else{
            it++;
        }
    }
}
