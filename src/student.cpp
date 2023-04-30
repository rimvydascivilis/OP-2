#include "student.h"

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

ostream& operator<<(ostream &os, const Student &s) {
    os << setw(20) << left << s.getSurname() << setw(20) << s.getName() <<
    setprecision(2) << fixed << s.getFinalGrade();
    return os;
}

bool compareFinalGradeAscending(const Student &a, const Student &b) {
    return a.getFinalGrade() < b.getFinalGrade();
}

bool compareFinalGradeDescending(const Student &a, const Student &b) {
    return a.getFinalGrade() > b.getFinalGrade();
}
