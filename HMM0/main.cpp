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
int obsRow;
int obsCol;
int inRow;
int inCol;

int print(int row, int col, vector<vector<float>> matrix){
        for (int l=0; l<row; ++l){
            for(int m=0;m<col;++m){
            cout << matrix[l][m] <<" ";
            
        }
    }
    
}

vector<vector<float>> multiply(int row1, vector<vector<float>> matrix1, int row2, int col2, vector<vector<float>> matrix2){

    vector<vector<float>> resMatrix(row1, std::vector<float>(col2));
    for(int i=0; i<row1; ++i){
        for(int j=0;j<col2;++j){           
            for(int k=0;k<row2;++k){
                resMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

   // print(row1, col2, resMatrix);
    return resMatrix;
    
}


vector<vector<float>> matrix(int row, int col, vector<float>& val){
    vector<vector<float>> matrix(row, std::vector<float>(col));
    int k=0;
    for (int i=0; i<row; ++i){
        for(int j=0;j<col;++j){
            matrix[i][j]=val[k];
            ++k;
        }
    }
    //print(row, col, matrix);
    return matrix;
}

int read(std::istream&){
    std::vector<float> transitions;
    std::vector<float> observations;
    std::vector<float> initial;
    string newline;
    std::cin >> tranRow;
    std::cin >> tranCol;

    for (int i=0;i<tranRow*tranCol;++i){
        float value;
        std::cin >> value;
        transitions.push_back(value);
    }
    cin >> obsRow;
    cin >> obsCol;
    for (int k=0;k<obsRow*obsCol;++k){
        float value;
        std::cin >> value;
        observations.push_back(value);
    }
    cin >> inRow;
    cin >> inCol;
    for (int l=0;l<inRow*inCol;++l){
        float value;
        std::cin >> value;
        initial.push_back(value);
    }
    
    vector<vector<float>> tranMatrix = matrix(tranRow, tranCol, transitions);
    vector<vector<float>> obsMatrix = matrix(obsRow, obsCol, observations);
    vector<vector<float>> inMatrix = matrix(inRow, inCol, initial);
    //print(tranRow, tranCol, tranMatrix);
    
    vector<vector<float>> mul1 = multiply(inRow, inMatrix, tranRow, tranCol, tranMatrix);
    vector<vector<float>> result = multiply(inRow, mul1, obsRow, obsCol, obsMatrix);
    cout << inRow << " "<< obsCol << " ";
    print(inRow, obsCol, result);
}

int main(int argc, char** argv) {
    read(std::cin);
    return 0;
}

