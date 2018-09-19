/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest1.cpp
 * Author: hanna
 *
 * Created on September 4, 2018, 1:04 PM
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include "main.h"
//#include "HMM1.h"
//#include "HMM2.h"
#include "HMM3.h"
using namespace std;

/*
 * Simple C++ Test Suite
 */

void test1() {
    main();
    //read3(std::cin);
    
}

void test2() {
    std::cout << "newsimpletest1 test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest1) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest1" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest1)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest1)" << std::endl;

   
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

