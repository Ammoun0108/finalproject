

#include"Course.cpp"
#include"LabCourse.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


// Function to try enrolling in a course
void tryEnroll(string code,
    unordered_map<string, Course*>& allCourses,
    unordered_map<string, Course*>& completedCourses,
    unordered_map<string, Course*>& enrolledCourses) {

    // Check if course exists in the system
    if (allCourses.find(code) == allCourses.end())
        throw string("Course not found.");

    // Check if the student is already enrolled
    if (enrolledCourses.find(code) != enrolledCourses.end())
        throw string("Already enrolled.");

    Course* course = allCourses[code];

    // Check if the course is already full
    if (course->getEnrolled() >= course->getCapacity())
        throw string("Course is full.");

    // If the course is a lab course, make sure co-requisites are met
    if (course->isLabCourse()) {
        for (string req : course->getCoReqs()) {
            // Check that each required co-req is either completed or already enrolled
            if (enrolledCourses.count(req) == 0 && completedCourses.count(req) == 0) {
                throw string("Missing co-requisite: " + req);
            }
        }
    }

    // All checks passed: enroll the student
    course->incrementEnrollment();
    enrolledCourses[code] = course;
    cout << "Successfully enrolled in " << code << endl;
}

int main() {
    // Maps to hold course data
    unordered_map<string, Course*> allCourses;       // All offered courses
    unordered_map<string, Course*> completedCourses; // Courses student already completed
    unordered_map<string, Course*> enrolledCourses;  // Courses student is currently enrolled in
    
    // Add example standard courses
    allCourses["CS101"] = new Course("CS101", "Intro to CS", "Snyder", 2);
    
    allCourses["ENG101"] = new Course("ENG101", "English Composition", "Brown", 2);
    allCourses["PHYS101"] = new Course("PHYS101", "Physics I", "Clark", 2);
    allCourses["CHEM101"] = new Course("CHEM101", "Chemistry I", "Watson", 2);

    // Add example lab courses with co-requisites
    allCourses["CS102"] = new LabCourse("CS102", "CS Lab", "Snyder", 2, { "CS101","MATH101"});
    allCourses["PHYS102"] = new LabCourse("PHYS102", "Physics Lab", "Taylor", 2, { "PHYS101" });
    allCourses["CHEM102"] = new LabCourse("CHEM102", "Chemistry Lab", "Lee", 2, { "CHEM101" });

    // Add completed courses manually (simulate student history  )
   
    completedCourses["MATH101"] = new Course("MATH101", "Calculus I", "Zhong", 3);
  
    string code; // To hold user input
    while (true) {
        // Display all courses before each enrollment prompt
        cout << "\nAvailable courses:\n";
        for (auto& p : allCourses) {
            p.second->display(); // Call display function (uses polymorphism)
            cout << "---\n";
        }

        // Prompt user for course code
        cout << "Enter course code to enroll (or 'exit' to quit): ";
        cin >> code;
        if (code == "exit") break; // Exit loop if user types 'exit'

        try {
            // Try to enroll in the requested course
            tryEnroll(code, allCourses, completedCourses, enrolledCourses);
        }
        catch (string& e) {
            // Catch and print any error messages from tryEnroll
            cout << "Enrollment failed: " << e << endl;
        }
    }

    // Clean up dynamically allocated memory
    for (auto& p : allCourses) {
        delete p.second;
    }

    return 0; // End of program
}

