/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HMM1.cpp
 * Author: hanna
 * 
 * Created on September 4, 2018, 7:51 PM
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
            cout << "\n";
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


vector<vector<float>> getMatrix(int row, int col, vector<float>& val){
    vector<vector<float>> resMatrix(row, std::vector<float>(col));
    int k=0;
    for (int i=0; i<row; ++i){
        for(int j=0;j<col;++j){
            resMatrix[i][j]=val[k];
            ++k;
        }
    }
    //print(row, col, matrix);
    return resMatrix;
}

vector<vector<float>> getCol(int rows, int obs, vector<vector<float>> matrix){
    vector<vector<float>> result(rows, std::vector<float>(1));

    for(int i=0;i<rows;++i){
        result[i][1] += matrix[i][obs];
        cout << matrix[i][obs] <<" ";
        cout << result[i][1]<<" ";
    }
   // print(rows,1,result);
    return result;
}

float sum(int obs, vector<vector<float>> matrix){
    float resSum;
    for(int i=0;i<obs;++i){
        resSum += matrix[i][1];
    }
    return resSum;
}

int read2(std::istream&){
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
    
    vector<vector<float>> tranMatrix = getMatrix(tranRow, tranCol, transitions);
    vector<vector<float>> obsMatrix = getMatrix(obsRow, obsCol, observations);
    vector<vector<float>> inMatrix = getMatrix(inRow, inCol, initial);
    //print(tranRow, tranCol, tranMatrix);
    
    int nrObs;
    int obs;
    cin >> nrObs;
    cin >> obs;
    vector<vector<float>> gottenCol = getCol(obsRow, obs, obsMatrix);
    vector<vector<float>> tempRes = multiply(nrObs, gottenCol, inRow, inCol, inMatrix);
    print(nrObs, inCol, tempRes);
//    vector<vector<float>> mult2;
//    for(int m=0;m<obs-1;++m){
//        cin>>obs;
//         vector<vector<float>> mult1 = multiply(nrObs, tempRes, tranRow,tranCol,tranMatrix);
//         mult2 = multiply(nrObs, getCol(obsRow, obs, obsMatrix), nrObs, 1, mult1);
//         tempRes = mult2;        
//    } 
    //cout<< "SUMMM!: " << sum(nrObs, mult2);
    
    //vector<vector<float>> mul1 = multiply(inRow, inMatrix, tranRow, tranCol, tranMatrix);
    //vector<vector<float>> result = multiply(inRow, mul1, obsRow, obsCol, obsMatrix);
    //cout << inRow << " "<< obsCol << " ";
    //print(inRow, obsCol, result);
}

int main(int argc, char** argv) {
    read2(std::cin);
    return 0;
}

