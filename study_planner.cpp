#include <iostream>
#include <vector>
#include<limits>
#include <thread>
#include <chrono>
using namespace std;

int main() {

    int n;
    cout << "Enter number of subjects: ";
    cin >> n;

    \

    int hoursPerDay;
    cout << "Enter study hours per day: ";
    cin >> hoursPerDay;

    vector<string> subjectNames(n);
    vector<int> difficulty(n);
    vector<int> confidence(n);
    vector<int> priority(n);
    vector<double> allocatedHours(n);

    for(int i = 0; i < n; i++) {
        cout << "\nEnter name of subject " << i+1 << ": ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, subjectNames[i]);

        cout << "Enter difficulty (1-5): ";
        cin >> difficulty[i];

        cout << "Enter confidence (1-5): ";
        cin >> confidence[i];

        priority[i] = (difficulty[i] * 2) + (5 - confidence[i]);

       
    }

    int totalPriority = 0;
    for(int i = 0; i < n; i++) {
        totalPriority += priority[i];
    }

    int totalHours = hoursPerDay;
    cout<< "TotalHours = " << totalHours << endl;

    
    for(int i = 0; i < n; i++) {
        allocatedHours[i] = (double(priority[i]) / totalPriority) * totalHours;
    }

    cout << "\n===== STUDY PLAN RESULT =====\n";
    for(int i = 0; i < n; i++) {
        cout << subjectNames[i] 
             << " -> Study " << allocatedHours[i]
             << " hrs/day (Priority: " << priority[i] << ")" << endl;
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