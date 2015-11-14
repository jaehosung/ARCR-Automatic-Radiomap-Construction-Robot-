#include<stdio.h>
#define _USE_MATH_DEFINES
#define R_EARTH 6371000
#include<math.h>
#define NUM 5

float angleArr[NUM][2] = {{36.367609,127.355281},{36.367717,127.355624},{36.367898,127.355511},{36.36782,127.355173},{36.367609,127.355281}};

float diffDistanceConti[NUM];
float diffDistancePrev[NUM];
float diffAngle[NUM]={0,};

//function Declaration
void absoulteMethod();
void angleDiffMethod();
float degToRad(float deg);
float radToDeg(float rad);

int main(){
    angleDiffMethod();
    return 0;
}

//AngleDifference Method
void angleDiffMethod(){
    int i,j;

//angle Degree to Radian
    for(i=0;i<NUM;i++){
        for(j=0;j<2;j++){
            angleArr[i][j]=degToRad(angleArr[i][j]);
        }
    }
//Print
    printf("print the angle we get\n");
    for(i=0;i<NUM;i++){
        for(j=0;j<2;j++){
            printf("%f\t",angleArr[i][j]);
        }
        printf("\n");
    }
//diffDistancePrev[i] refers 'from i to i+1'
    for(i=0;i<NUM-1;i++){
        float pi1 = angleArr[i][0];
        float pi2 = angleArr[i+1][0];
        float dpi = angleArr[i+1][0]-angleArr[i][0];
        float dlambda = angleArr[i+1][1]-angleArr[i][1];
        float a = sin(dpi/2)*sin(dpi/2)+cos(pi1)*cos(pi2)*sin(dlambda/2)*sin(dlambda/2); 
        float c = 2*atan2(sqrt(a),sqrt(1-a));
        diffDistancePrev[i]=R_EARTH*c;
        printf("%d   %f\n",i,diffDistancePrev[i]);
    }
//diffDistanceConti[i] refers 'from i to i+2'
    for(i=0;i<NUM-2;i++){
        float pi1 = angleArr[i][0];
        float pi2 = angleArr[i+2][0];
        float dpi = angleArr[i+2][0]-angleArr[i][0];
        float dlambda = angleArr[i+2][1]-angleArr[i][1];
        float a = sin(dpi/2)*sin(dpi/2)+cos(pi1)*cos(pi2)*sin(dlambda/2)*sin(dlambda/2); 
        float c = 2*atan2(sqrt(a),sqrt(1-a));
        diffDistanceConti[i]=R_EARTH*c;
        printf("%d   %f\n",i,diffDistanceConti[i]);
    }
//anglediff  means the vector difference between two pathes,and It measured  the clockwise from the origin Vector
    for(i=1;i<NUM-1;i++){
        float a = diffDistanceConti[i-1];
        float b = diffDistancePrev[i-1];
        float c = diffDistancePrev[i];
        diffAngle[i]=radToDeg(acos((b*b+c*c-a*a)/(2*b*c)));
        printf("%f\n",diffAngle[i]);
    }
}

float radToDeg(float rad){
    return (rad*180/M_PI);
}

float degToRad(float deg){
    return (deg*M_PI/180);
}
