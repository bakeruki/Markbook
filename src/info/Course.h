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

void SaveCoursesToFile(const std::vector<Course>& courses, const std::string& fileName);
std::vector<Course> LoadCoursesFromFile(const std::string& fileName);
