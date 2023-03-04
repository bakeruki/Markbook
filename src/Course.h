#pragma once
#include <string>
#include <vector>
#include "Student.h"

struct Course
{
	std::string teacher;
	std::string subject;
	std::vector<Student> students;
};

void saveCourseToFile(const std::vector<Student>& students, const std::string& teacher, const std::string& subject, const std::string& fileName);
Course loadCourseFromFile(const std::string& fileName);
