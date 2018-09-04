/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hanna
 *
 * Created on September 4, 2018, 12:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
int input = 3;
int tranRow;
int tranCol;
int emRow;
int emCol;
int inRow;
int inCol;


int read(std::istream&){
    std::vector<float> transitions;
    std::vector<float> observations;
    std::vector<float> initial;
    std::cin >> tranRow;
    std::cin >> tranCol;
    std::cout << " tranRow: " << tranRow << " \n";
    std::cout << " tranCol: " << tranCol << " \n";
    for (int i=0;i<tranRow*tranCol;++i){
        float value;
        std::cin >> value;
        transitions.push_back(value);
    }
    std::cout << "transitions contents: ";
    for (int j=0; j<transitions.size(); ++j){
        std::string res = std::to_string(transitions[j]);
       std::cout << res << " ";
    }
  
}
int main(int argc, char** argv) {

    return 0;
}

