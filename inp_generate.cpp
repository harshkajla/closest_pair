#include <bits/stdc++.h>
using namespace std ;

int main() {
	srand(time(NULL)) ;
	cout << "5" << endl ;
	for(int i = 0 ; i < 5 ; i++) {
		printf("%d %d\n" , rand() % 20000 , rand() % 10000) ;
	}
}