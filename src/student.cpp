#include "student.h"

void calculateFinalGrade(Student& student, bool useAverage) {
    if (useAverage) {
        double sum = accumulate(student.homeworkGrades.begin(), student.homeworkGrades.end(), 0.0);
        double average = sum / student.homeworkGrades.size();
        student.finalGrade = average * 0.4 + student.examGrade * 0.6;
    } else {
        vector<float> homeworkGrades = student.homeworkGrades;
        sort(homeworkGrades.begin(), homeworkGrades.end());
        size_t n = homeworkGrades.size();
        float median = (n % 2 == 0) ? (homeworkGrades[n / 2 - 1] + homeworkGrades[n / 2]) / 2.0f
                                     : homeworkGrades[n / 2];
        student.finalGrade = median * 0.4f + student.examGrade * 0.6f;
    }
}

void generateGrades(Student& student, int gradesToGenerate, mt19937 *gen) {
    if (gen == nullptr) {
        static random_device rd;
        static mt19937 eng(rd());
        gen = &eng;
    }

    uniform_int_distribution<int> disGrades(0, 10);
    student.homeworkGrades.resize(gradesToGenerate);
    for (int i = 0; i < gradesToGenerate; i++) {
        student.homeworkGrades[i] = disGrades(*gen);
    }
    student.examGrade = disGrades(*gen);
}
