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
	std::vector<Student> studentsA;
	std::vector<Student> studentsB;
	studentsA.push_back(Student{ "Michelle", "Vuong", 99.99 });
	studentsA.push_back(Student{ "Luqman", "Patel", 98.32 });
	studentsB.push_back(Student{ "Sean", "Lee", 78.43 });
	studentsB.push_back(Student{ "Adrian", "Garcia", 56.23 });
	courses.push_back(Course{ "Camilleri", "Computer Science", studentsA });
	courses.push_back(Course{ "Megson", "Data Management", studentsB });

	//create dropdown menu
	wxArrayString choices = BuildDropdownChoiceArray();
	courseSelectDropdown = new wxChoice(panel, wxID_ANY, wxPoint(250, 100), wxSize(300, -1), choices);
	courseSelectDropdown->SetFont(mainFont);

	//create buttons
	addCourseButton = new wxButton(panel, wxID_ANY, "Add Course", wxPoint(75, 100), wxSize(150, -1));
	addStudentButton = new wxButton(panel, wxID_ANY, "Add Student", wxPoint(75, 525), wxSize(150, -1));

	//create list 
	studentList = new wxListView(panel, wxID_ANY, wxPoint(75, 150), wxSize(650, 350));
	BuildStudentList();
	PopulateStudentList();

	//create header
	headline = "No course selected!";
	headlineText = new wxStaticText(panel, wxID_ANY, headline, wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
}

void MainFrame::BindEventHandlers()
{
	courseSelectDropdown->Bind(wxEVT_CHOICE, &MainFrame::OnDropdownChange, this);
	addStudentButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddStudentButtonClick, this);
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
	studentList->SetColumnWidth(2, 150);
}

void MainFrame::PopulateStudentList()
{
	studentList->DeleteAllItems();
	int i = 0;
	for (Student student : activeCourse.students) {
		studentList->InsertItem(i, student.firstName);
		studentList->SetItem(i, 1, student.lastName);
		studentList->SetItem(i, 2, (std::to_string(student.average)).substr(0,5));
	}
}

void MainFrame::OnDropdownChange(wxCommandEvent& evt)
{
	UpdateActiveCourse(evt.GetString());
	headlineText->SetLabel(activeCourse.teacher + " - " + activeCourse.subject);
}

void MainFrame::OnAddStudentButtonClick(wxCommandEvent& evt)
{
	wxMessageDialog dialog(this, "Add Student Form", "Add Student", wxYES_NO | wxCANCEL);
	int result = dialog.ShowModal();
}

void MainFrame::UpdateActiveCourse(wxString courseName)
{
	for (Course course : courses) {
		if (course.subject == courseName) {
			activeCourse = course;
		}
	}

	PopulateStudentList();
}
