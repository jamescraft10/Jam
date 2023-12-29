#include <stdio.h>
#include <stdbool.h>
int main(void) {
int ab = 0+1;
double cd = 0.1;
float ef = 0.1;
bool gh = true;
ab = 0+0;
cd = ab+2;
ef = cd+0.1;
gh = false;
printf("%d\n",ab);
printf("%lf\n",cd);
printf("%f\n",ef);
printf("%d\n",gh);
return ab;

}