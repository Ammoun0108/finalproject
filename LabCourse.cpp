#pragma once
#include "Course.cpp"
// LabCourse is a specialized Course that has co-requisites
class LabCourse : public Course {
private:
    vector<string> coReqs; // List of required co-requisite course codes

public:
    // Constructor for lab course
    LabCourse(string c, string t, string i, int cap, vector<string> reqs)
        : Course(c, t, i, cap), coReqs(reqs) {}

    // Display extended details for LabCourse
    void display() override {
        cout << "Course Code: " << courseCode << endl;
        cout << "Title: " << title << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Enrolled: " << enrolled << endl;
        cout << "Co-requisites: ";
        for (string code : coReqs) {
            cout << code << " ";
        }
        cout << endl;
    }

    // Identify this course as a lab course
    bool isLabCourse() override { return true; }

    // Return the co-requisite course list
    vector<string> getCoReqs() override { return coReqs; }
};
