#include "Course.h"
#include "Student.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void SaveCoursesToFile(const std::vector<Course>& courses, const std::string& fileName)
{
    /*Text File Structure:
    * numCourses
    * teacherName
    * subject
    * numStudents
    * firstname lastname average
    * firstname lastname average
    * and so on
    * teacherName
    * subject
    * numStudents
    * firstname lastname average
    * and so on
    */

    std::ofstream ostream(fileName);
    //numCourses
    ostream << courses.size();

    for (Course course : courses) {
        //teacherName
        ostream << '\n' << course.teacher;
        //subject
        std::string subject = course.subject;
        std::replace(subject.begin(), subject.end(), ' ', '_');
        ostream << '\n' << subject;

        //number of students
        ostream << '\n' << course.students.size();

        //students
        for (const Student& student : course.students) {
            std::string fullName = student.firstName + ' ' + student.lastName;

            ostream << '\n' << fullName << ' ' << student.average;
        }
    }
}

std::vector<Course> LoadCoursesFromFile(const std::string& fileName)
{
    std::vector<Course> courses;

    if (!std::filesystem::exists(fileName)) {
        return courses;
    }
  
    std::ifstream istream(fileName);

    int numCourses;
    istream >> numCourses;

    for (int i = 0; i < numCourses; i++) {
        std::string teacher;
        istream >> teacher;

        std::string subject;
        istream >> subject;
        std::replace(subject.begin(), subject.end(), '_', ' ');

        int numStudents;
        istream >> numStudents;

        std::vector<Student> students;

        for (int j = 0; j < numStudents; j++) {
            std::string firstName;
            std::string lastName;
            double average;

            istream >> firstName >> lastName >> average;

            students.push_back(Student{ firstName, lastName, average });
        }
        
        courses.push_back(Course{ teacher, subject, students });
    }

    return courses;
}
