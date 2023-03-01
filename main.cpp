#include "MyLib.h"

int main() {
    vector<Student> students;
    string results;

    addStudents(students);
    if (students.size() == 0) {
        cout << "Nera duomenu, rezultatu failas nebus sukurtas" << endl;
        return 0;
    }
    cout << "Skaiciuojami balai..." << endl;
    for (Student &student : students) {
        calculateFinalGrade(student);
    }
    cout << "Rezultatai surikiuojami..." << endl;
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.surname < b.surname; });
    cout << "Rezultatai isvedami i faila..." << endl;
    writeResultsToFile(students, "rezultatai.txt");
    
    return 0;
}

void addStudents(vector<Student> &students) {
    cout << "Ivesti studentus is failo spausk \"f\", is klaviaturos spausk \"k\": ";
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (action == 'f' || action == 'F') {
        addStudentsFromFile(students);
    } else {
        addStudentsFromSTDIN(students);
    }
}

void addStudentsFromFile(vector<Student> &students) {
    string fileName;
    ifstream file;

    cout << "Failu sarasas:";
    fflush(stdout);
    int exitCode = system("ls -l | awk '{print $9}'");

    if (exitCode != 0) {
        cout << "Nepavyko nuskaityti failu saraso" << endl;
        return;
    }
    
    while(1) {
        cout << "Iveskite failo pavadinima, norint iseiti ivesk \"iseiti\": ";
        cin >> fileName;
        if (fileName == "iseiti") {
                exit(0);
        }
        try {
            file.open(fileName);     
            if (!file.is_open()) {
                throw invalid_argument("Nepavyko atidaryti failo");
            }
            if (file.peek() == ifstream::traits_type::eof()) {
                throw invalid_argument("Failas tuscias");
            }
            break;
        } catch(const exception& ia) {
            cout << ia.what() << '\n';
        }
    }

    cout << "Nuskaitomi studentai is failo..." << endl;

    int currentLine = 0;
    string line;
    int gradesCount = 0;

    getline(file, line);
    stringstream ss(line);
    string grade;
    while (ss >> grade) {
        gradesCount++;
    }
    gradesCount -= 2;


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
            } catch (const invalid_argument& ia) {
                cout << "Nepavyko konvertuoti pazymio i skaiciu, pazymys praleidziamas (" << currentLine <<  "eil.)" << endl;
            }
        }
        if (newStudent.homeworkGrades.size() < 2) {
            cout << "Nepavyko nuskaityti pazymiu, studentas praleidziamas (" << currentLine <<  "eil.)" << endl;
            continue;
        }
        if (newStudent.homeworkGrades.size() != gradesCount) {
            cout << "Nepavyko nuskaityti visu pazymiu ar nesuvesti visi pazymiai, studentas praleidziamas (" << currentLine <<  "eil.)" << endl;
            continue;
        }

        newStudent.examGrade = newStudent.homeworkGrades.back();
        newStudent.homeworkGrades.pop_back();
        students.push_back(newStudent);
    }
    file.close();
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
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
    int gradesToGenerate = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> disGrades(0, 10);
    cout << "Iveskite studento namu darbu pazymiu skaiciu: ";
    while (1) {
        cin >> gradesToGenerate;
        if (!cin) {
            cout << "Ivedete ne skaiciu, pakartokite: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        if (gradesToGenerate < 0) {
            cout << "Pazymiu skaicius turi buti nuo 1, pakartokite: " << endl;
            continue;
        }
        break;
    }

    for (int i = 0; i < gradesToGenerate; i++) {
        student.homeworkGrades.push_back(disGrades(gen));
    }
    student.examGrade = disGrades(gen);
}

void writeResultsToFile(vector<Student> &students, string fileName) {
    cout << "Apskaiciuoti namu darbus vidurkiu spausk \"v\", mediana spausk \"m\": ";
    
    char action;
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    bool useAverage = action == 'v' ? true : false;
    string finalGradeType = useAverage ? "Vid." : "Med.";
    stringstream ss;
    ss << setw(20) << left << "Pavarde" << setw(20) << "Vardas" << "Galutinis (" + finalGradeType + ")" << endl;
    ss << string(60, '-') << endl;

    string res = ss.str();
    for (int i = 0; i < students.size() - 1; i++) {
        res += getFormatedStudentData(students[i], useAverage) + "\n";
    } res += getFormatedStudentData(students[students.size() - 1], useAverage);

    ofstream file(fileName);
    file << res;
    file.close();
}

string getFormatedStudentData(Student student, bool useAverage) {
    stringstream ss;
    double finalGrade = useAverage ? student.finalGradeAverage : student.finalGradeMedian;
    ss << setw(20) << left << student.surname << setw(20) << student.name << setprecision(2) << fixed << finalGrade;
    return ss.str();
}