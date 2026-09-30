// RunnersMarathon2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

const int MAX_RUNNERS = 6;
const int DAYS = 7;
const int COL = 10;

struct Runners
{
    std::string name;
    double miles[DAYS];
    double total;
    double average;
};
int readRunnerData(Runners runner[])
{
    int accessable = 0;
    std::ifstream file("runners.txt");

    if (!file.is_open()) {
        std::cerr << "error opening file";

    }
    std::string line;
    std::string word;

    // i = line read
    // j = string read

    for (int i = 0; std::getline(file, line) && i < MAX_RUNNERS; i++) {
        std::istringstream stream(line);
        for (int j = 0; stream >> word; j++) {
            if (j == 0) {
                runner[i].name = word;
            }
            else {
                runner[i].miles[j-1] = std::stod(word);
            }
        }
        accessable++;
        if (i == (MAX_RUNNERS - 1)) {
            std::cout << "Maximum array size reached, Closing file... \n";
        }
    }
    
    file.close();
    return accessable;
}
void calculateTotalAndAverage(Runners runner[], int accessable)
{
    double total = 0;
    for (int i = 0; i < accessable; i++) {
        for (int j = 0; j < DAYS; j++) {
            total += runner[i].miles[j];
        }
        runner[i].total = total;
        runner[i].average = total / DAYS;
        total = 0;
    }
}
void printTable(const Runners runner[], int accessable)
{
    std::string header[COL] = { "Runner Name", "Day 1", "Day 2" , "Day 3" , "Day 4" , "Day 5" , "Day 6" , "Day 7", "Total", "Average" };
    std::cout << std::left;


    for (int i = 0; i < COL; i++) {
        if (i == 0) {
            std::cout << std::setw(15) << header[i];
        }
        else {
            std::cout << std::setw(8) << header[i];
        }
    }

    std::cout << "\n";
    std::cout << "--------------------------------------------------------------------------------------\n";

    for (int i = 0; i < accessable; i++) {
        std::cout << std::setw(15) << runner[i].name;
        for (int j = 0; j < DAYS; j++) {
            std::cout << std::setw(8) << runner[i].miles[j];
        }
        std::cout << std::setw(8) << runner[i].total;
        std::cout << std::setw(8) << runner[i].average;
        std::cout << "\n";
    }
}
int main()
{
    Runners runner[MAX_RUNNERS];
    int ACCESSABLE_RUNNERS = readRunnerData(runner);
    calculateTotalAndAverage(runner, ACCESSABLE_RUNNERS);
    printTable(runner, ACCESSABLE_RUNNERS);
    return 0;

}


