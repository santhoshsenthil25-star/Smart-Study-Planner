#include <iostream>
#include <vector>
#include<limits>
#include <thread>
#include <chrono>
using namespace std;

class Subject {
public:
    string name;
    int difficulty;
    int confidence;
    int priority;
    double allocatedHours;

    void calculatePriority() {
        priority = (difficulty * 2) + (5 - confidence);
    }
};

int main() {

    int n;
    cout << "Enter number of subjects: ";
    cin >> n;

    \

    int hoursPerDay;
    cout << "Enter study hours per day: ";
    cin >> hoursPerDay;

    vector<Subject> subjects(n);

    for(int i = 0; i < n; i++) {
    cout << "\nEnter name of subject " << i+1 << ": ";
    cin.ignore();
    getline(cin, subjects[i].name);

    cout << "Enter difficulty (1-5): ";
    cin >> subjects[i].difficulty;

    cout << "Enter confidence (1-5): ";
    cin >> subjects[i].confidence;

    subjects[i].calculatePriority();
}

    int totalPriority = 0;
    for(int i = 0; i < n; i++) {
    totalPriority += subjects[i].priority;
    }

    int totalHours = hoursPerDay;
    cout<< "TotalHours = " << totalHours << endl;

    
    for(int i = 0; i < n; i++) {
    subjects[i].allocatedHours =
        (double(subjects[i].priority) / totalPriority) * hoursPerDay;
}

    cout << "\n===== STUDY PLAN RESULT =====\n";
    for(int i = 0; i < n; i++) {
    cout << subjects[i].name
         << " -> Study " << subjects[i].allocatedHours
         << " hrs/day (Priority: " << subjects[i].priority << ")\n";
}
    int choice;
    cout << "\nSelect subject number to start focus (1 to " << n << "): ";
    cin >> choice;

    cout << "\nStarting focus session for " << subjectNames[choice-1] << "...\n";

    // For demo: small timer
    int timeInSeconds = allocatedHours[choice-1] * 10;

    for(int i = timeInSeconds; i > 0; i--) {
        cout << "Time left: " << i << " seconds\r";
        cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cout << "\nSession complete!\n";

    return 0;
}