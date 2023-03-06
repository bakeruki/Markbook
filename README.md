# Markbook
Simple Grade/Markbook GUI application made with wxWidgets in C++. My first attempt at learning C++.

# Features
- Add courses to the markbook
You can add a course to the markbook by clicking on the "Add Course" button, and then specifying a subject name and teacher name. 
- Add students to a course
Once you have selected a course, you can add a student to it by pressing the "Add Student" button at the bottom of the interface.
A first and last name must be specified, as well as a grade average (for now until assignments are added).
- Persistence
When the application is exited, the data is saved into a text file named "db.txt". It will be created if it is not found when the application is opened.

# Planned Features
- Ability to remove students
Coming very soon. You will be able to remove a student from a course.
- Ability to edit students.
Change their names, ect.
- Course Info Pane
Window that shows the information about the course, such as number of students, course median, ect.
- Adding assignments
You will be able to create assignments, and then specify the score that the student got on that assignment, which will affect their grade average.
- Adding weights
Ability to add groups of assignment weights (ie. a test is worth 30% of the overall grade) to a course, and then add those weights to
created assignments which will weigh on their average correctly.
