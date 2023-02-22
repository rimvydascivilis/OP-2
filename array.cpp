#include "MyLibA.h"

int main() {
    Student *students = nullptr;
    int studentCount = 0;

    AddStudents(students, studentCount);
    printResults(students, studentCount);

    if (students != nullptr) {
        delete[] students;
        students = nullptr;
    }

    return 0;
}

void AddStudents(Student *&students, int &studentCount) {
    char action = 't';
    do {
        Student *newStudents = new Student[studentCount + 1];
        enterStudentData(newStudents[studentCount]);
        copy(students, students + studentCount, newStudents);

        studentCount++;
        if (students != nullptr) delete[] students;
        students = newStudents;

        cout << "Baigti darba spausk \"b\", testi spausk bet kuri kita klavisa: ";
        cin >> action;
    } while(action != 'b' && action != 'B');
}

void enterStudentData(Student &student) {
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> student.name >> student.surname;
    
    cout << "Generuoti pazymius spausk \"g\", ivesti pazymius spausk \"i\": ";
    char action;
    cin >> action;

    if (action == 'g' || action == 'G') {
        generateGrades(student);
    } else{
        cout << "Iveskite studento namu darbu pazymius, norint baigti iveskite raide:" << endl;
        while (student.homeworkGradeCount == 0){
            int homeworkGrade;
            while (cin >> homeworkGrade) {
                if (homeworkGrade < 0 || homeworkGrade > 10) {
                    cout << "Pazymys turi buti nuo 0 iki 10, pakartokite: " << endl;
                    continue;
                }

                int *newHomeworkGrades = new int[student.homeworkGradeCount + 1];
                copy(student.homeworkGrades, student.homeworkGrades + student.homeworkGradeCount, newHomeworkGrades);
                newHomeworkGrades[student.homeworkGradeCount] = homeworkGrade;
                
                student.homeworkGradeCount++;
                if (student.homeworkGrades != nullptr) delete[] student.homeworkGrades;
                student.homeworkGrades = newHomeworkGrades;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if (student.homeworkGradeCount == 0) {
                cout << "Neivedete nei vieno pazymio, pakartokite: " << endl;
            }
        }

        cout << "Iveskite studento egzamino rezultata: ";
        while (1){
            cin >> student.examGrade;
            if (!cin || student.examGrade < 0 || student.examGrade > 10) {
                cout << "Pazymys turi buti nuo 0 iki 10, pakartokite: " << endl;
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            break;
        }
    }
    calculateFinalGrade(student);
}

void calculateFinalGrade(Student &student) {
    int homeworkGrades[student.homeworkGradeCount];
    copy(student.homeworkGrades, student.homeworkGrades + student.homeworkGradeCount, homeworkGrades);

    double sum = accumulate(homeworkGrades, homeworkGrades + student.homeworkGradeCount, 0);
    student.finalGradeAverage = sum / student.homeworkGradeCount * 0.4 + student.examGrade * 0.6;
    
    sort(homeworkGrades, homeworkGrades + student.homeworkGradeCount);
    int l = homeworkGrades[student.homeworkGradeCount - student.homeworkGradeCount / 2 - 1];
    int r = homeworkGrades[student.homeworkGradeCount / 2];
    student.finalGradeMedian = (l + r) / 2 * 0.4 + student.examGrade * 0.6;
}

void generateGrades(Student &student) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> disGradeCount(1, 10);
    uniform_int_distribution<int> disGrades(0, 10);

    student.homeworkGradeCount = disGradeCount(gen);
    student.homeworkGrades = new int[student.homeworkGradeCount];

    for (int i = 0; i < student.homeworkGradeCount; i++) {
        student.homeworkGrades[i] = disGrades(gen);
    }

    student.examGrade = disGrades(gen);
}

void printResults(Student *students, int studentCount) {
    cout << "Apskaiciuoti namu darbus vidurkiu spausk \"v\", mediana spausk \"m\": ";
    
    char action;
    cin >> action;

    bool useAverage = action == 'v' ? true : false;
    string finalGradeType = useAverage ? "Vid." : "Med.";

    cout << setw(15) << left << "Pavarde" << setw(15) << "Vardas" << setw(25) << "Galutinis (" + finalGradeType + ")" << endl;
    cout << string(55, '-') << endl;

    for (int i = 0; i < studentCount; i++) {
        printStudentData(students[i], useAverage);
    }
}

void printStudentData(Student &student, bool useAverage) {
    double finalGrade = useAverage ? student.finalGradeAverage : student.finalGradeMedian;
    cout << setw(15) << student.surname << setw(15) << student.name << setprecision(2) << fixed << finalGrade << endl;

    if (student.homeworkGrades != nullptr) {
        delete[] student.homeworkGrades;
        student.homeworkGrades = nullptr;
    }
}