#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Course class (base class for all types of courses)
class Course {
protected:
    string courseCode;     // Unique identifier for the course
    string title;          // Name of the course
    string instructor;     // Instructor's name
    int capacity;          // Max number of students allowed
    int enrolled;          // Current number of enrolled students

public:
    // Constructor to initialize course data
    Course(string c, string t, string i, int cap) {
        courseCode = c;
        title = t;
        instructor = i;
        capacity = cap;
        enrolled = 0;
    }

    // Display course details (can be overridden)
    virtual void display() {
        cout << "Course Code: " << courseCode << endl;
        cout << "Title: " << title << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Enrolled: " << enrolled << endl;
    }

    // Basic getters and utilities
    string getCode() { return courseCode; }
    int getEnrolled() { return enrolled; }
    int getCapacity() { return capacity; }
    void incrementEnrollment() { enrolled++; }

    // Used to identify LabCourse (default = false)
    virtual bool isLabCourse() { return false; }

    // Returns list of co-requisites (default = empty)
    virtual vector<string> getCoReqs() { return {}; }

    // Virtual destructor for proper cleanup
    virtual ~Course() {}
};

