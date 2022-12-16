
//Diwas Dulal
//Description : This Fucntions are different functions where one is a recursive  Fibonacci function, one is recursive sum of all intergers, one is recursive Largest Value in array, and one is Finding amount of eagles and the size of each.



#include "parameters.h"
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

int Sum(const int n);
int Fib(const int n);
int Largest(const int arr[], int n);
int EagleCounter(vector<vector<char>> &grid, int r, int c);

// a recursive function that computes the fibonacci series
int Fib(const int n) {
  //base case returns the value if it is 1 or less
  if (n <= 1) {
    return n;
  }
  //adds each time recursively but decrements n by 2 and n by 1 each call
  return Fib(n - 2) + Fib(n - 1);
}
// a recursive function that computes the sum of integers 1, 2, 3, …., n for a
// given number n. So Sum(6) should return 1 + 2 + 3 + 4 + 5 + 6 , i.e. 21. The
// recurrence relation is defined as: sum(n) = n + sum(n-1)
int Sum(const int n) {
  //base case to return 1 if n ==1
  if (n == 1) {
    return n;
  }
  //recursive call which decrements n by 1 each time until a base case is not returned which is 1 then adds it to the previous call
  return n + Sum(n - 1);
}
// a recursive function that computes the largest value for an integer array of
// positive and negative values
int Largest(const int arr[], int n) {
  //base case returns the first value when n is 1
  if (n == 1){
    return arr[0];
  }
  //recursive call on Largest to return each value from the bottom and return the max of that and the max of arr[n-1] and retruns the max out of both
  return max(arr[n - 1], Largest(arr, n - 1));
}

//FindEagle function takes as parameters the 2-D array and the x-y coordinates of a cell that is a part of an eagle (non-zero value) and erases (change to 0) the image of an eagle. 
int FindEagle(vector<vector<int>> &grid, int x, int y) {
  int R = grid.size(); // Amount of Rows
  int C = grid[0].size(); //Amount of coloum
  if (x >= 0 and x < R and y >= 0 and y < C and grid[x][y] != 0) {
    grid[x][y] = 0; // updating grid value to 0
    //this is the recursive call to FindEagle and checks every neighbour vertically, horizontally, and diagonally and adds one each time and returns it
    return 1 + FindEagle(grid, x + 1, y) + FindEagle(grid, x - 1, y) +
           FindEagle(grid, x, y + 1) + FindEagle(grid, x, y - 1) +
           FindEagle(grid, x - 1, y - 1) + FindEagle(grid, x + 1,y - 1) +
           FindEagle(grid, x - 1, y + 1) + FindEagle(grid, x + 1, y + 1);
  }
  return 0;
}

// a recursive function that examines and counts the number of objects (eagles) in a photograph.
void FindEagles(vector<vector<int>> &grid) {
  int R = grid.size();// Amount of Rows
  int C = grid[0].size();//Amount of coloum
  int amount = 0; // holds the amount of eagles found
  //goes throguh the grid and increments Amount of eagle each time a non zero is seent hen calls the recursive fucntion which returns a count of teh size of a certain eagle
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (grid[i][j] == 1) {
        amount += 1;
        int eaglesize = 0;
        int count = FindEagle(grid, i, j); //storest he size of an eagle 
        cout << "An eagle size " << count << " is found." << endl;
      }
    }
  }
  cout << endl;
  cout << amount << " eagle(s) found in the picture." << endl <<endl;
}

int main() {
  ifstream myIn("eagle.dat");
  cout << Fib(FibVal) << endl << endl;
  cout << Sum(SumVal) << endl << endl;
  int n = sizeof(LongestVal) / sizeof(LongestVal[0]);
  cout << Largest(LongestVal, n) << endl << endl;
  int num;
  int r, c, size;
  //this while loop goes throguh and assigns each value of the grid from the file until there is no Row or Column size then calls FindEagles on each grid 
  while (myIn >> r >> c) {
    //creats a size r x c grid using a vector
    vector<vector<int>> grid(r, vector<int>(c, 0));
    //this loops assigns each value to the appropriate place in the grid
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        myIn >> grid[i][j];
        cout << grid[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    FindEagles(grid);//calls the FindEagles
  }

  return 0;
}
