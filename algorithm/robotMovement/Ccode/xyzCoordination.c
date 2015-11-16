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
