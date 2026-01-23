#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomBetween(int low, int high)
{
    return low + rand() % (high - low + 1);
}

int main()
{
    srand(time(0));

    const int INTERSECTIONS = 4;
    const int CARS_PASSED = 5;

    static int NS_queue[INTERSECTIONS];
    static int EW_queue[INTERSECTIONS];
    static string emergency[INTERSECTIONS];
    string action[INTERSECTIONS];

    static bool initialized = false;

    if (!initialized)
    {
        for (int i = 0; i < INTERSECTIONS; i++)
        {
            NS_queue[i] = randomBetween(6, 10);
            EW_queue[i] = randomBetween(6, 10);

            int chance = randomBetween(1, 100);
            if (chance >= 80) emergency[i] = "NS";
            else if (chance >= 60) emergency[i] = "EW";
            else emergency[i] = "NONE";
        }
        initialized = true;
    }

    ofstream stateFile("state.csv");
    for (int i = 0; i < INTERSECTIONS; i++)
    {
        stateFile << NS_queue[i] << ","
                  << EW_queue[i] << ","
                  << emergency[i] << ",";

        if (i < INTERSECTIONS - 1)
            stateFile << NS_queue[i + 1];
        else
            stateFile << 0;

        if (i != INTERSECTIONS - 1)
            stateFile << "\n";
    }
    stateFile.close();

    ifstream actionFile("action.txt");
    for (int i = 0; i < INTERSECTIONS; i++)
    {
        if (actionFile.is_open() && !(actionFile >> action[i]))
            action[i] = "NONE";
    }
    actionFile.close();

    int movedNS[INTERSECTIONS] = {0};

    for (int i = 0; i < INTERSECTIONS; i++)
    {
        if (action[i] == "NS")
        {
            int removed = min(CARS_PASSED, NS_queue[i]);
            NS_queue[i] -= removed;
            movedNS[i] = removed;
        }
        else if (action[i] == "EW")
        {
            int removed = min(CARS_PASSED, EW_queue[i]);
            EW_queue[i] -= removed;
        }
    }

    
    for (int i = 0; i < INTERSECTIONS - 1; i++)
        NS_queue[i + 1] += movedNS[i];

    NS_queue[0] += randomBetween(2, 4);

    for (int i = 0; i < INTERSECTIONS; i++)
    {
        if (randomBetween(1, 100) <= 20)
            EW_queue[i] += 1;
    }

    for (int i = 0; i < INTERSECTIONS; i++)
    {
        int chance = randomBetween(1, 100);
        if (chance >= 80) emergency[i] = "NS";
        else if (chance >= 60) emergency[i] = "EW";
        else emergency[i] = "NONE";
    }

    ofstream nextState("state.csv");
    for (int i = 0; i < INTERSECTIONS; i++)
    {
        nextState << NS_queue[i] << ","
                  << EW_queue[i] << ","
                  << emergency[i] << ",";

        if (i < INTERSECTIONS - 1)
            nextState << NS_queue[i + 1];
        else
            nextState << 0;

        if (i != INTERSECTIONS - 1)
            nextState << "\n";
    }
    nextState.close();

    return 0;
}
