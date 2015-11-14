#include<stdio.h>
#define _USE_MATH_DEFINES
#define R_EARTH 6371000
#include<math.h>
#define NUM 5

float angleArr[NUM][2] = {{36.367609,127.355281},{36.367717,127.355624},{36.367898,127.355511},{36.36782,127.355173},{36.367609,127.355281}};
float pos_diffArr[NUM][3];
float posArr[NUM][3];
float diffAngleZero[NUM][2];
float diffAnglePrev[NUM][2];

float diffDistanceConti[NUM];
float diffDistancePrev[NUM];
float diffAngle[NUM];

//function Declaration
void absoulteMethod();
void angleDiffMethod();
float degToRad(float deg);

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
// Get the value of diff angle
    for(i=0;i<NUM;i++){
        for(j=0;j<2;j++){
            diffAngleZero[i][j]=angleArr[i][j]-angleArr[0][j];
            if(i>0)diffAnglePrev[i][j]=angleArr[i][j]-angleArr[i-1][j];else diffAnglePrev[i][j]=0;
        }
    }
//Get the distance
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
//diffDistanceConti[i] refers from i to i+2
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
    for(i=0;i<NUM-1;i++){

    }
}

void absolutemethod(){
    int i,j;
// from this reasonalbe data
    for(i=0;i<num;i++){
        for(j=0;j<2;j++){
            printf("%f\t",anglearr[i][j]);
            anglearr[i][j] = anglearr[i][j]*m_pi/180;
            printf("%f\t",anglearr[i][j]);
        }
        printf("\n");
        posarr[i][0]=r_earth*sin(m_pi/2-anglearr[i][0])*cos(anglearr[i][1]);
        posarr[i][1]=r_earth*sin(m_pi/2-anglearr[i][0])*sin(anglearr[i][1]);
        posarr[i][2]=r_earth*cos(m_pi/2-anglearr[i][0]);
    }

//difference from first value
    for(i=0;i<num;i++){
        for(j=0;j<3;j++){
            pos_diffarr[i][j]=posarr[i][j]-posarr[0][j];
        }
    }

    for(i=0;i<num;i++){
        for(j=0;j<3;j++){
            printf("%.10f",posarr[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    printf("difference\n");
    for(i=0;i<num;i++){
        for(j=0;j<3;j++){
            printf("%.10f",pos_diffarr[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}

float degToRad(float deg){
    return (deg*M_PI/180);
}
