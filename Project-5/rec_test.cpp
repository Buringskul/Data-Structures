#include <iostream>
#include <assert.h>
#include "rec_fun.h"

using namespace std;

void binary_print(ostream& outs, unsigned int n) {
  if (n > 1) {
    binary_print(outs, n / 2);
  }
  
  outs << n % 2;
}


void triangle(ostream& outs, unsigned int m, unsigned int n)
{
	if (m > n) {
    return; 
  }
    
	else {
		for (int i = 1; i <= m; i++)
		{
			outs << "*";
		}
    
		outs << "\n"; 
		triangle(outs, m + 1, n);

		for (int j = 1; j <= m; j++)
		{
			outs << "*";
		}
		outs << "\n";
	}
}


double power(double x, int n) {
  if (n == 0) { //if exponent is 0
    return 1;
  }
  
  else if (n < 0) { //negative exponent
    return 1/power(x, -n);
  }

  else if (n % 2 == 1) { //odd exponenet
    return x * power(x * x, n / 2);
  }
    
  else { //even exponent
    return power(x * x, n / 2);
  }
}


void indented_sentences(size_t m, size_t n)
{
	if (m > n) {
    return;
  }
    
	else {
		for (int i = 1; i < m; i++) {
      cout << " ";
    }
    
		cout << "This was written by calling number " << m << ".\n";
		indented_sentences(m + 1, n);
    
		for (int j = 1; j < m; j++) { 
			cout << " ";
    }
    
		cout << "This was ALSO written by calling number " << m << ".\n";
	}
}


int main()
{
	binary_print(cout,11);
	cout<<endl;
	triangle(cout,3,5);
	cout<<endl;
	cout<<power (4,3);
	cout<<endl;
	indented_sentences(5,8);
	system("pause");
}