#include <iostream>
#include <string>
#include <algorithm>
#include<iomanip>
using namespace std;

int main() {
    cout << "********************************" << endl;
    cout << "         TEST MARKER            " << endl;
    cout << "********************************" << endl;

    int num_students, choice, functionality;
    char students_grade, again;
    float percentage;
    // Loop to ensure valid input for number of students
    
    cout << "\nEnter the number of students: ";
    cin >> num_students;
    if (cin.fail()|| num_students <= 0){
        cout << "Invalid input,Please restart the program and enter a positive number.";
        cin.clear();
    }else{
    // Array of correct answers for comparison
    string correct_answers[20] = {"TRUE", "TRUE", "FALSE", "TRUE", "FALSE",
                                  "A", "B", "C", "D", "A",
                                  "B", "C", "D", "A", "B",
                                  "VERB TO BE", "WILLIAM SHAKESPEARE", "VERB", "SPEAKING", "AMERICA"};
    
    // Dynamic arrays to store student answers and scores
    string** students = new string*[num_students];
    int* total_scores = new int[num_students];
    char* grades = new char[num_students];

    for (int i = 0; i < num_students; ++i) {
        students[i] = new string[21];
    }
    
    // Input student IDs and their answers
    for (int i = 0; i < num_students; i++) {
        cout << "Enter student ID: ";
        cin >> students[i][0];
        cin.ignore();
        for (int j = 1; j <= 20; j++) {
            cout << "Enter answer for question " << j << ": ";
            getline(cin, students[i][j]);   
            transform(students[i][j].begin(), students[i][j].end(), students[i][j].begin(), ::toupper);  // Convert each answer to uppercase
        }
    }

    // Calculate total scores and grades
    for (int i = 0; i < num_students; i++) {
        int total_score = 0;
        for (int j = 1; j <= 20; j++) {
            if (students[i][j] == correct_answers[j-1]) {
                total_score += 2; // Correct answer: +2 points
            } else if (students[i][j].empty()) {
                total_score += 0; // No answer: 0 points
            } else {
                total_score -= 1; // Incorrect answer: -1 point
            }
        }

        total_scores[i] = total_score;
        
        // Convert total score to percentage and assign grades
        percentage = total_score * 2.5;
        if (percentage >= 90 && percentage <= 100) {
            grades[i] = 'A';
        } else if (percentage >= 80 && percentage < 90) {
            grades[i] = 'B';
        } else if (percentage >= 70 && percentage < 80) {
            grades[i] = 'C';
        } else if (percentage >= 60 && percentage < 70) {
            grades[i] = 'D';
        } else {
            grades[i] = 'F';
        }
    }

    cout << endl;
    cout << left << setw(10) << "ID" 
         << setw(20) << "Total score" 
         << setw(10) << "Grade" 
         << endl;
    cout << "------------------------------------" << endl;
  
  // Print student IDs, total scores, and grades in tabular form
    for (int i = 0; i < num_students; i++) {
        cout << left << setw(10) << students[i][0]
             << setw(20) << total_scores[i]
             << setw(10) << grades[i]
             << endl;
    }

    // Bubble sort to rank students based on total scores
    for (int i = 0; i < num_students - 1; ++i) {
        for (int j = 0; j < num_students - i - 1; ++j) {
            if (total_scores[j] < total_scores[j + 1]) { // Descending order
                // Swap marks
                int tempMarks = total_scores[j];
                total_scores[j] = total_scores[j + 1];
                total_scores[j + 1] = tempMarks;

                // Swap student IDs
                string* tempStudent = students[j];
                students[j] = students[j + 1];
                students[j + 1] = tempStudent;

                // Swap grades
                char tempGrade = grades[j];
                grades[j] = grades[j + 1];
                grades[j + 1] = tempGrade;
            }
        }
    }

    do {
        // Switch cases for functionalities
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Which functionality do you want: " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\n1. See top 5 or top 10 students " << "\n2. Search for a student " << endl;
        cout<<"~~~~> ";
        cin >> functionality; 
          

        switch (functionality) {
            case 1: {
                // Display top students based on user choice
                cout << "Enter 5 or 10: ";
                cin >> choice;

                if (choice != 5 && choice != 10) {
                    cout << "Invalid choice. Please restart the program and enter either 5 or 10." << endl;
                    return 1;
                }

                // Display top students
                cout << "\nTop " << choice << " Students:" << endl;
                for (int i = 0; i < choice && i < num_students; ++i) {
                    cout << i + 1 << ". " << "Student ID: " << students[i][0] << " - " << total_scores[i] << " marks - Grade: " << grades[i] << endl;
                }
                break;
            }

            case 2: {
                // Search for student by ID and display their information
                cout << "Enter the ID of the student you want to check: "; 
                string student_id; 
                cin >> student_id;
                bool student_found = false; 
                for (int i = 0; i < num_students; i++) { 
                    if (students[i][0] == student_id) { 
                        student_found = true; 
                        cout << "- - - - - - - - - -"<< endl 
                             << "\nStudent ID: " << student_id 
                             << "\nTotal Score: " << total_scores[i] 
                             << "\nAnswers: "; 
                        for (int j = 1; j <= 20; j++) { 
                            cout << j<<"."<<students[i][j] << " ";
                        } 
                        cout << "\nGrade: " << grades[i] << endl << "- - - - - - - - - - " << endl; 
                        break;
                    }
                }
                if (!student_found) { 
                    cout << "Student ID: " << student_id << " not found." << endl; 
                }
                break;
            }

            default: 
                cout << "Invalid functionality. Please try again." << endl;
        }

        cout << endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl 
                    << "Do you want to continue? If yes, enter Y "<< endl 
                    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        
        cout<<"~~~~~> ";
        
        cin >> again;

    } while (again == 'y' || again == 'Y');  

    // Free dynamically allocated memory
    for (int i = 0; i < num_students; ++i) {
        delete[] students[i];
    }
    delete[] students;
    delete[] total_scores;
    delete[] grades;

    cout << "\n********************************" << endl;
    cout << "#          THANK YOU!           #" << endl;
    cout << "********************************" << endl;
    }  
    return 0;
}
