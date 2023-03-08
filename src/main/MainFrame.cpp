#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "../info/Course.h"
#include "../info/Student.h"
#include "../dialog/AddStudentDialog.h"
#include "../dialog/AddCourseDialog.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	//create panel
	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	//get courses - manually set for testing purposes for now
	courses = LoadCoursesFromFile("db.txt");

	//create dropdown menu
	BuildDropdown();

	//create buttons
	addCourseButton = new wxButton(panel, wxID_ANY, "Add Course", wxPoint(75, 100), wxSize(150, -1));
	courseInfoButton = new wxButton(panel, wxID_ANY, "Course Info", wxPoint(575, 100), wxSize(150, -1));
	addStudentButton = new wxButton(panel, wxID_ANY, "Add Student", wxPoint(75, 525), wxSize(150, -1));

	//create list 
	studentList = new wxListView(panel, wxID_ANY, wxPoint(75, 150), wxSize(650, 350));
	BuildStudentList();

	//create header
	headline = "No course selected!";
	headlineText = new wxStaticText(panel, wxID_ANY, headline, wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
}

void MainFrame::BindEventHandlers()
{
	courseSelectDropdown->Bind(wxEVT_CHOICE, &MainFrame::OnDropdownChange, this);
	addStudentButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddStudentButtonClick, this);
	courseInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnCourseInfoButtonClick, this);
	addCourseButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddCourseButtonClick, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClose, this);
}

wxArrayString MainFrame::BuildDropdownChoiceArray()
{
	wxArrayString choices;
	for (Course& course : courses) {
		choices.Add(course.subject);
	}
	return choices;
}

void MainFrame::BuildDropdown()
{
	wxArrayString choices = BuildDropdownChoiceArray();
	courseSelectDropdown = new wxChoice(panel, wxID_ANY, wxPoint(250, 100), wxSize(300, -1), (choices));
	courseSelectDropdown->SetFont(wxFontInfo(wxSize(0, 24)));
	courseSelectDropdown->Bind(wxEVT_CHOICE, &MainFrame::OnDropdownChange, this);
}

void MainFrame::BuildStudentList()
{
	studentList->AppendColumn("First Name");
	studentList->AppendColumn("Last Name");
	studentList->AppendColumn("Grade");
	studentList->SetColumnWidth(0, 250);
	studentList->SetColumnWidth(1, 250);
	studentList->SetColumnWidth(2, 150);
}

void MainFrame::PopulateStudentList()
{
	studentList->DeleteAllItems();
	int i = 0;
	for (Student student : (*activeCourse).students) {
		studentList->InsertItem(i, student.firstName);
		studentList->SetItem(i, 1, student.lastName);
		studentList->SetItem(i, 2, (std::to_string(student.average)).substr(0,5));
	}
}

void MainFrame::OnDropdownChange(wxCommandEvent& evt)
{
	UpdateActiveCourse(evt.GetString());
}

void MainFrame::OnAddStudentButtonClick(wxCommandEvent& evt)
{
	if (activeCourse == NULL) {
		wxMessageBox("Please select a class first!", "Error");
		return;
	}

	AddStudentDialog dialog(this, wxID_ANY, "Add Student");
	int result = dialog.ShowModal();

	if (result == wxID_OK) {
		wxMessageBox(wxString::Format("First Name: %s\nLast Name: %s\nAverage: %s\n", dialog.GetFirstName(), dialog.GetLastName(), std::to_string(dialog.GetAverage()).substr(0, 5)), "Student Added!");
		
		(*activeCourse).students.push_back(Student{ std::string(dialog.GetFirstName().mb_str()), std::string(dialog.GetLastName().mb_str()), dialog.GetAverage()});

		PopulateStudentList();
	}
}

void MainFrame::OnCourseInfoButtonClick(wxCommandEvent& evt)
{
	if (activeCourse == NULL) {
		wxMessageBox("Please select a class first!", "Error");
		return;
	}
	
	wxMessageBox(wxString::Format("Course Name: %s\nCourse Teacher: %s\nNumber of Students: %s\n", (*activeCourse).subject, (*activeCourse).teacher, std::to_string((*activeCourse).students.size())), "Course Info");
}

void MainFrame::OnAddCourseButtonClick(wxCommandEvent& evt)
{	
	AddCourseDialog dialog(this, wxID_ANY, "Add Course");
	int result = dialog.ShowModal();

	if (result == wxID_OK) {
		wxMessageBox(wxString::Format("Teacher: %s\nSubject: %s\n", dialog.GetTeacher(), dialog.GetSubject()), "Course Added!");

		std::vector<Student> students;
		Course course{ std::string(dialog.GetTeacher().mb_str()), std::string(dialog.GetSubject().mb_str()), students };

		courses.push_back(course);
		
		courseSelectDropdown->Destroy();
		BuildDropdown();
		courseSelectDropdown->SetSelection(courses.size() - 1);

		UpdateActiveCourse(course.subject);
	}
}

void MainFrame::OnWindowClose(wxCloseEvent& evt)
{
	SaveCoursesToFile(courses, "db.txt");
	evt.Skip();
}

void MainFrame::UpdateActiveCourse(wxString courseName)
{
	for (Course& course : courses) {
		if (course.subject == courseName) {
			activeCourse = &course;
		}
	}

	headlineText->SetLabel((*activeCourse).teacher + " - " + (*activeCourse).subject);
	PopulateStudentList();
}
