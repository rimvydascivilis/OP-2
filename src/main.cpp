#include "student_io.h"
#include "student.h"
#include "gen_stud_file.h"
#include "timer.h"
#include "student_splitting.h"

int main() {
    Student s("Jan", "Kowalski", {1, 2, 3, 4, 5}, 6);
    s.calculateFinalGrade(true);
    cout << "Sukurtas" << endl;
    cout << s << endl;
    Student s1(s);
    cout << "Nukopijuotas S1:" << endl;
    cout << s1 << endl;
    cout << "S:" << endl;
    cout << s << endl;
    Student s2{move(s)};
    cout << "Move:" << endl;
    cout << s2 << endl;
    cout << "S:" << endl;
    cout << s << endl;

    return 0;
}
