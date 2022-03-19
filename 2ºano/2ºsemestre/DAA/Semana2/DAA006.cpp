#include <iostream>
#include <math.h>
#define PI 3.14159265359
double c1, c2, cr;
double intersect(double x1, double y1, double x2, double y2, double sw) {
    if(y2 <= c2-cr || x2 <= c1-cr || y1 >= c2+cr || x1 >= c1+cr) return 0;
    if(sqrt(pow(x2-c1,2) + pow(y2-c2,2)) <= cr && sqrt(pow(c1-x1,2) + pow(c2-y1,2)) <= cr && sqrt(pow(c1-x1,2) + pow(c2-y2,2)) <= cr && sqrt(pow(c1-x2,2) + pow(c2-y1,2)) <= cr) return sw*sw; //fazer dist entre centro e 4 vertices
    if(y2 >= c2+cr && x2 >= c1+cr && y1 <= c2-cr && x1 <= c1-cr) return PI*cr*cr;
    double area = 0;
    if (sw > 0.005) {
        area += intersect(       x1,y1+(sw/2),x2-(sw/2),       y2,sw/2);
        area += intersect(x1+(sw/2),y1+(sw/2),       x2,       y2,sw/2);
        area += intersect(       x1,       y1,x2-(sw/2),y2-(sw/2),sw/2);
        area += intersect(x1+(sw/2),       y1,       x2,y2-(sw/2),sw/2);
    }
    return area;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        double s1, s2, sw;
        scanf("%lf %lf %lf %lf %lf %lf", &s1, &s2, &sw, &c1, &c2, &cr);
        printf("%.4lf\n", intersect(s1,s2,s1+sw,s2+sw,sw));
    }
    return 0;
}