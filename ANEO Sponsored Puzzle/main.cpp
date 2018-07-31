#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/* 
    @autor A.Mattia (matti.pw@gmail.com) 
    @github https://github.com/MaGiiK02/
    @codegamePuzzleLink https://www.codingame.com/training/medium/aneo
    The idea is that is too see the semaphores as clocks,
    this let us think about use module to calculate if we are arriving whean a semaphore is red or green.
    NOTE: after some tests I have discovered that in the last test my solution found a better solution (88 insted of 74).
*/

typedef struct _semaphore  {
    double duration;
    double distance;
} Semaphore;

bool isGoannaBeRed(double sDistance,double sDuration,double speed);
double calculateSemaphoreSpeed(double sDistance,double sDuration,double speed);
double kilometerPerHourToMetrePerSecond(int kmh);
int metrePerSecondToKilometerPerHour (double ms);
double calculateCruiseSpeed(double speed,Semaphore* sem,int count);
 
int main()
{
    int maxSpeed;
    double speed;
    int lightCount;
    Semaphore* semaphores;
    
    cin >> maxSpeed; cin.ignore();
    cin >> lightCount; cin.ignore();
    
    semaphores = (Semaphore*)calloc(lightCount, sizeof(Semaphore));
    speed =  kilometerPerHourToMetrePerSecond(maxSpeed);
    
    
    cerr <<  " s_count: " << lightCount << " max_s: " << speed << endl;
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        cerr << "dis: " << distance << " switchTime: " << duration << endl;
        semaphores[i].duration = duration;
        semaphores[i].distance = distance;
    }
    
    speed = calculateCruiseSpeed(speed,semaphores,lightCount);
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    free(semaphores);
    cout << metrePerSecondToKilometerPerHour(speed) << endl;
}

bool isGoannaBeRed(double sDistance,double sDuration,double speed) {
    double durationDoubled = (sDuration*2);
    double timeToArrive =  sDistance/speed;
    double timeInCurrentSemaphoreCycle =  round(fmod(timeToArrive , durationDoubled)); 
    return timeInCurrentSemaphoreCycle >= sDuration && timeInCurrentSemaphoreCycle != durationDoubled;
}

// the function assumes that at the current speed the semaphore will be red
double calculateSemaphoreSpeed(double sDistance,double sDuration,double speed) {
    double durationDoubled = (sDuration*2);
    double timeToArrive =  sDistance/speed;
    double timeInCurrentSemaphoreCycle = fmod(timeToArrive , durationDoubled); 
    double secondsToLoseForTheGreen = durationDoubled - timeInCurrentSemaphoreCycle;
    return fmod((sDistance / (timeToArrive + secondsToLoseForTheGreen)),speed);
}

double calculateCruiseSpeed(double speed,Semaphore* sem,int count){
    int lastUpdateIndex =-1;
    for(int i=0; i<count; i++) {
        if(isGoannaBeRed(sem[i].distance,sem[i].duration,speed) && i != lastUpdateIndex) {
            speed = calculateSemaphoreSpeed(sem[i].distance,sem[i].duration,speed);
            cerr   << "[" << i << "]" <<" CalculationgNewSpeed::::" << speed<< endl;
            lastUpdateIndex = i;
            i = -1;
        }
    }
    return speed;
}

double kilometerPerHourToMetrePerSecond (int kmh) {
    return round((kmh) * (1000.0/3600.0));
}
int metrePerSecondToKilometerPerHour (double ms) {
    return (int)(ms * 3.6);
}