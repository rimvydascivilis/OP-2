#include "MyLibV.h"

int main() {
    vector<Student> students;
    int studentCount = 0;

    AddStudents(students);
    printResults(students);
    
    return 0;
}

void AddStudents(vector<Student> &students) {
    char action = 't';
    do {
        Student newStudent;
        enterStudentData(newStudent);
        students.push_back(newStudent);

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
        while (student.homeworkGrades.size() == 0){
            int homeworkGrade;
            while (cin >> homeworkGrade) {
                if (homeworkGrade < 0 || homeworkGrade > 10) {
                    cout << "Pazymys turi buti nuo 0 iki 10, pakartokite: " << endl;
                    continue;
                }
                student.homeworkGrades.push_back(homeworkGrade);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if (student.homeworkGrades.size() == 0) {
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
    vector<int> homeworkGrades = student.homeworkGrades;

    double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0);
    student.finalGradeAverage = sum / homeworkGrades.size() * 0.4 + student.examGrade * 0.6;
    
    sort(homeworkGrades.begin(), homeworkGrades.end());
    int hCount = homeworkGrades.size();
    int l = homeworkGrades[hCount - hCount / 2 - 1];
    int r = homeworkGrades[hCount / 2];
    student.finalGradeMedian = (l + r) / 2 * 0.4 + student.examGrade * 0.6;
}

void generateGrades(Student &student) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> disGradeCount(1, 10);
    uniform_int_distribution<int> disGrades(0, 10);

    for (int i = 0; i < disGradeCount(gen); i++) {
        student.homeworkGrades.push_back(disGrades(gen));
    }
    student.examGrade = disGrades(gen);
}

void printResults(vector<Student> students) {
    cout << "Apskaiciuoti namu darbus vidurkiu spausk \"v\", mediana spausk \"m\": ";
    
    char action;
    cin >> action;

    bool useAverage = action == 'v' ? true : false;
    string finalGradeType = useAverage ? "Vid." : "Med.";

    cout << setw(15) << left << "Pavarde" << setw(15) << "Vardas" << setw(25) << "Galutinis (" + finalGradeType + ")" << endl;
    cout << string(55, '-') << endl;

    for(auto student : students) {
        printStudentData(student, useAverage);
    }
}

void printStudentData(Student student, bool useAverage) {
    double finalGrade = useAverage ? student.finalGradeAverage : student.finalGradeMedian;
    cout << setw(15) << student.surname << setw(15) << student.name << setprecision(2) << fixed << finalGrade << endl;
}