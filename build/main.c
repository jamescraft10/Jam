#include <stdio.h>
#include <stdbool.h>
int sub(int a, int b) {
    return a-b;
}
void outabc() {
    printf("abc\n");
}
int add(int a, int b) {
    return a+b;
}
int main(void) {
    int ab = 0+1;
    double cd = 0.1;
    float ef = 0.1;
    bool gh = true;
    int aaa = 5%2;
    int array[] = {
1,2,3,4,5}
;
    char str[] = "Hello, World!\n";
    char inputString[30];
    fgets( inputString, sizeof( inputString), stdin);
        for(int i = 0;
 i < 5;
 ++i) {
        printf("%d\n",i);
    }
    int i = 0;
    while(i <= 10) {
        if(i%2 == 0) {
            printf("Number is even\n");
        }
 else {
            printf("Number is odd\n");
        }
        ++i;
    }
    printf("%s",str);
    printf("%d\n\n",array[2]);
    ab = 0+0;
    cd = ab*2;
    ef = cd+0.1;
    gh = false;
    outabc();
    printf("%d\n",ab);
    printf("%lf\n",cd);
    printf("%f\n",ef);
    printf("%d\n",gh);
    printf("%d\n",aaa);
    printf("%d\n",add(5,6));
    printf("Output works!\n");
    return ab;
}
