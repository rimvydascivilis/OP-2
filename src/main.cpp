#include "student_io.h"
#include "student.h"
#include "gen_stud_file.h"
#include "timer.h"
#include "student_splitting.h"

int main() {
    Student s("Jan", "Kowalski", {1, 2, 3, 4, 5}, 6);
    s.calculateFinalGrade(true);

    cout << "Originalus 's'       " << s << endl;
    Student s1(s);
    cout << "Nukopijuotas is 's': " << s1 << endl;
    cout << endl << endl;
    Student s2(move(s));
    cout << "Orginalus 's':  " << s << endl;
    cout << "Perkeltas 's2': " << s2 << endl;

    return 0;
}
