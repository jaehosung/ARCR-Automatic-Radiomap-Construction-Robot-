#include<stdio.h>
#include<math.h>

//#define _USE_MATH_DEFINES
#define R_EARTH 6371000
#define NUM 5

/*case1*/
//float angleArr[NUM][2] = {{36.367609,127.355281},{36.367717,127.355624},{36.367898,127.355511},{36.36782,127.355173},{36.367609,127.355281}};

/*case2*/
//float angleArr[NUM][2] = {{36,0},{37,0},{38,0},{37,0},{36,0}};

/*case3*/
float angleArr[NUM][2] = {{36,127},{36,128},{37,128},{37,127},{36,127}};
float diffDistanceConti[NUM];
float diffDistancePrev[NUM];
float diffAngle[NUM]={0,};

//function Declaration
void angleDiffMethod();
float degToRad(float deg);
float radToDeg(float rad);
int addSign(int i);
void printValue();

int main(){
    angleDiffMethod();
    printValue();
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
//diffDistancePrev[i] refers 'from i to i+1'
    for(i=0;i<NUM-1;i++){
        float pi1 = angleArr[i][0];
        float pi2 = angleArr[i+1][0];
        float dpi = angleArr[i+1][0]-angleArr[i][0];
        float dlambda = angleArr[i+1][1]-angleArr[i][1];
        float a = sin(dpi/2)*sin(dpi/2)+cos(pi1)*cos(pi2)*sin(dlambda/2)*sin(dlambda/2); 
        float c = 2*atan2(sqrt(a),sqrt(1-a));
        diffDistancePrev[i]=R_EARTH*c;
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
    }
//anglediff  means the vector difference between two pathes,and It measured  the clockwise from the origin Vector
    for(i=1;i<NUM-1;i++){
        float a = diffDistanceConti[i-1];
        float b = diffDistancePrev[i-1];
        float c = diffDistancePrev[i];
        float cos= (b*b+c*c-a*a)/(2*b*c);
        if(cos>1) cos = 1; else if(cos<-1) cos = -1;
//add degree of Sign 'acos (-1 to 1) (0 to PI)'
        diffAngle[i]=(180-radToDeg(acos(cos)))*addSign(i);
    }
}
//Print the value of distance and angles
void printValue(){
    for(i=0;i<NUM-1; i++){
        printf("trial%d\t distance : %.2f \t angle : %.2f\n",i+1,diffDistancePrev[i],diffAngle[i]);
    }
}
int addSign(int i){
    if(i==0) return 1;
    float lat1 = angleArr[i-1][0], long1 = angleArr[i-1][1];
    float lat2 = angleArr[i][0], long2 = angleArr[i][1];
    float lat3 = angleArr[i+1][0], long3 = angleArr[i+1][1];
    float dlat1 = lat2-lat1, dlat2 = lat3-lat2;
    float dlong1 = long2-long1, dlong2 = long3-long2;
    float crossProduct = dlat1*dlong2-dlat2*dlong1;
    if(crossProduct>=0) return 1; else return -1;
}

float radToDeg(float rad){
    return (rad*180/M_PI);
}

float degToRad(float deg){
    return (deg*M_PI/180);
}
