#include <iostream>
#include <vector>
#include <algorithm>
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

    void allocateHours(int totalHours, int totalPriority) {
        allocatedHours = (double(priority) / totalPriority) * totalHours;
    }
};

class StudyPlan {
private:
    vector<Subject> subjects;
    int streak;
    vector<int> dailyHours;
    int daysLeft;
    bool isExamDay;

public:
    void loadStreak(){
        FILE *file = fopen("streak.txt", "r");
        if(file == NULL) {
            streak = 0;
        } else {
            fscanf(file, "%d", &streak);
            fclose(file);
        }
    }

    void saveStreak() {
        FILE *file = fopen("streak.txt", "w");
        fprintf(file, "%d", streak);
        fclose(file);
    }
    void inputSubjects() {
        int n;
        cout << "Enter number of subjects: ";
        cin >> n;
        subjects.resize(n);

        for(int i = 0; i < n; i++) {
            cin.ignore(); // clear newline
            cout << "\nEnter name of subject " << i+1 << ": ";
            getline(cin, subjects[i].name);

            cout << "Enter difficulty (1-5): ";
            cin >> subjects[i].difficulty;

            cout << "Enter confidence (1-5): ";
            cin >> subjects[i].confidence;
        }

        string dayType;
        cout << "\nIs it exam days or normal days? (normal/exam): ";
        cin >> dayType;
        isExamDay = (dayType == "exam");

        if(isExamDay) 
        {
            cout << "Enter number of days left for exams: ";
            cin>> daysLeft;

            dailyHours.resize(daysLeft);

            for(int i = 0; i < daysLeft; i++) 
            {
                cout << "Enter study hours for Day " << i+1 << ": ";
                cin >> dailyHours[i];
            }
        } 
        else 
        {
            daysLeft = 1;
            dailyHours.resize(1);

            cout << "Enter study hours for today: ";
            cin >> dailyHours[0];
        }
    }
    

    void calculatePriorities() {
        for(auto &sub : subjects)
            sub.calculatePriority();
    }

    void sortByPriority() {
    sort(subjects.begin(), subjects.end(), [](Subject &a, Subject &b) {
        return a.priority > b.priority; // descending
        });
    }

    void allocateHours() {
    int totalPriority = 0;
    for(auto &sub : subjects) totalPriority += sub.priority;

    // Use Day 1 hours for initial display
    for(auto &sub : subjects)
        sub.allocatedHours = (double(sub.priority) / totalPriority) * dailyHours[0];
    }

    void displayPlan() {
        cout << "\n===== STUDY PLAN RESULT =====\n";
        for(size_t i = 0; i < subjects.size(); i++) {
            cout << i+1 << ". " << subjects[i].name
                 << " -> Study " << subjects[i].allocatedHours << " hrs/day"
                 << " (Priority: " << subjects[i].priority << ")" << endl;
        }
    }

    void displayPriorityGraph() {
        cout << "\n===== SUBJECT PRIORITY GRAPH =====\n";

        int rank = 1;
        for(auto &sub : subjects) {
            cout << rank++ << ". " << sub.name << " | ";

            for(int i = 0; i < sub.priority; i++) {
                cout << "#";
            }

            cout << " (" << sub.priority << ")" << endl;
        }
    }
    void showTreeGrowth() {
        cout << "\n🌱 Your Study Tree:\n";

        if(streak == 1)
            cout << "  .\n";
        else if(streak == 2)
            cout << "  .\n  |\n";
        else if(streak == 3)
            cout << "  .\n /|\\\n  |\n";
        else if(streak == 4)
            cout << "  .\n /|\\\n / \\\n";
        else if(streak >= 5)
            cout << "  🌳 FULL GROWN TREE 🌳\n";
    }
    void showAchievements() {
        if(streak == 3)
            cout << "🏆 Achievement: Consistency Starter!\n";
        else if(streak == 5)
            cout << "🏆 Achievement: Focus Master!\n";
        else if(streak == 10)
            cout << "🏆 Achievement: Study Legend!\n";
    }
    void focusSession(int choice) {
        if(choice < 1 || choice > subjects.size()) {
            cout << "Invalid subject number!\n";
            return;
        }

        Subject &sub = subjects[choice-1];
        cout << "\nStarting focus session for " << sub.name << "...\n";

        int timeInSeconds = 15; // demo 15 seconds
        for(int i = timeInSeconds; i > 0; i--) {
            cout << "Time left: " << i << " seconds\r";
            cout.flush();
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "\nSession complete!\n";

        streak++;
        saveStreak();

        cout << "🔥 Current Streak: " << streak << " days\n";

        showTreeGrowth();
        showAchievements();
    }

    void runDailySchedule() 
    {
        cout << "\n===== DAILY STUDY SCHEDULE =====\n";

        int totalPriority = 0;
        for(auto &sub : subjects) totalPriority += sub.priority;

        for(int day = 0; day < daysLeft; day++) 
        {
            cout << "\nDay " << day + 1 << " (Total Hours: " << dailyHours[day] << "):\n";

            for(auto &sub : subjects) 
            {
                double hours = (double(sub.priority) / totalPriority) * dailyHours[day];
                cout << sub.name << " -> " << hours << " hrs\n";
            }
        }
    }
};

int main() {
    StudyPlan plan;

    plan.loadStreak();
    plan.inputSubjects();
    plan.calculatePriorities();
    plan.sortByPriority();
    plan.allocateHours();
    plan.displayPlan();
    plan.displayPriorityGraph();

    int choice;
    cout << "\nSelect subject number to start focus: ";
    cin >> choice;
    plan.focusSession(choice);

    plan.runDailySchedule();

    return 0;
}