#include <bits/stdc++.h>
using namespace std ;

class point {
	public:
		double x , y ;
} ;

bool compareX(point const& point1 , point const& point2) {
	if(point1.x < point2.x)
		return true ;
	else if(point1.x == point2.x)
		return point1.y < point2.y ;
	else
		return false ;
}

double dist(point& point1 , point& point2) {
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y)) ;
}

vector <point> points_x ;

int main() {
	int n ;
	scanf("%d" , &n) ;
	points_x.resize(n) ;
	double d = numeric_limits <double> :: max() ;
	for(int i = 0 ; i < n ; i++)
		scanf("%lf %lf" , &points_x[i].x , &points_x[i].y) ;
	sort(points_x.begin() , points_x.end() , compareX) ;
	for(int i = 0 ; i < n ; i++) {
		for(int j = i + 1 ; j < n ; j++) {
			d = min(d , dist(points_x[i] , points_x[j])) ;
			//printf("(%d , %d) -> %lf\n" , i , j , dist(points_x[i] , points_x[j])) ;
		}
	}
	printf("%lf\n" , d) ;
}
