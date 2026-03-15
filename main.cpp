#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

struct Point { double x, y; };

double dist(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

// using squared dist here to avoid unnecessary sqrt during sorting
double dist2(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

// positive = left turn, negative = right turn, 0 = collinear
double cross(Point O, Point A, Point B) {
    return (A.x-O.x)*(B.y-O.y)-(A.y-O.y)*(B.x-O.x);
}

double pointLineDist(Point A, Point B, Point P) {
    double len=dist(A,B);
    if(len==0) return dist(A,P);
    return abs(cross(A,B,P))/len;
}

// Graham Scan - O(n log n)
vector<Point> convexHull(vector<Point> pts) {
    int n=pts.size();
    if(n<=2) return pts;

    // start from the lowest point, it's guaranteed to be on the hull
    int pivot=0;
    for(int i=1;i<n;i++)
        if(pts[i].y<pts[pivot].y||(pts[i].y==pts[pivot].y&&pts[i].x<pts[pivot].x))
            pivot=i;
    swap(pts[0],pts[pivot]);
    Point p0=pts[0];

    // sort by polar angle, if same angle then by distance
    sort(pts.begin()+1,pts.end(),[&](Point a,Point b){
        double c=cross(p0,a,b);
        if(c!=0) return c>0;
        return dist2(p0,a)<dist2(p0,b);
    });

    // keep only left turns, pop right turns off the stack
    vector<Point> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);
    for(int i=2;i<n;i++) {
        while(hull.size()>=2&&cross(hull[hull.size()-2],hull[hull.size()-1],pts[i])<=0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    return hull;
}

// rotating calipers on the hull - O(n)
// for each edge check the farthest point, that's the strip width for that direction
double minStripWidth(vector<Point>& hull) {
    int n=hull.size();
    if(n<=2) return 0.0;

    double minW=numeric_limits<double>::infinity();
    int j=1;
    for(int i=0;i<n;i++) {
        Point A=hull[i], B=hull[(i+1)%n];
        // j only moves forward, never resets - that's what keeps this O(n)
        while(pointLineDist(A,B,hull[(j+1)%n])>pointLineDist(A,B,hull[j]))
            j=(j+1)%n;
        double w=pointLineDist(A,B,hull[j]);
        if(w<minW) minW=w;
    }
    return minW;
}

// divide and conquer closest pair - O(n log n)
struct Pair { Point a,b; double d; };

// used for small inputs or base case
Pair bruteForce(vector<Point>& pts,int lo,int hi) {
    Pair best={pts[lo],pts[lo+1],dist(pts[lo],pts[lo+1])};
    for(int i=lo;i<hi;i++)
        for(int j=i+1;j<hi;j++) {
            double d=dist(pts[i],pts[j]);
            if(d<best.d) best={pts[i],pts[j],d};
        }
    return best;
}

Pair closestRec(vector<Point>& pts,int lo,int hi) {
    if(hi-lo<=3) return bruteForce(pts,lo,hi);

    int mid=(lo+hi)/2;
    double midX=pts[mid].x;
    Pair left=closestRec(pts,lo,mid), right=closestRec(pts,mid,hi);
    Pair best=(left.d<right.d)?left:right;
    double delta=best.d;

    // only look at points close to the dividing line
    vector<Point> strip;
    for(int i=lo;i<hi;i++)
        if(abs(pts[i].x-midX)<delta)
            strip.push_back(pts[i]);

    sort(strip.begin(),strip.end(),[](Point a,Point b){ return a.y<b.y; });

    // at most 7 comparisons per point here due to geometry
    for(int i=0;i<(int)strip.size();i++)
        for(int j=i+1;j<(int)strip.size()&&(strip[j].y-strip[i].y)<delta;j++) {
            double d=dist(strip[i],strip[j]);
            if(d<delta) { delta=d; best={strip[i],strip[j],d}; }
        }
    return best;
}

Pair closestPair(vector<Point> pts) {
    sort(pts.begin(),pts.end(),[](Point a,Point b){
        return a.x!=b.x?a.x<b.x:a.y<b.y;
    });
    return closestRec(pts,0,pts.size());
}

void printPoint(Point p) { cout<<"("<<p.x<<", "<<p.y<<")"; }

int main(int argc, char* argv[]) {
    string filename = argc>=2 ? argv[1] : "points.txt";
    ifstream f(filename);
    if(!f.is_open()) { cerr<<"Cannot open: "<<filename<<endl; return 1; }

    int n; f>>n;
    vector<Point> pts(n);
    for(int i=0;i<n;i++) f>>pts[i].x>>pts[i].y;

    cout<<fixed<<setprecision(1);

    vector<Point> hull=convexHull(pts);
    cout<<"Otoczka: ";
    for(int i=0;i<(int)hull.size();i++) { if(i>0) cout<<", "; printPoint(hull[i]); }
    cout<<endl;

    cout<<fixed<<setprecision(4);
    cout<<"Proste: d="<<minStripWidth(hull)<<endl;

    if(pts.size()>=2) {
        Pair cp=closestPair(pts);
        cout<<fixed<<setprecision(1);
        cout<<"Najblizsze Punkty: [";
        printPoint(cp.a); cout<<", "; printPoint(cp.b);
        cout<<fixed<<setprecision(3);
        cout<<"] d="<<cp.d<<endl;
    }
    return 0;
}