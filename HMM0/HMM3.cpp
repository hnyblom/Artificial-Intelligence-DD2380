
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int tranRow;
int tranCol;
int obsRow;
int obsCol;
int inRow;
int inCol;

vector<vector<double> > stateResMatrix;
vector<vector<double> > tranMatrix;
vector<vector<double> > obsMatrix;
vector<vector<double> > pi;

int print(vector<vector<double> > matrix){
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

vector<vector<double> > getMatrix(int row, int col, vector<double>& val){
    vector<vector<double> > resMatrix(row, vector<double>(col));
    int k=0;
    for (int i=0; i<row; ++i){
        for(int j=0;j<col;++j){
            resMatrix[i][j]=val[k];
            ++k;
        }
    }
    return resMatrix;
}

int printResult(vector<vector<double> > tranMatrix, vector<vector<double> >  obsmatrix){
  //print transition matrix
  cout << tranRow << " " << tranCol;
  for(int i=0; i<tranRow; ++i){
    for(int j=0; j<tranCol; ++j){
      cout << " " << tranMatrix[i][j];
    }
  }
  //print observation matrix
  cout << "\n" << obsRow << " " << obsCol;
  for(int i=0; i<obsRow; ++i){
    for(int j=0; j<obsCol; ++j){
      cout << " " << obsMatrix[i][j];
    }
  }
  cout << "\n";
  return 0;
}

//read in matrices from inputfile. Transition matrix, observation matrix and initial matrix (pi)
int readMatrices(){
  vector<double> transitions;
  vector<double> observations;
  vector<double> initial;
  string newline;
  cin >> tranRow;
  cin >> tranCol;

  //read in vectors transitions, observations, initial
  for (int i=0;i<tranRow*tranCol;++i){
      double value;
      cin >> value;
      transitions.push_back(value);
  }

  cin >> obsRow;
  cin >> obsCol;
  for (int k=0;k<obsRow*obsCol;++k){
      double value;
      cin >> value;
      observations.push_back(value);
  }

  cin >> inRow;
  cin >> inCol;
  for (int l=0;l<inRow*inCol;++l){
      double value;
      cin >> value;
      initial.push_back(value);
  }  

  //turn into matrices
  tranMatrix = getMatrix(tranRow, tranCol, transitions);
  obsMatrix = getMatrix(obsRow, obsCol, observations);
  pi = getMatrix(inRow, inCol, initial);


  return 0;
}

int main(int argc, char **argv){
  readMatrices();
  int T; //nr observations
  int N = tranRow; //number states
  int M = obsCol; //number observation symbols
  

  int maxiter = 30;
  int iter = 0;
  double logProb = 0;
  double oldLogProb = -INFINITY;
  
  //read in observationsequence
   cin >> T;
   int obs;
   vector<double> obsSeq(T);
   for(int n = 0; n<T; ++n){
        cin >> obs;
        obsSeq[n] = obs;
   }
   
  //computed matrices alfa-forward, beta-backward
  vector<double> c(T, 0.0); //scaling
  vector<vector<double> > alfa(T, vector<double>(N));
  vector<vector<double> > beta(T, vector<double>(N));
  vector<vector<double> > gamma(T, vector<double>(N));

  vector<vector<vector<double> > > digamma(T);
  for (int i = 0; i < T; ++i){
    vector<vector<double> > temp(N, vector<double>(N));
    digamma[i] = temp;
  }


  //doing the actual stuff from stamp
  while((iter < maxiter) && logProb> oldLogProb ){
    //----------Alfa forward-----------------------------------------------------------------------------
    //alfa 0
    c[0] = 0;
    
    for(int i=0;i<N;++i){
      alfa[0][i] = pi[0][i]*obsMatrix[i][obsSeq[0]];
      c[0] += alfa[0][i];
    }

    //scale
    c[0] = 1.0/c[0];
    for(int i=0;i<N;++i){
      alfa[0][i] *= c[0];
    }

    for(int t=1;t<T;++t){
      c[t] = 0;
      for(int i=0;i<N;++i){
        alfa[t][i] = 0;
        for(int j=0;j<N;++j){
          alfa[t][i] += alfa[t-1][j]*tranMatrix[j][i];
        }
        alfa[t][i] *= obsMatrix[i][obsSeq[t]];
        c[t] += alfa[t][i];
      }

      //scale
      c[t] = 1.0/c[t];
      for(int i=0;i<N;++i){
        alfa[t][i] *= c[t];
      }
    }

    //----------Beta backward------------------------------------------------

    for(int i=0;i<N;++i){    
      beta[T-1][i] = c[T-1];
     
    }

    for(int t=T-2; t>=0;--t){
      for(int i=0;i<N;++i){
        beta[t][i] = 0;
        for(int j=0;j<N;++j){
          beta[t][i] += tranMatrix[i][j] * obsMatrix[j][obsSeq[t+1]] * beta[t+1][j];
        }
        //scale
        beta[t][i] *= c[t];
      }
    }

  //---------digamma & gamma------------------------------------------------------------------------------

    for(int t=0;t<(T-1);++t){
      double denom = 0;
      for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
          denom += alfa[t][i] * tranMatrix[i][j] * obsMatrix[j][obsSeq[t+1]] * beta[t+1][j];
        }
      }

      for(int i=0;i<N;++i){
        gamma[t][i] = 0;
        for(int j=0;j<N;++j){
          digamma[t][i][j] = (alfa[t][i] * tranMatrix[i][j] * obsMatrix[j][obsSeq[t+1]] * beta[t+1][j]) / denom;
          gamma[t][i] += digamma[t][i][j];
          
        }
      }
    }


    //Special case gamma T-1(i)
    double denom =0;
    for(int i=0;i<N;++i){
        denom += alfa[T-1][i];
    }
    for(int i=0;i<N;++i){
        gamma[T-1][i] = alfa[T-1][i]/denom;
    }
    

    //-------------------------------------do estimations-------------------------------------------------------------------
    //Re-estimate pi - initial matrix 
    for(int i=0; i<N; ++i){
        pi[0][i] = gamma[0][i];
    }


    //Re-estimate A - transitionmatrix
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            double numer = 0;
            double denom = 0;
            for(int t=0; t<T-1; ++t){
              numer += digamma[t][i][j];
              denom += gamma[t][i];     
            }
            tranMatrix[i][j] = numer/denom;  //kan vara avrundning här på division med små tal som blir fel?
        }
    }
    //Re-estimate B - observationmatrix
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            double numer =0;
            double denom =0;
            for(int t=0; t<T; ++t){ 
                if(obsSeq[t] == j){
                    numer += gamma[t][i];
                }
                denom += gamma[t][i];
            }
            obsMatrix[i][j] = numer/denom; //kan vara avrundning här på division med små tal som blir fel?
        }
    }


    //Compute log
    double logProb= 0;   //fucking hell 
    for(int i=0;i<T;++i){
        logProb += log(c[i]);
    }
    logProb = logProb*(-1);


    oldLogProb = logProb;  //kanske blir fel vid första loopen? 
    ++iter;
    
  }

  // //Print matrix
 printResult(tranMatrix, obsMatrix);

  return 0;
}
