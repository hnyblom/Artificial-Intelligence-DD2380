/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HMM1.cpp
 * Author: Hanna & Nicole
 * 
 * Created on September 4, 2018, 7:51 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;

int input = 3;
int tranRow;
int tranCol;
int obsRow;
int obsCol;
int inRow;
int inCol;
vector<vector<float> > stateResMatrix;
int obsCounter = 0;

int print(vector<vector<float> > matrix){
    int row = matrix.size();
    int col = matrix[0].size();
    for (int l=0; l<row; ++l){
        for(int m=0; m<col;++m){
            cout << matrix[l][m] <<" ";
        }
        if(col == 0){
            cout << matrix[l][0] <<" ";
        }
        cout << "\n";
    }
    return 0;
}

vector<vector<float> > elemMultiply(vector<vector<float> > matrix1, vector<vector<float> > matrix2){
    if(matrix1.size() != matrix2.size()){
        cout << "------- ERROR different matrix sizes elemMultiply";
    }

    vector<vector<float> > resMatrix(matrix1.size(), std::vector<float>(1));
    for(int i=0; i < matrix1.size(); ++i){
        resMatrix[i][0] += matrix1[i][0] * matrix2[i][0];
    }
    return resMatrix;
    
}


//get one column from a matrix, 
vector<vector<float> > getCol(int obs, vector<vector<float> > matrix){
    int rows = matrix.size();
    vector<vector<float> > result(rows, std::vector<float>(1));
    for(int i=0;i<rows;++i){
        result[i][0] += matrix[i][obs];
    }
    return result;
}

float sum(vector<vector<float> > matrix){
    float resSum = 0;
    int rows = matrix.size();

    for(int i=0; i<rows; ++i){
        resSum += matrix[i][0];
    }
    return resSum;
}


vector<vector<float> > multiply(vector<vector<float> > matrix1, vector<vector<float> > matrix2){
    int row1 = matrix1.size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    //elementärmultiplicera ihop column med matrix 2 sedan summera
    vector<vector<float> > resMatrix(row1, std::vector<float>(1));

    for (int i = 0; i < row2; ++i){
        vector<vector<float> > column = getCol(i, matrix1);
        vector<vector<float> > multi = elemMultiply(column, matrix2);
        float summ = sum(multi);
        resMatrix[i][0] += summ;
    }
    return resMatrix;
    
}


vector<vector<float> > getMatrix(int row, int col, vector<float>& val){
    vector<vector<float> > resMatrix(row, std::vector<float>(col));
    int k=0;
    for (int i=0; i<row; ++i){
        for(int j=0;j<col;++j){
            resMatrix[i][j]=val[k];
            ++k;
        }
    }
    return resMatrix;
}

vector<vector<float> > getMax(vector<vector<float> >  mat){
    vector<vector<float> > resMat(mat.size(), std::vector<float>(1));
    float temp = 0;
    int index = 0;
    for(int i=0; i<mat.size();++i){
        for(int j=0;j<mat[0].size();++j){
            if(mat[i][j]>temp){
                temp = mat[i][j];
                index = j;
                
            }
        }
        resMat[i][0] += temp;
        temp=0;
        stateResMatrix[i][obsCounter] += index;
        index = 0;
    }
    return resMat;
}
int backtrack(int index){
    std::vector<int> path =  vector<int>();
    path.push_back(index);

    for(int i=stateResMatrix[0].size()-1;i>0; --i){
        path.push_back(stateResMatrix[index][i]);
         index = stateResMatrix[index][i];
    }

     cout  << path[path.size()-1];
    for (int j = path.size()-2; j >= 0; --j){
        cout << " " << path[j];
    }
    return 0;
    
}
int read2(std::istream&){
    vector<float> transitions;
    vector<float> observations;
    vector<float> initial;
    string newline;
    cin >> tranRow;
    cin >> tranCol;
    //read in vectors transitions, observations, initial
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
    
    //turn into matrices
    vector<vector<float> > tranMatrix = getMatrix(tranRow, tranCol, transitions);
    vector<vector<float> > obsMatrix = getMatrix(obsRow, obsCol, observations);
    vector<vector<float> > inMatrix = getMatrix(inCol, inRow, initial);
    
    int nrObs;
    int obs;
    cin >> nrObs;
    cin >> obs;
    
    stateResMatrix = vector<vector<float> >(tranRow, std::vector<float>(nrObs));
    //first elementwise operation
    vector<vector<float> > column = getCol(obs, obsMatrix);
    vector<vector<float> > partRes = elemMultiply(inMatrix, column);
      
    
    for (int m = 0; m < nrObs-1; ++m){
        vector<vector<float> > tempMatrix2 (tranRow, std::vector<float>(tranCol));
        cin >>obs;
        obsCounter++;
        for(int n=0;n<tranRow; ++n){
           
            for(int b=0;b<tranCol;++b){
                tempMatrix2[n][b] += partRes[b][0]*tranMatrix[b][n]*obsMatrix[n][obs];
            }
        }
        partRes = getMax(tempMatrix2);
    }

    float temp=0;
    int index=0;
    for(int s =0;s<partRes.size();++s){       
        if(partRes[s][0]>temp){
            temp=partRes[s][0];
            index=s;
        }
    }
    backtrack(index);
    return 0;
}

int main(int argc, char** argv) {
    read2(std::cin);
    return 0;
}

