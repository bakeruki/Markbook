#include "Course.h"
#include "Student.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveCourseToFile(const std::vector<Student>& students, const std::string& teacher, const std::string& subject, const std::string& fileName)
{
    /*Text File Structure:
    * teacherName
    * subject
    * numStudents
    * firstname lastname average
    * firstname lastname average
    * and so on
    */

    std::ofstream ostream(fileName);
    //teacherName
    ostream << teacher;
    //subject
    ostream << subject;
    //number of students
    ostream << students.size();

    for (const Student& student : students) {
        std::string fullName = student.firstName + " " + student.lastName;

        ostream << '\n' << fullName << ' ' << student.average;
    }
}

Course loadCourseFromFile(const std::string& fileName)
{
    if (!std::filesystem::exists(fileName)) {
        return Course();
    }
  
    std::vector<Student> students;
    std::ifstream istream(fileName);

    std::string teacher;
    istream >> teacher;

    std::string subject;
    istream >> subject;

    int n;
    istream >> n;

    for (int i = 0; i < n; i++) {
        std::string firstName;
        std::string lastName;
        double average;

        istream >> firstName >> lastName >> average;

        students.push_back(Student{firstName, lastName, average});
    }

    return Course{ teacher, subject, students };
}
