#include <stdio.h>
#include <math.h>

#define NUM_DATA_POINTS 10
#define EPSILON 0.001

float lineSlope(float class1AvgX, float class1AvgY, float class2AvgX, float class2AvgY);
float lineMidpoint(float avg1, float avg2);
float distanceCalculator(float testX, float testY ,float avgX, float avgY);

int main(){

    float class1X, class1Y, class2X, class2Y;
    int i;
    float class1AvgX = 0, class1AvgY = 0;
    float class2AvgX = 0, class2AvgY = 0;

    
    
    for (i = 0; i < NUM_DATA_POINTS; i++)
    { 
        scanf("%f", &class1X);
        scanf("%f", &class1Y);

        class1AvgX +=class1X;
        class1AvgY +=class1Y;
    }

    class1AvgX /= NUM_DATA_POINTS;
    class1AvgY /= NUM_DATA_POINTS;

    
    for (i = 0; i < NUM_DATA_POINTS; i++) //user enter the data points
    { 
        scanf("%f", &class2X);
        scanf("%f", &class2Y);

        class2AvgX +=class2X;  //calculating the avrage of the datas
        class2AvgY +=class2Y;
    }

    class2AvgX /= NUM_DATA_POINTS;
    class2AvgY /= NUM_DATA_POINTS;

    float separatingLineSlope = lineSlope(class1AvgX, class1AvgY, class2AvgX, class2AvgY);
    float separatingLineMidpointX =lineMidpoint(class1AvgX, class2AvgX);
    float separatingLineMidpointY =lineMidpoint(class1AvgY, class2AvgY);
    
    printf("Midpoint = (%.1f, %.1f)\n", separatingLineMidpointX, separatingLineMidpointY);
    printf("Separating line slope = %.1f\n", separatingLineSlope);

    float testX, testY;
    while (1) {
        // User enters a test point
        if (scanf("%f %f", &testX, &testY) != 2) { //User enters something not expected Program quits.     
            break;
        }

        // Calculate the distance from the test point to the average points of both classes
        double distance1 = distanceCalculator( testX, testY ,class1AvgX, class1AvgY);
        double distance2 = distanceCalculator( testX, testY ,class2AvgX, class2AvgY);

        // Classify and print the result
        if (distance1 < distance2) {
            printf("class 1, distance = %.2lf\n", distance1);
        } else {
            printf("class 2, distance = %.2lf\n", distance2);
        }

    
    }

    return 0;

}


float lineSlope(float class1AvgX, float class1AvgY, float class2AvgX, float class2AvgY){
    
    return (class2AvgY - class1AvgY) / (class2AvgX - class1AvgX + EPSILON);
}

float lineMidpoint(float avg1, float avg2){
    return (avg1 + avg2) / 2;

}

float distanceCalculator(float testX, float testY ,float avgX, float avgY){
   float distance =  sqrt((testX - avgX) * (testX - avgX) +
                    (testY - avgY) * (testY - avgY));

    return distance;
}