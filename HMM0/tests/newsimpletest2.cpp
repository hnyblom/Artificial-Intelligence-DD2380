/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest2.cpp
 * Author: hanna
 *
 * Created on September 19, 2018, 11:07 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

int print(vector<vector<double> > matrix);

void testPrint() {
    vector<vector<double> > matrix;
    int result = print(matrix);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testPrint (newsimpletest2) message=error message sample" << std::endl;
    }
}

vector<vector<double> > getMatrix(int row, int col, vector<double>& val);

void testGetMatrix() {
    int row;
    int col;
    vector<double>& val;
    vector<vector<double> > result = getMatrix(row, col, val);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetMatrix (newsimpletest2) message=error message sample" << std::endl;
    }
}

int printResult(vector<vector<double> > tranMatrix, vector<vector<double> > obsmatrix);

void testPrintResult() {
    vector<vector<double> > tranMatrix;
    vector<vector<double> > obsmatrix;
    int result = printResult(tranMatrix, obsmatrix);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testPrintResult (newsimpletest2) message=error message sample" << std::endl;
    }
}

int readMatrices();

void testReadMatrices() {
    int result = readMatrices();
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testReadMatrices (newsimpletest2) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest2" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testPrint (newsimpletest2)" << std::endl;
    testPrint();
    std::cout << "%TEST_FINISHED% time=0 testPrint (newsimpletest2)" << std::endl;

    std::cout << "%TEST_STARTED% testGetMatrix (newsimpletest2)" << std::endl;
    testGetMatrix();
    std::cout << "%TEST_FINISHED% time=0 testGetMatrix (newsimpletest2)" << std::endl;

    std::cout << "%TEST_STARTED% testPrintResult (newsimpletest2)" << std::endl;
    testPrintResult();
    std::cout << "%TEST_FINISHED% time=0 testPrintResult (newsimpletest2)" << std::endl;

    std::cout << "%TEST_STARTED% testReadMatrices (newsimpletest2)" << std::endl;
    testReadMatrices();
    std::cout << "%TEST_FINISHED% time=0 testReadMatrices (newsimpletest2)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

