#include <gtest/gtest.h>
#include "student.h"

TEST(StudentTest, Constructor) {
    Student s("John", "Smith");
    EXPECT_EQ(s.getName(), "John");
    EXPECT_EQ(s.getSurname(), "Smith");
}

TEST(StudentTest, CalculateFinalGradeAverage) {
    Student s("John", "Smith", {1, 1, 1, 6, 10}, 5);
    s.calculateFinalGrade(true);
    EXPECT_EQ(s.getFinalGrade(), 4.52);
}

TEST(StudentTest, CalculateFinalGradeMedian) {
    Student s("John", "Smith", {1, 9, 10, 3, 5}, 5);
    s.calculateFinalGrade(false);
    EXPECT_EQ(s.getFinalGrade(), 5);
}
