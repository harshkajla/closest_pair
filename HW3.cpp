/*Given a set of n points in a plane, find the minimum possible distance between any 2 points
Algorithm :
	1.) Sort the points in increasing order of x coordinate
	2.) apply the algorithm recursively on the left half and the right half to get d = min(d_left , d_right)
	3.) make the sep line, which passes somewhere in the middle and consider the region within the 'd-range' of sep
	4.) sort the points on this line in the increasing order of y coordinate
	5.) iterate over all the points and check the points 11 units ahead of it and find d'
	6.) return min(d , d')
*/

#include <bits/stdc++.h>
using namespace std ;

class point {
	public:
		double x , y ;
		int id ;
		void disp() {
			printf("%lf %lf %d\n" , x , y , id) ;
		}
} ;

bool compareX(point const& point1 , point const& point2) {
	if(point1.x < point2.x)
		return true ;
	else if(point1.x == point2.x)
		return point1.y < point2.y ;
	else
		return false ;
}

bool compareY(point const& point1 , point const& point2) {
	if(point1.y < point2.y)
		return true ;
	else if(point1.y == point2.y)
		return point1.x < point2.x ;
	else
		return false ;
}

double dist(point& point1 , point& point2) {
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y)) ;
}

vector <point> points_x , points_y , temp ;

//returns the minimum distance between any 2 pair of points
vector <double> solve(int start , int end) { //start = first point, end = last point
	vector <double> answer(3) ;
	if(start == end) {								//there is just 1 point, then minimum distance = infinity
		answer[1] = answer[0] = points_x[start].id ;
		answer[2] = numeric_limits <double> :: max() ;
		return answer ;
	}
	else if(end == start + 1) { 						//there are just 2 points, then minimum distance is the distance between them
		if(compareY(points_y[end] , points_y[start]) == true) {
			point tmp = points_y[end] ;
			points_y[end] = points_y[start] ;
			points_y[start] = tmp ;
		}
		answer[0] = points_x[start].id ;
		answer[1] = points_x[end].id ;
		answer[2] = dist(points_x[start] , points_x[end]) ;
		return answer ;
	}
	else {
		vector <double> d_left = solve(start , (start + end) / 2) ;
		vector <double> d_right = solve((start + end) / 2 + 1 , end) ;
		for(int i = start ; i <= end ; i++)
			temp[i] = points_y[i] ;
		int j = start , k = (start + end) / 2 + 1 ;
		for(int i = start ; i <= end ; i++)
			if(j == (start + end) / 2 + 1)
				points_y[i] = temp[k++] ;
			else if(k == end + 1)
				points_y[i] = temp[j++] ;
			else if(compareY(temp[j] , temp[k]) == true)
				points_y[i] = temp[j++] ;
			else
				points_y[i] = temp[k++] ;
		double d = min(d_left[2] , d_right[2]) ;
		double sep = (points_x[(start + end) / 2].x + points_x[(start + end) / 2 + 1].x) / 2 ;
		vector <double> d_sep(3) ;
		d_sep[2] = numeric_limits <double> :: max() ;
		vector <point> within_sep ;
		for(int i = start ; i <= end ; i++)
			if(points_y[i].x >= sep - d_sep[2] && points_y[i].x <= sep + d_sep[2])
				within_sep.push_back(points_y[i]) ;
		for(int i = 0 ; i < within_sep.size() ; i++) {
			for(int j = i + 1 ; j <= (i + 11) && j < within_sep.size() ; j++) {
				if(dist(within_sep[i] , within_sep[j]) < d_sep[2]) {
					d_sep[2] = dist(within_sep[i] , within_sep[j]) ;
					d_sep[0] = within_sep[i].id ;
					d_sep[1] = within_sep[j].id ;
				}
			}
		}
		if(d_left[2] < d_sep[2] && d_left[2] < d_right[2])
			return d_left ;
		else if(d_right[2] < d_left[2] && d_right[2] < d_sep[2])
			return d_right ;
		else
			return d_sep ;
	}
}

int main() {
	int n ;
	scanf("%d" , &n) ;
	points_x.resize(n) ;
	points_y.resize(n) ;
	temp.resize(n) ;
	for(int i = 0 ; i < n ; i++) {
		scanf("%lf %lf" , &points_x[i].x , &points_x[i].y) ;
		points_x[i].id = i ;
	}
	sort(points_x.begin() , points_x.end() , compareX) ;
	for(int i = 0 ; i < n ; i++) {
		temp[i].x = points_y[i].x = points_x[i].x ;
		temp[i].y = points_y[i].y = points_x[i].y ;
		temp[i].id = points_y[i].id = points_x[i].id ;
	}
	vector <double> ans = solve(0 , n - 1) ;
	printf("%d %d %.6lf\n" , (int)min(ans[0] , ans[1]) , (int)max(ans[0] , ans[1]) , ans[2]) ;
}
