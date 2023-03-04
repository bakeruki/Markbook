#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Student.h"
#include "Course.h"

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

	//get courses
	std::vector<Student> students;
	students.push_back(Student{ "Michelle", "Vuong", 99 });
	students.push_back(Student{ "Luqman", "Patel", 98 });
	courses.push_back(Course{ "Camilleri", "Computer Science", students });
	courses.push_back(Course{ "Megson", "Data Management", students });

	//create dropdown menu
	wxArrayString choices = BuildDropdownChoiceArray();
	courseSelectDropdown = new wxChoice(panel, wxID_ANY, wxPoint(250, 100), wxSize(300, -1), choices);
	courseSelectDropdown->SetFont(mainFont);

	//create buttons
	addCourseButton = new wxButton(panel, wxID_ANY, "Add Course", wxPoint(75, 100), wxSize(150, -1));

	//create list 
	studentList = new wxListView(panel, wxID_ANY, wxPoint(100, 200), wxSize(600, -1));
	BuildStudentList();

	//create header
	headline = "No course selected!";
	headlineText = new wxStaticText(panel, wxID_ANY, headline, wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
}

void MainFrame::BindEventHandlers()
{
	courseSelectDropdown->Bind(wxEVT_CHOICE, &MainFrame::OnDropdownChange, this);
}

wxArrayString MainFrame::BuildDropdownChoiceArray()
{
	wxArrayString choices;
	for (Course& course : courses) {
		choices.Add(course.subject);
	}
	return choices;
}

void MainFrame::BuildStudentList()
{
	studentList->AppendColumn("First Name");
	studentList->AppendColumn("Last Name");
	studentList->AppendColumn("Grade");
	studentList->SetColumnWidth(0, 250);
	studentList->SetColumnWidth(1, 250);
	studentList->SetColumnWidth(2, 100);
}

void MainFrame::OnDropdownChange(wxCommandEvent& evt)
{
	UpdateActiveCourse(evt.GetString());
	headlineText->SetLabel(activeCourse.teacher + " - " + activeCourse.subject);
}

void MainFrame::UpdateActiveCourse(wxString courseName)
{
	for (Course course : courses) {
		if (course.subject == courseName) {
			activeCourse = course;
		}
	}
}
