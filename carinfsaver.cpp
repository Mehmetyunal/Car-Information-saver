#include <bits/stdc++.h> // Includes all standard C++ libraries
using namespace std;     // Use the standard namespace

ofstream file; // Global file stream for writing cars

class Cars // Defines a class to represent a car
{
public:
    string brand; // Car brand
    int ps;       // Horsepower

    Cars(string carbrand, int carps) // Constructor
    {
        brand = carbrand; // Sets the car brand
        ps = carps;       // Sets the car horsepower
    }

    void printcartofile() // Prints car info to the global file
    {
        file << brand << " : " << ps << endl;
    }
};

int main()
{
    while (true) // Infinite menu loop
    {
        vector<Cars> carslist; // Temporary list to hold cars before writing to file
        string input;
        cout << "What do you want to do? (1= add new cars / 2= see the existing cars / 3= delete car): " << endl;
        cin >> input; // User chooses menu option

        if (input == "1") // Option 1: Add new cars
        {
            int howmany = 0;
            cout << "How many cars do you want to add: " << endl;
            cin >> howmany; // Number of cars to add

            for (int i = 1; i <= howmany; i++) // Loop for each car
            {
                int inputps = 0;
                string inputbrand = "";
                cout << "Please enter the brand  of the  " << i << ". car: " << endl;
                cin >> inputbrand;                                                              // Get brand from user
                transform(inputbrand.begin(), inputbrand.end(), inputbrand.begin(), ::toupper); // Convert to uppercase
                cout << "Please enter the hs of the " << i << ". car: " << endl;
                cin >> inputps; // Get horsepower

                Cars c(inputbrand, inputps); // Create a car object
                carslist.push_back(c);       // Add to temporary list
            }

            file.open("cars.txt", ios::app); // Open file in append mode
            for (auto cars : carslist)       // Loop through list
            {
                cars.printcartofile(); // Write car to file
            }
            file.close(); // Close file
        }
        else if (input == "2") // Option 2: View existing cars
        {
            ifstream file("cars.txt"); // Open file for reading

            if (file.is_open()) // checks if the file is open
            {
                while (!file.eof()) // Loop until end-of-file
                {
                    string word;
                    getline(file, word);  // Read a line
                    cout << word << endl; // Print the line
                }
                file.close(); // Close file
            }
            else
                cout << "Your first need to add cars." << endl;
        }
        else if (input == "3") // Option 3: Delete a car
        {
            fstream file;                              // Declare a file stream for reading/writing
            file.open("cars.txt", ios::out | ios::in); // Open original file
            fstream temp;
            temp.open("temp.txt", ios::out | ios::app | ios::in); // Open temporary file

            if (file.is_open()) // checks if the file is open
            {
                cout << "Which car do you want to delete? ";
                string deletecar = "";
                cin >> deletecar;                                                            // Get brand to delete
                transform(deletecar.begin(), deletecar.end(), deletecar.begin(), ::toupper); // Convert to uppercase

                string word;
                while (file >> word) // Read file word by word
                {
                    string deleteline;
                    getline(file, deleteline); // Read the rest of the line
                    if (word == deletecar)     // If word matches deletion target
                    {
                        continue; // Skip writing to temp
                    }
                    temp << word << deleteline << endl; // Otherwise, write to temp
                }

                temp.close();
                temp.open("temp.txt", ios::in); // Reopen temp file for reading
                file.close();
                file.open("cars.txt", ios::in); // Reopen original file for reading

                bool same = false; // Flag for comparison
                string same1, same2;
                file.seekg(0, ios::beg); // Move read pointer to beginning
                temp.seekg(0, ios::beg);

                while (!file.eof()) // Compare files line by line
                {
                    getline(file, same1);
                    getline(temp, same2);
                    if (same1 == same2) // If lines match
                    {
                        same = true;
                    }
                    else // If any line differs
                    {
                        same = false;
                        break; // Stop comparison
                    }
                }

                file.close(); // Close original file
                temp.close(); // Close temp file

                remove("cars.txt");             // Delete original file
                rename("temp.txt", "cars.txt"); // Rename temp to original

                if (same == true) // If files were identical
                {
                    cout << "This car wasn't added." << endl;
                }
            }
            else
                cout << "Your first need to add cars." << endl;
        }
        else
            cout << "Please enter 1, 2 or 3." << endl; // Invalid menu option
    }
}
