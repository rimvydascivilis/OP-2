#include "student_io.h"
#include "student.h"
#include "gen_stud_file.h"
#include "timer.h"
#include "student_splitting.h"

int main() {
    vector<Student> students;
    double programDuration = 0;
    Timer timer;

    char action = getActionFromInput();
    if (action == 'g'){
        gen_stud_file(getHomeworkCountFromInput());
        return 0;
    }
    if (action == 'f') {
        string fileName = getFileNameFromInput();

        timer.reset();
        addStudentsFromFile(students, fileName);
        timer.stop();

        programDuration += timer.getDuration();
        cout << "Studentu nuskaitymas is failo uztruko: " << timer.getDuration() << "s" << endl;
    } else {
        addStudentsFromSTDIN(students);
    }

    bool useAverage = getFinalGradeCalculationMethod();
    for (Student &student : students) {
        student.calculateFinalGrade(useAverage);
    }

    int method = selectStudentSplittingMethod();
    if (method == 'A') {
        timer.reset();
        sort(students.begin(), students.end(), compareFinalGradeAscending);
        timer.stop();
        cout << "Studentu rusiavimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
    
        timer.reset();
        vector<Student> failedStudents;
        vector<Student> passedStudents;
        splitStudents1(students, passedStudents, failedStudents);
        timer.stop();
        cout << "Studentu surinkimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
        
        timer.reset();
        writeResultsToFile(passedStudents, failedStudents, useAverage);
        timer.stop();
        programDuration += timer.getDuration();
    } else if(method == 'B') {
        timer.reset();
        sort(students.begin(), students.end(), compareFinalGradeDescending);
        timer.stop();
        cout << "Studentu rusiavimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
    
        timer.reset();
        vector<Student> failedStudents;
        splitStudents2(students, failedStudents);
        timer.stop();
        cout << "Studentu surinkimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
        
        timer.reset();
        writeResultsToFile(students, failedStudents, useAverage);
        timer.stop();
        programDuration += timer.getDuration();
    } else {
        timer.reset();
        sort(students.begin(), students.end(), compareFinalGradeDescending);
        timer.stop();
        cout << "Studentu rusiavimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
    
        timer.reset();
        vector<Student> failedStudents;
        vector<Student> passedStudents;
        splitStudents3(students, passedStudents, failedStudents);
        timer.stop();
        cout << "Studentu surinkimas uztruko: " << timer.getDuration() << "s" << endl;
        programDuration += timer.getDuration();
        
        timer.reset();
        writeResultsToFile(passedStudents, failedStudents, useAverage);
        timer.stop();
        programDuration += timer.getDuration();
    }
    
    cout << "Programos veikimo laikas (Be naudotojo ivesties laukimo laiko): " << programDuration << "s" << endl;
    return 0;
}
