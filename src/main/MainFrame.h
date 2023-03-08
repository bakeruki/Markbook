#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <string>
#include "../info/Course.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	//init functions
	void CreateControls();
	void BindEventHandlers();

	//control creation helpers
	wxArrayString BuildDropdownChoiceArray();
	void BuildDropdown();
	void BuildStudentList();
	void PopulateStudentList();

	//event handlers
	void OnDropdownChange(wxCommandEvent& evt);
	void OnAddStudentButtonClick(wxCommandEvent& evt);
	void OnCourseInfoButtonClick(wxCommandEvent& evt);
	void OnAddCourseButtonClick(wxCommandEvent& evt);
	void OnWindowClose(wxCloseEvent& evt);

	//event helpers
	void UpdateActiveCourse(wxString courseName);

	//elements
	wxPanel* panel;
	wxStaticText* headlineText;
	wxChoice* courseSelectDropdown;
	wxButton* addCourseButton;
	wxButton* courseInfoButton;
	wxButton* addStudentButton;
	wxListView* studentList;

	//variables
	std::string headline;
	std::vector<Course> courses;
	Course* activeCourse;
};

