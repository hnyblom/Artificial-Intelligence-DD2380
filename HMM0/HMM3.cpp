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
vector<vector<float> > tranMatrix;
vector<vector<float> > obsMatrix;
vector<vector<float> > inMatrix;
vector<vector<float> > partRes;
vector<vector<float> > backPartRes;
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
//get one row from a matrix, 
vector<vector<float> > getRow(int obs, vector<vector<float> > matrix){
    int cols = matrix[0].size();
    vector<vector<float> > result(cols, std::vector<float>(1));
    for(int i=0;i<cols;++i){
        result[i][0] += matrix[obs][i];
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
vector<vector<float> > rowMultiply(vector<vector<float> > matrix1, vector<vector<float> > matrix2){
    int row1 = matrix1.size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    //elementärmultiplicera ihop row med matrix 2 sedan summera
    vector<vector<float> > resMatrix(row1, std::vector<float>(1));

    for (int i = 0; i < col2; ++i){
        vector<vector<float> > row = getRow(i, matrix1);
        vector<vector<float> > multi = elemMultiply(row, matrix2);
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


float forwardAlgorithm(vector<float> obsSeq, vector<vector<float> > obsMatrix, vector<vector<float> > tranMatrix, vector<vector<float> > inMatrix){
   vector<vector<float> > column = getCol(obsSeq[0], obsMatrix);
   //c0 = partRes
   partRes = elemMultiply(inMatrix, column);

   for (int m = 0; m < obsSeq.size()-1; ++m){
       vector<vector<float> > tempMatrix = multiply(tranMatrix, partRes);
       column = getCol(obsSeq[m+1], obsMatrix);
       partRes = elemMultiply(tempMatrix, column);
 
   }
   float summ = sum(partRes);

   cout << summ;
   return summ;

}
vector<float> flipObs(vector<float> obsSeq){
    vector<float> backObsSeq(obsSeq);

    vector<vector<float> > backStart(obsSeq.size(), std::vector<float>(1));
    for(int i=0; i<obsSeq.size(); ++i){     
        //Flippar på observation sequence
        backObsSeq[obsSeq.size()-1-i]=obsSeq[i];
    }
    return backObsSeq;
}

float backwardAlgorithm(vector<float> obsSeq, vector<vector<float> > obsMatrix, vector<vector<float> > tranMatrix, vector<vector<float> > inMatrix){
    vector<vector<float> > backStart(obsSeq.size(), std::vector<float>(1));
    for(int i=0; i<obsSeq.size(); ++i){
        //Fyller vektor med ettor 
        backStart[i].push_back(1);
    }
   backPartRes = backStart;
   vector<float> backObsSeq = flipObs(obsSeq);
   
   for (int m = 0; m < obsSeq.size()-1; ++m){
       vector<vector<float> > tempMatrix = rowMultiply(tranMatrix, backPartRes);
       vector<vector<float> > column = getCol(backObsSeq[m], obsMatrix);
       backPartRes = elemMultiply(tempMatrix, column);
 
   }
   float summ = sum(backPartRes);

   cout << summ;
   return summ;

}
float gamma(vector<float> obsSeq, vector<vector<float> > tranM, float frontSum){
    float denom = 0;
    int nrStates = tranM.size();
    //vector<float> gammaRes;
    vector<float> backObsSeq = flipObs(obsSeq);
    vector<float> newObs;
    float gammaRes;
    
    //for(int t=0;t<obsSeq.size(); ++t){
        for(int i=0;i<nrStates; ++i){
            
            //for(int j=0;j<nrStates;++j){
                gammaRes += (partRes.at(i)).at(1) * (backPartRes.at(i)).at(1) / frontSum;
                
            }
        //}
   // }
    return gammaRes;
}

int read3(std::istream&){
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
    tranMatrix = getMatrix(tranRow, tranCol, transitions);
    obsMatrix = getMatrix(obsRow, obsCol, observations);
    inMatrix = getMatrix(inCol, inRow, initial);

       
   int nrObs;
   cin >> nrObs;
   int obs;
   vector<float> obsSeq(nrObs);
   for(int n = 0; n<nrObs; ++n){
        cin >> obs;
        obsSeq[n] = obs;
   }
   float forwSum = forwardAlgorithm(obsSeq, obsMatrix, tranMatrix, inMatrix);
   float backSum = backwardAlgorithm(obsSeq, obsMatrix, tranMatrix, inMatrix);
   
   //gamma = för varje värde i partres/backbartres, multiplicera och dela med forwardSum
   vector<vector<float>> gammaRes(partRes.size());
   vector<vector<float>> diGammaRes(partRes.size());
   
   //Nr of observations is nr of rows in transitionmatrix
   gamma(obsSeq, tranMatrix, forwSum);
   
//   for(int p=0;p<partRes.size();++p){
//       float temp = partRes[p]*backPartRes[p];
//       temp = temp/forwardSum;
//       gammaRes[p]=temp;
//       diGammaRes[p] = temp*pa
//   }
   
   

    return 0;
}    
    

int main(int argc, char** argv) {
    read3(std::cin);
    return 0;
}

