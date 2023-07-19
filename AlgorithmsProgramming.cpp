/*
*
* Courtney Lee 
* COMP 3270 Programming Assignment
*
*/

#include <chrono> 
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//function for algorithm 1
int algorithm_1 (int inputArray[], int inputSize) {
    int maxSoFar = 0;
    int sum = 0;
    
    for (int L = 0; L < inputSize; L++) {
        for (int U = L; U < inputSize; U++) {
            sum = 0;
            for (int I = L; I <= U; I++) {
                sum += inputArray[I];
            }
            maxSoFar = max(maxSoFar, sum);
        }
    }
    return maxSoFar;
}


//function for algorithm 2
int algorithm_2 (int inputArray[], int inputSize) {
    int maxSoFar = 0;
    int sum = 0;

    for (int L = 0; L < inputSize; L++) {
        sum =0; 
        for (int U = L; U < inputSize; U++) {
            sum += inputArray[U];
            maxSoFar = max(maxSoFar,sum);
        }
    }
    return maxSoFar; 
}

//function for algorithm 3
int algorithm_3 (int inputArray[], int left, int right) {
    if (left > right) {
        return 0;
    }
    if (left == right) {
        return max(0, inputArray[left]);
    }

    int middle = (left + right) / 2; 
    int sum = 0;
    int maxToLeft = 0;

    for (int I = middle; I >= left; I--) {
        sum += inputArray[I];
        maxToLeft = max(maxToLeft, sum);
    }

    sum = 0;
    int maxToRight = 0;
    for (int I = middle + 1; I <= right; I++) {
        sum += inputArray[I];
        maxToRight = max(maxToRight, sum);
    }

    int maxCrossing = maxToLeft + maxToRight; 
    int maxInA = algorithm_3(inputArray, left, middle);
    int maxInB = algorithm_3(inputArray, middle + 1, right);
    int tempMax = max(maxCrossing, maxInA);
    return max(tempMax, maxInB);

}

//function for algorithm 4
int algorithm_4(int inputArray[], int inputSize) {
    int maxSoFar = 0;
    int maxEndingHere = 0;

    for (int I = 0; I <inputSize; I++) {
        maxEndingHere = max(0, maxEndingHere + inputArray[I]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

int main() {
    //create the 4 algorithms 
    int algorithm_1(int inputArray[], int inputSize);
    int algorithm_2(int inputArray[], int inputSize);
    int algorithm_3(int inputArray[], int left, int right);
    int algorithm_4(int inputArray[], int inputSize);

    //Open input file to read
    ifstream inputFile;
    inputFile.open("phw_input.txt");

    //error message if file cant be found
    if (!inputFile.is_open()) {
        cout << "File could not be opened.";
        return 1;
    }

    //read in values from input file and put values in array
    int inputValue;
    int fileArray[10];

    for (int i = 0; i < 10; i++) {
        inputFile >> inputValue;
        //ignore commas
        inputFile.ignore (1, ',');
        fileArray[i] = inputValue;
    }
    inputFile.close();

    int answersArray[4];
    int size = sizeof(fileArray)/sizeof(fileArray[0]);

    //call the algorithms and store answers in the array
    answersArray[0] = algorithm_1(fileArray, size);
    answersArray[1] = algorithm_2(fileArray, size);
    answersArray[2] = algorithm_3(fileArray, 0, size-1);
    answersArray[3] = algorithm_4(fileArray, size);

    //answers should all be the same
    cout 
    << "algorithm-1: "<< answersArray[0] << endl
    << "algorithm-2: "<< answersArray[1] << endl
    << "algorithm-3: "<< answersArray[2] << endl
    << "algorithm-4: "<< answersArray[3] << endl; 

    double outputArray[19][8]; //19x8 matrix
    int result = 0;
    int calcTime;
    double totalTime;
    int seqSize; 

    //run for each sequence sizes that goesfrom 10, incrementing by 5 until 100
    for (int seqNum = 2; seqNum <= 20; seqNum ++) {
        seqSize = seqNum*5;
        int sequence[seqSize];
        for (int i = 0; i < seqSize; i++) {
        //create random numbers between -20 and 20 to populate each array
            sequence [i] = rand() %41 - 20; 
        }

        /*
        * Algorithm 1
        * 
        * for particular syntax use of chrono: 
        * https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
        * 
        */ 
        totalTime = 0;
        //start clock
        auto start = chrono::high_resolution_clock::now();
        //run algorithm 1 3000 times
        for (int i = 0; i < 3000; i++) {
            result = algorithm_1(sequence, seqSize); 
        }
        //stop clock
        auto finish = chrono::high_resolution_clock::now();
        //calculate total time for this algorithm 
        totalTime = chrono::duration_cast<chrono::microseconds>(finish-start).count();

        //take average and store in the output array
        outputArray [seqNum - 2] [0] = double(totalTime/3000);


        /*
        * Algorithm 2
        */ 
        totalTime = 0;
        //start clock
        start = chrono::high_resolution_clock::now();
        //run algorithm 2 1000 times
        for (int i = 0; i < 3000; i++) {
            result = algorithm_2(sequence, seqSize); 
        }
        //stop clock
        finish = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::microseconds>(finish-start).count();

        //take average and store in the output array
        outputArray [seqNum - 2] [1] = double(totalTime/3000);


        /*
        * Algorithm 3
        */ 
        totalTime = 0;
        //start clock
        start = chrono::high_resolution_clock::now();
        //run algorithm 3 3000 times
        for (int i = 0; i < 3000; i++) {
            result = algorithm_3(sequence, 0, seqSize); 
        }
        //stop clock
        finish = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::microseconds>(finish-start).count();

        //take average and store in the output array
        outputArray [seqNum - 2] [2] = double(totalTime/3000);

        /*
        * Algorithm 4
        */ 
        totalTime = 0;
        //start clock
        start = chrono::high_resolution_clock::now();
        //run algorithm 4 3000 times
        for (int i = 0; i < 3000; i++) {
            result = algorithm_4(sequence, seqSize); 
        }
        //stop clock
        finish = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::microseconds>(finish-start).count();

        //take average and store in the output array
        outputArray [seqNum - 2] [3] = double(totalTime/3000);

        calcTime = 0;
        for (int i = 1; i <= seqSize; i++) {
            calcTime = (i+1)*(i+2)/2 - 1 + i*3*(i+1);
        }

        //calculate T(n) -> formulas derived from homework portion of programming assignment seqSize = n
        outputArray[seqNum-2][4] = double(calcTime + 3 + seqSize + (seqSize+1)*(seqSize+2)/2 + 5*seqSize*(seqSize+1)) / double(250);
        outputArray[seqNum-2][5] = double(4 + seqSize*2 + (seqSize+1)*(seqSize+2)/2 + 15*seqSize*(seqSize+2)/2) / double(5000);
        outputArray[seqNum-2][6] = double((log(seqSize)/log(2)-1)*seqSize*16 + 40*seqSize + 9*log(seqSize)/log(2) - 80) / double(5000);
        outputArray[seqNum-2][7] = double(21*seqSize + 5) / double(5000);
    }

    //print to ouput file
    ofstream printFile; 
    printFile.open("courtneyLee_phw_output.txt");
    printFile << "algorithm-1, algorithm-2, algorithm-3, algorithm-4, T1(n), T2(n), T3(n), T4(n)" << endl;

    //loop through matrix to print values in correct locations 
    for(int i = 0; i <= 18; i++) {
        for (int j = 0; j <= 7; j++) {
            printFile << outputArray[i][j] << ",";
        }
        printFile << endl;
    }
    printFile.close();
}
