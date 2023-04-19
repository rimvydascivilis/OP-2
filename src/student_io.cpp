#include "student_io.h"

char getActionFromInput() {
    cout << "Ivesti studentu duomenis is failo spausk \"f\"\n";
    cout << "Ivesti studentu duomenis is klaviaturos spausk \"k\"\n";
    cout << "Generuoti studentu failus spausk \"g\"" << endl;
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return tolower(action);
}

void addStudentsFromFile(vector<Student> &students, string fileName) {
    ifstream file(fileName);

    int currentLine = 0;
    string line;
    int gradesCount = 0;

    getline(file, line);
    stringstream ss(line);
    string grade;
    while (ss >> grade) {
        gradesCount++;
    }
    gradesCount -= 2; // name and surname

    while (getline(file, line)) {
        currentLine++;
        Student newStudent = parseLine(line);

        if (newStudent.homeworkGrades.size() < 2) {
            cout << "Nepavyko nuskaityti pazymiu, studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        if (newStudent.homeworkGrades.size() != gradesCount) {
            cout << "Nepavyko nuskaityti visu pazymiu, arba nesuvesti visi pazymiai? studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        newStudent.examGrade = newStudent.homeworkGrades.back();
        newStudent.homeworkGrades.pop_back();
        students.push_back(newStudent);
    }
    file.close();
    if (students.empty()) {
        cout << "Nepavyko nuskaityti nei vieno studento is failo" << endl;
        exit(1);
    }
}

void addStudentsFromFile(list<Student> &students, string fileName) {
    ifstream file(fileName);

    int currentLine = 0;
    string line;
    int gradesCount = 0;

    getline(file, line);
    stringstream ss(line);
    string grade;
    while (ss >> grade) {
        gradesCount++;
    }
    gradesCount -= 2; // name and surname

    while (getline(file, line)) {
        currentLine++;
        Student newStudent = parseLine(line);

        if (newStudent.homeworkGrades.size() < 2) {
            cout << "Nepavyko nuskaityti pazymiu, studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        if (newStudent.homeworkGrades.size() != gradesCount) {
            cout << "Nepavyko nuskaityti visu pazymiu, arba nesuvesti visi pazymiai? studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        newStudent.examGrade = newStudent.homeworkGrades.back();
        newStudent.homeworkGrades.pop_back();
        students.push_back(newStudent);
    }
    file.close();
    if (students.empty()) {
        cout << "Nepavyko nuskaityti nei vieno studento is failo" << endl;
        exit(1);
    }
}

void addStudentsFromFile(deque<Student> &students, string fileName) {
    ifstream file(fileName);

    int currentLine = 0;
    string line;
    int gradesCount = 0;

    getline(file, line);
    stringstream ss(line);
    string grade;
    while (ss >> grade) {
        gradesCount++;
    }
    gradesCount -= 2; // name and surname

    while (getline(file, line)) {
        currentLine++;
        Student newStudent = parseLine(line);

        if (newStudent.homeworkGrades.size() < 2) {
            cout << "Nepavyko nuskaityti pazymiu, studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        if (newStudent.homeworkGrades.size() != gradesCount) {
            cout << "Nepavyko nuskaityti visu pazymiu, arba nesuvesti visi pazymiai? studentas praleidziamas (" << currentLine << "eil.)" << endl;
            continue;
        }
        newStudent.examGrade = newStudent.homeworkGrades.back();
        newStudent.homeworkGrades.pop_back();
        students.push_back(newStudent);
    }
    file.close();
    if (students.empty()) {
        cout << "Nepavyko nuskaityti nei vieno studento is failo" << endl;
        exit(1);
    }
}

int getHomeworkCountFromInput() {
    int homeworkCount;
    while (true) {
        cout << "Iveskite namu darbu skaiciu: ";
        cin >> homeworkCount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ivestas netinkamas skaicius" << endl;
            continue;
        }
        if (homeworkCount < 1) {
            cout << "Ivestas netinkamas skaicius" << endl;
            continue;
        }
        break;
    }
    return homeworkCount;
}

string getFileNameFromInput() {
    string fileName;

    cout << "Failu sarasas:" << endl;
    int errCode = system("ls data 2> /dev/null");
    if (errCode != 0) {
        cout << "Nepavyko nuskaityti failu saraso" << endl;
    }

    while (true) {
        cout << "Iveskite failo pavadinima, norint iseiti ivesk \"iseiti\": ";
        cin >> fileName;
        if (fileName == "iseiti") {
            exit(0);
        }
        fileName = "data/" + fileName;
        try {
            if (!fileExists(fileName)) {
                throw invalid_argument("Nepavyko atidaryti failo, failas neegzistuoja");
            }

            if (fileEmpty(fileName)) {
                throw invalid_argument("Failas tuscias");
            }
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
    return fileName;
}

bool fileExists(const string& fileName) {
    ifstream file(fileName);
    bool exists = file.good();
    file.close();
    return exists;
}

bool fileEmpty(string fileName) {
    ifstream file(fileName);
    bool empty = file.peek() == ifstream::traits_type::eof();
    file.close();
    return empty;
}

Student parseLine(const string& line) {
    stringstream ss(line);
    Student student;
    ss >> student.name >> student.surname;

    string grade;
    while (ss >> grade) {
        grade = cleanGradeString(grade);
        try {
            float gradeFloat = stof(grade);
            if (gradeFloat < 0 || gradeFloat > 10) {
                throw invalid_argument("Negalimas pazymys " + grade);
            }
            student.homeworkGrades.push_back(gradeFloat);
        } catch (const invalid_argument& ia) {
            cout << "Negalima apdoroti pazymio: " << ia.what() << endl;
        }
    }

    return student;
}

string cleanGradeString(string grade) {
    grade.erase(remove_if(grade.begin(), grade.end(), [](char c) {
        return !isdigit(c) && c != '.' && c != ',';
    }), grade.end());

    replace(grade.begin(), grade.end(), ',', '.');

    return grade;
}

void addStudentsFromSTDIN(vector<Student> &students) {
    char action = 't';
    do {
        Student newStudent;
        enterStudentInformation(newStudent);
        students.push_back(newStudent);

        cout << "Baigti darba spausk \"b\", testi spausk bet kuri kita klavisa: ";
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(action) != 'b');
}

void addStudentsFromSTDIN(list<Student> &students) {
    char action = 't';
    do {
        Student newStudent;
        enterStudentInformation(newStudent);
        students.push_back(newStudent);

        cout << "Baigti darba spausk \"b\", testi spausk bet kuri kita klavisa: ";
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(action) != 'b');
}

void addStudentsFromSTDIN(deque<Student> &students) {
    char action = 't';
    do {
        Student newStudent;
        enterStudentInformation(newStudent);
        students.push_back(newStudent);

        cout << "Baigti darba spausk \"b\", testi spausk bet kuri kita klavisa: ";
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(action) != 'b');
}

void enterStudentInformation(Student &student) {
    cout << "Iveskite studento varda ir pavarde: ";
    cin >> student.name >> student.surname;

    cout << "Generuoti pazymius spausk \"g\", ivesti pazymius spausk \"i\": ";
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (tolower(action) == 'g') {
        int gradesToGenerate;
        while (true) {
            cout << "Iveskite studento namu darbu pazymiu skaiciu: ";
            if (cin >> gradesToGenerate && gradesToGenerate >= 0) {
                break;
            }
            cout << "Pakartokite ivedima. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        generateGrades(student, gradesToGenerate);
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
        if (!(cin >> student.examGrade)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Neteisingas pazymys, pakartokite: ";
            continue;
        }
        if (student.examGrade < 0 || student.examGrade > 10) {
            cout << "Pazymys turi buti nuo 0 iki 10, pakartokite: ";
            continue;
        }
        break;
    }
}

bool getFinalGradeCalculationMethod() {
    char action;
    cout << "Skaiciuoti galutini pazymi pagal vidurki spausk \"v\"\n";
    cout << "Skaiciuoti galutini pazymi pagal mediana spausk \"m\"" << endl;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return action == 'v';
}

void writeResultsToFile(vector<Student>& students, string fileName, bool useAverage) {
    if (students.size() < 1) return;

    string finalGradeType = useAverage ? "Vid." : "Med.";
    stringstream ss;
    ss << setw(20) << left << "Pavarde" << setw(20) << "Vardas" << "Galutinis (" + finalGradeType + ")" << endl;
    ss << string(60, '-') << endl;

    string res = ss.str();
    for (int i = 0; i < students.size() - 1; i++) {
        res += getFormattedStudentData(students.at(i), useAverage) + "\n";
    }
    res += getFormattedStudentData(students.at(students.size() - 1), useAverage);

    ofstream file(fileName);
    file << res;
    file.close();
}

void writeResultsToFile(list<Student> &students, string fileName, bool useAverage) {
    if (students.size() < 1) return;

    string finalGradeType = useAverage ? "Vid." : "Med.";
    stringstream ss;
    ss << setw(20) << left << "Pavarde" << setw(20) << "Vardas" << "Galutinis (" + finalGradeType + ")" << endl;
    ss << string(60, '-') << endl;

    string res = ss.str();
    for (auto it = students.begin(); it != prev(students.end()); it++) {
        res += getFormattedStudentData(*it, useAverage) + "\n";
    }
    res += getFormattedStudentData(students.back(), useAverage);

    ofstream file(fileName);
    file << res;
    file.close();
}

void writeResultsToFile(deque<Student> &students, string fileName, bool useAverage) {
    if (students.size() < 1) return;

    string finalGradeType = useAverage ? "Vid." : "Med.";
    stringstream ss;
    ss << setw(20) << left << "Pavarde" << setw(20) << "Vardas" << "Galutinis (" + finalGradeType + ")" << endl;
    ss << string(60, '-') << endl;

    string res = ss.str();
    for (int i = 0; i < students.size() - 1; i++) {
        res += getFormattedStudentData(students.at(i), useAverage) + "\n";
    }
    res += getFormattedStudentData(students.at(students.size() - 1), useAverage);

    ofstream file(fileName);
    file << res;
    file.close();
}

string getFormattedStudentData(const Student& student, bool useAverage) {
    stringstream ss;
    ss << setw(20) << left << student.surname << setw(20) << student.name << setprecision(2) << fixed << student.finalGrade;
    return ss.str();
}
