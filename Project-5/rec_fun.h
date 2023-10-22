#include<iostream>
#include<cstdlib>
#include<cctype>
using namespace std;


void binary_print(ostream& outs, unsigned int n);
void triangle(ostream& outs, unsigned int m, unsigned int n);
  // Precondition: m <= n
  // Postcondition: The function has printed a pattern of 2*(n-m+1) lines
  // to the output stream outs. The first line contains m asterisks, the next 
  // line contains m+1 asterisks, and so on up to a line with n asterisks.
  // Then the pattern is repeated backwards, going n back down to m.
  /* Example output:
     triangle(cout, 3, 5) will print this to cout:
     ***
     ****
     *****
     *****
     ****
     ***
  */
//Hint: Only one of the arguments changes in the recursive call. Which one? 

//Rewrite the recursive power function from Fig. 9.10 on page 463, so that the time to compute pow(x,n) is log(n): 
double power(double x, int n); 
    // Precondition: If x is zero, then n must be positive. 
    // Postcondition: The value returned is x raised to the power n. 
//Hint: use the formula x^2n = x^n  x^n


void indented_sentences(size_t m, size_t n); 
// precondition: m <=n; 
//postcondition: print out the above pattern by calling number from m to n 