#include "student.h"

Student::Student(Student &&s) {
    setName(s.getName());
    setSurname(s.getSurname());
    homeworkGrades = move(s.homeworkGrades);
    examGrade = move(s.examGrade);
    finalGrade = move(s.finalGrade);

    s.setName("");
    s.setSurname("");
    s.homeworkGrades.clear();
    s.homeworkGrades.shrink_to_fit();
    s.examGrade = 0;
    s.finalGrade = 0;
}

void Student::calculateFinalGrade(bool useAverage) {
    if (useAverage) {
        calculateFinalGradeAverage();
    } else {
        calculateFinalGradeMedian();
    }
}

void Student::calculateFinalGradeAverage() {
    double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0.0);
    double average = sum / homeworkGrades.size();
    finalGrade = average * 0.4 + examGrade * 0.6;
}

void Student::calculateFinalGradeMedian() {
    vector<float> hw = homeworkGrades;
    sort(hw.begin(), hw.end());
    size_t n = hw.size();
    float median = (n % 2 == 0) ? (hw[n / 2 - 1] + hw[n / 2]) / 2.0f
                                    : hw[n / 2];
    finalGrade = median * 0.4f + examGrade * 0.6f;
}

void Student::generateGrades(int gradesToGenerate, mt19937 *gen) {
    if (gen == nullptr) {
        static random_device rd;
        static mt19937 eng(rd());
        gen = &eng;
    }

    uniform_int_distribution<int> disGrades(0, 10);
    homeworkGrades.resize(gradesToGenerate);
    for (int i = 0; i < gradesToGenerate; i++) {
        homeworkGrades[i] = disGrades(*gen);
    }
    examGrade = disGrades(*gen);
}

void Student::sayHello() {
    cout << "Hello, I'm a student, " << getName() << " " << getSurname() << "!" << endl;
}

istream &operator>>(istream &is, Student &s) {
    string line, name, surname;
    getline(is, line);
    stringstream ss(line);
    ss >> name >> surname;
    s.setName(name);
    s.setSurname(surname);
    float grade;
    while (ss >> grade) {
        s.homeworkGrades.push_back(grade);
    }
    s.examGrade = s.homeworkGrades.back();
    s.homeworkGrades.pop_back();
    return is;
}

ostream& operator<<(ostream &os, const Student &s) {
    os << setw(20) << left << s.getSurname() << setw(20) << s.getName() <<
    setprecision(2) << fixed << s.getFinalGrade();
    return os;
}

Student &Student::operator=(const Student &s) {
    if (this != &s) {
        setName(s.getName());
        setSurname(s.getSurname());
        homeworkGrades = s.homeworkGrades;
        examGrade = s.examGrade;
        finalGrade = s.finalGrade;
    }
    return *this;
}

Student &Student::operator=(Student &&s) {
    if (this != &s) {
        setName(s.getName());
        setSurname(s.getSurname());
        homeworkGrades = move(s.homeworkGrades);
        examGrade = s.examGrade;
        finalGrade = s.finalGrade;

        s.setName("");
        s.setSurname("");
        s.homeworkGrades.clear();
        s.examGrade = 0;
        s.finalGrade = 0;
    }
    return *this;
}

bool compareFinalGradeAscending(const Student &a, const Student &b) {
    return a.getFinalGrade() < b.getFinalGrade();
}

bool compareFinalGradeDescending(const Student &a, const Student &b) {
    return a.getFinalGrade() > b.getFinalGrade();
}
