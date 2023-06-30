// GPA Calculator v2.0
// June 29th, 2023 - June 30th, 2023
// By: Sean Allgaier

#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

// Declaring functions
void menu();
void errorMessage();
float gradeCalculation(int courseCount, int currentSemester, vector<float> &totalTermHours, vector<float> &totalEarnedCredits);
float calculateCumulativeGPA(float cumulativeGPA, vector<float> termGPA, vector<float> &totalTermHours, vector<float> &totalEarnedCredits);
float verifyGradeInput(string courseGrade);
bool verifyGradeWeight(int creditHours);

//--------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    menu();
    cout << endl << "Ending..." << endl << endl;                        // Debug message to verify menu option functioned properly
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

void errorMessage()
{
    std::cin.clear();                                                   // Clears user input
    std::cin.ignore(256, '\n'); 
    cout << "Invalid input, please try again." << endl << endl;      
}

//--------------------------------------------------------------------------------------------------------------------------------------------

void menu()
{
	vector<float> termGPA;
    vector<float> totalGPA;
    vector<float> totalTermHours;
    vector<float> totalEarnedCredits;
    float cumulativeGPA = 0;


    // Menu displaying how grades are weighted 
    cout << endl
    //      0         1         2         3         4         5           
    //      012345678901234567890123456789012345678901234567890
        << "###################################################" << endl
        << setw(32)
        << "GPA Calculator" << endl
        << setw(33)
        << "By Sean Allgaier" << endl
        << "###################################################" << endl;

    semesterNumInput:
    int semesterCount;
    cout << "Please enter the number semesters to calculate: ";                 // Prompt user to input number of semesters
    std::cin >> semesterCount;
    // Loops until user makes a correct input
    while (cin.fail())
    {
        std::cin.clear();                                                       // Clears user input
        errorMessage();                                                         // Outputs error message
        std::cin.ignore(256, '\n');                                         
        goto semesterNumInput;
    }

    for (int i = 0; i < semesterCount; i++)
    {
        courseNumInput:
        int courseCount;
        cout << "Enter number of courses for semester #" << i+1 << ": ";        // Prompt user to input number of courses within each semester
        cin >> courseCount;
        // Loops until user makes a correct input
        while (cin.fail())
        {
            errorMessage();                                                     // Outputs error message                                        
            goto courseNumInput;
        }
        termGPA.push_back(gradeCalculation(courseCount, i, totalTermHours, totalEarnedCredits));
        cout << "Calculating semester gpa..." << endl;
        cout << fixed << setprecision(3);
        cout << "Semester #" << i+1 << " gpa = " << termGPA[i] << endl << endl;
    }

    cout << endl << endl << "Calculating cumulative gpa..." << endl;

    cout << endl << "Results: " << endl;

    for (int i = 0; i < semesterCount; i++)
    {
        cout << fixed << setprecision(3);
        cout << "Semester #" << i+1 << " gpa = " << termGPA[i] << endl;
    }

    
    cumulativeGPA = calculateCumulativeGPA(cumulativeGPA, termGPA, totalTermHours, totalEarnedCredits);
    cout << "Cumulative GPA = " << cumulativeGPA << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

float gradeCalculation(int courseCount, int currentSemester, vector<float> &totalTermHours, vector<float> &totalEarnedCredits)
{
    float gpa = 0, earnedGradeSum = 0, totalCreditSum = 0;
    cout << endl << "Semester #" << currentSemester+1 << " GPA calculation: " << endl;

    for (int i = 0; i < courseCount; i++)
    {
        courseGradeInput:
        string courseGrade;
        float creditHours = 0;

        cout << "Please enter the letter grade for course #" << i+1 << ": ";
        std::cin >> courseGrade;

        courseGrade[0] = toupper(courseGrade[0]);                                   // Forces only the first character of the user's grade to be capitalized 
        
        if (verifyGradeInput(courseGrade) == -1)
        {
            errorMessage();                                                         // Outputs error message
            goto courseGradeInput;
        }

        // Prompts user for credit hour weight for the courses 
        // && Verifies that user inputs the correct weight

        if (courseGrade != "P")
        {
            cout << "Credit hours for course #" << i+1 << ": ";
            cin >> creditHours;

            // Loops until user makes a correct input
            while (cin.fail())
            {
                errorMessage();                                                     // Outputs error message                                        
                goto courseGradeInput;
            }

            if (!verifyGradeWeight(creditHours))
            {
                errorMessage();                                                     // Outputs error message 
                goto courseGradeInput;
            }
        }
        else if (courseGrade == "P")
            creditHours = 0.0;


        confirmMessage:
        string confirm;
        cout << endl;
        cout << "Course #" << i+1 << ": " << endl;
        cout << "Earned Grade: " << courseGrade << endl;
        cout << "Credit Hours: " << creditHours << endl;
        cout << "Confirm (Y/N): ";
        cin >> confirm;

        if (confirm != "Y" && confirm != "N" && confirm != "y" && confirm != "n")
        {
            errorMessage();                                                       // Outputs error message 
            goto confirmMessage;
        }

        else if(confirm == "N" || confirm == "n")
        {
            goto courseGradeInput; 
        }

        cout << endl << endl;

        float actualGrade = verifyGradeInput(courseGrade);

        float courseGPA = 0;
        if (courseGrade != "P")
        {
            courseGPA = actualGrade * creditHours;
            earnedGradeSum += courseGPA;
            totalCreditSum += creditHours;
        }
        
    }

    gpa = earnedGradeSum/totalCreditSum;
    totalEarnedCredits.push_back(earnedGradeSum);
    totalTermHours.push_back(totalCreditSum);
    return gpa;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

float verifyGradeInput(string courseGrade)
{
    float earnedGrade;
    if (courseGrade == "A+") // || (stoi(courseGrade) >= 97))
    {
        earnedGrade = 4.0;
        return earnedGrade;
    }
    else if (courseGrade == "A") // || (stoi(courseGrade) < 97 && stoi(courseGrade) >= 93))
    {
        earnedGrade = 4.0;
        return earnedGrade;
    }
    else if (courseGrade == "A-") // || (stoi(courseGrade) < 93 && stoi(courseGrade) >= 90))
    {
        earnedGrade = 3.7;
        return earnedGrade;
    }
    else if (courseGrade == "B+") // || (stoi(courseGrade) <= 89 && stoi(courseGrade) >= 87))
    {
        earnedGrade = 3.3;
        return earnedGrade;
    }
    else if (courseGrade == "B") // || (stoi(courseGrade) < 87 && stoi(courseGrade) >= 83))
    {
        earnedGrade = 3.0;
        return earnedGrade;
    }
    else if (courseGrade == "B-") //|| (stoi(courseGrade) < 83 && stoi(courseGrade) >= 80))
    {
        earnedGrade = 2.7;
        return earnedGrade;
    }
    else if (courseGrade == "C+") // || (stoi(courseGrade) < 80 && stoi(courseGrade) >= 77))
    {
        earnedGrade = 2.3;
        return earnedGrade;
    }
    else if (courseGrade == "C") // || (stoi(courseGrade) < 77 && stoi(courseGrade) >= 73))
    {
        earnedGrade = 2.0;
        return earnedGrade;
    }
    else if (courseGrade == "C-") // || (stoi(courseGrade) < 73 && stoi(courseGrade) >= 70))
    {
        earnedGrade = 1.7;
        return earnedGrade;
    }
    else if (courseGrade == "D+") // || (stoi(courseGrade) < 70 && stoi(courseGrade) >= 67))
    {
        earnedGrade = 1.3;
        return earnedGrade;
    }
    else if (courseGrade == "D") // || (stoi(courseGrade) < 67 && stoi(courseGrade) >= 63))
    {
        earnedGrade = 1.0;
        return earnedGrade;
    }
    else if (courseGrade == "D-") // || (stoi(courseGrade) < 63 && stoi(courseGrade) >= 60))
    {
        earnedGrade = 0.7;
        return earnedGrade;
    }
    else if (courseGrade == "F") // || (stoi(courseGrade) < 59))
    {
        earnedGrade = 0.0;
        return earnedGrade;
    }
    else if (courseGrade == "P")
    {
        earnedGrade = 0.0;
        return earnedGrade;
    }
    else
        return -1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

bool verifyGradeWeight(int creditHours)
{
    if (creditHours == 4 || creditHours == 3 || creditHours == 2 || creditHours == 1)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

float calculateCumulativeGPA(float cumulativeGPA, vector<float> termGPA, vector<float> &totalTermHours, vector<float> &totalEarnedCredits)
{
    float sumTakenHours = 0, sumEarnedCredits = 0;
    for (int i = 0; i < totalTermHours.size(); i++)
    {
        sumTakenHours += totalTermHours[i];
    }
    
    for (int i = 0; i < totalEarnedCredits.size(); i++)
    {
        sumEarnedCredits += totalEarnedCredits[i];
    }

    cumulativeGPA = sumEarnedCredits / sumTakenHours;

    return cumulativeGPA;
}

//--------------------------------------------------------------------------------------------------------------------------------------------