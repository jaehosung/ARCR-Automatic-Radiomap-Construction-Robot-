import math
NUM = 5
angleArr = [[36.367609,127.355281],[36.367717,127.355624],[36.367898,127.355511],[36.36782,127.355173],[36.367609,127.355281]]
diffDistanceConti = [0 for i in range(NUM)];
diffDistancePrevp = [0 for i in range(NUM)];
diffAngle = [0 for i in range(NUM)];

#add the sign to the angle value
def addSign(num) :
    return num*-1
def degToRad(deg) :
    return deg*math.pi/180
def radTodeg(rad) :
    return  rad*180/math.pi

