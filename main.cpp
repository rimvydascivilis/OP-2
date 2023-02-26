#include "MyLib.h"

int main() {
    vector<Student> students;
    string results;

    addStudents(students);
    for (Student &student : students) {
        calculateFinalGrade(student);
    }
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.surname < b.surname; });
    
    results = getResults(students);
    cout << results;

    ofstream file("rezultatai.txt");
    file << results;
    file.close();
    
    return 0;
}

void addStudents(vector<Student> &students) {
    cout << "Ivesti studentus is failo spausk \"f\", is klaviaturos spausk \"k\": ";
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (action == 'f' || action == 'F') {
        string fileName;
        cout << "Iveskite failo pavadinima: ";
        cin >> fileName;
        addStudentsFromFile(fileName, students);
    } else {
        addStudentsFromSTDIN(students);
    }
}

void addStudentsFromFile(string fileName, vector<Student> &students) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Nepavyko atidaryti failo" << endl;
        exit(1);
    }
    cout << "Nuskaitomi studentai is failo..." << endl;

    int currentLine = 1;
    string line;

    getline(file, line); // Skip first line
    while (getline(file, line)) {
        currentLine++;
        Student newStudent;
        stringstream ss(line);
        ss >> newStudent.name >> newStudent.surname;
        string grade;
        while (ss >> grade) {
            int commaPos = grade.find(",");
            if (commaPos != string::npos) {
                grade.replace(commaPos, 1, ".");
            }
            grade.erase(remove_if(grade.begin(), grade.end(), [](char c) { return !isdigit(c) && !(c == '.'); }), grade.end());
            try {
                float gradeFloat = stof(grade);
                if (gradeFloat < 0 || gradeFloat > 10) {
                    cout << "Pazymys turi buti nuo 0 iki 10, pazymys praleidziamas (" << currentLine <<  "eil.)" << endl;
                    continue;
                }
                newStudent.homeworkGrades.push_back(gradeFloat);
            } catch (const std::invalid_argument& ia) {
                cout << "Nepavyko konvertuoti pazymio i skaiciu, pazymys praleidziamas (" << currentLine <<  "eil.)" << endl;
            }
        }
        if (newStudent.homeworkGrades.size() < 2) {
            cout << "Nepavyko nuskaityti pazymiu, studentas praleidziamas (" << currentLine <<  "eil.)" << endl;
            continue;
        }

        newStudent.examGrade = newStudent.homeworkGrades.back();
        newStudent.homeworkGrades.pop_back();
        students.push_back(newStudent);
    }
    file.close();
    cout << "Studentai nuskaityti is failo" << endl;
}

void addStudentsFromSTDIN(vector<Student> &students) {
    char action = 't';
    do {
        Student newStudent;
        enterStudentData(newStudent);
        students.push_back(newStudent);

        cout << "Baigti darba spausk \"b\", testi spausk bet kuri kita klavisa: ";
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    } while(action != 'b' && action != 'B');
}

void enterStudentData(Student &student) {
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> student.name >> student.surname;
    
    cout << "Generuoti pazymius spausk \"g\", ivesti pazymius spausk \"i\": ";
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (action == 'g' || action == 'G') {
        generateGrades(student);
        return;
    }

    cout << "Iveskite studento namu darbu pazymius, norint baigti iveskite raide:" << endl;
    while (student.homeworkGrades.size() == 0){
        float homeworkGrade;
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

void calculateFinalGrade(Student &student) {
    vector<float> homeworkGrades = student.homeworkGrades;

    double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0);
    student.finalGradeAverage = sum / homeworkGrades.size() * 0.4 + student.examGrade * 0.6;
    
    sort(homeworkGrades.begin(), homeworkGrades.end());
    int hCount = homeworkGrades.size();
    float l = homeworkGrades[hCount - hCount / 2 - 1];
    float r = homeworkGrades[hCount / 2];
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

string getResults(vector<Student> students) {
    cout << "Apskaiciuoti namu darbus vidurkiu spausk \"v\", mediana spausk \"m\": ";
    
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    bool useAverage = action == 'v' ? true : false;
    string finalGradeType = useAverage ? "Vid." : "Med.";
    stringstream ss;
    ss << setw(20) << left << "Pavarde" << setw(20) << "Vardas" << "Galutinis (" + finalGradeType + ")" << endl;
    ss << string(55, '-') << endl;

    string res = ss.str();
    for (int i = 0; i < students.size() - 1; i++) {
        res += getFormatedStudentData(students[i], useAverage) + "\n";
    } res += getFormatedStudentData(students[students.size() - 1], useAverage);

    return res;
}

string getFormatedStudentData(Student student, bool useAverage) {
    stringstream ss;
    double finalGrade = useAverage ? student.finalGradeAverage : student.finalGradeMedian;
    ss << setw(20) << left << student.surname << setw(20) << student.name << setprecision(2) << fixed << finalGrade;
    return ss.str();
}