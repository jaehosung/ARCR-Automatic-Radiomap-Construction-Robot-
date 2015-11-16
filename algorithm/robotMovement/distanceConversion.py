from math import *
angleArr = [[36.367609,127.355281],[36.367717,127.355624],[36.367898,127.355511],[36.36782,127.355173],[36.367609,127.355281]]
NUM = len(angleArr)
diffDistanceConti = [0 for i in range(NUM)]
diffDistancePrev = [0 for i in range(NUM)]
diffAngle = [0 for i in range(NUM)]
returnArr = [ [0 for i in range(2)] for j in range(NUM-1)]

R_EARTH = 6371000

#add the sign to the angle value
def addSign(i) :
    if i==0 :
        return 0
    else :
        lat1 = angleArr[i-1][0]
        long1 = angleArr[i-1][1]
        lat2 = angleArr[i][0]
        long2 = angleArr[i][1]
        lat3 = angleArr[i+1][0]
        long3 = angleArr[i+1][1]
        dlat1 = lat2-lat1
        dlat2 = lat3-lat2
        dlong1 = long2-long1
        dlong2 = long3-long2
        crossProduct = dlat1*dlong2-dlat2*dlong1
        if crossProduct>=0 :
            return 1
        else :
            return -1;

# unit conversion
def degToRad(deg) :
    return deg*pi/180

def radToDeg(rad) :
    return  rad*180/pi

# angle difference Method
def angleDiffMethod() :
    for i in range(0,NUM):
        for j in range(0,2):
            angleArr[i][j]=degToRad(angleArr[i][j])

    # diffDistancePrev[i] refers 'from i to i+1'
    for i in range(0,NUM-1) :
        pi1 = angleArr[i][0]
        pi2 = angleArr[i+1][0]
        dpi = angleArr[i+1][0]-angleArr[i][0]
        dlambda = angleArr[i+1][1]-angleArr[i][1]
        a = sin(dpi/2)*sin(dpi/2)+cos(pi1)*cos(pi2)*sin(dlambda/2)*sin(dlambda/2)
        c = 2*atan2(sqrt(a),sqrt(1-a))
        diffDistancePrev[i]=R_EARTH*c

    #diffDistanceConti[i] refers 'from i to i+2'
    for i in range(0,NUM-2) :
        pi1 = angleArr[i][0]
        pi2 = angleArr[i+2][0]
        dpi = angleArr[i+2][0]-angleArr[i][0]
        dlambda = angleArr[i+2][1]-angleArr[i][1]
        a = sin(dpi/2)*sin(dpi/2)+cos(pi1)*cos(pi2)*sin(dlambda/2)*sin(dlambda/2)
        c = 2*atan2(sqrt(a),sqrt(1-a))
        diffDistanceConti[i]=R_EARTH*c
    # anglediff  means the vector difference between two pathes,and It measured  the clockwise from the origin Vector
    for i in range(1,NUM-1) :
        a = diffDistanceConti[i-1]
        b = diffDistancePrev[i-1]
        c = diffDistancePrev[i]
        cosValue= (b*b+c*c-a*a)/(2*b*c);
        if cosValue>1 :
            cosValue = 1
        elif cosValue<-1 :
            cosValue = -1
        #add degree of Sign 'acos (-1 to 1) (0 to PI)'
        diffAngle[i]=(180-radToDeg(acos(cosValue)))*addSign(i)

def printValue() :
    for i in range(0,NUM-1) :
        print "trial%d\tdistance : %f\tangle %f"  % (i+1,diffDistancePrev[i],diffAngle[i])

def returnValue() : 
    for i in range(0,NUM-1) :
        returnArr[i][0]=diffDistancePrev[i]
        returnArr[i][1]=diffAngle[i]
    return returnArr

angleDiffMethod()
print(returnValue())
