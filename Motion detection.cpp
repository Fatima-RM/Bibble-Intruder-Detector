#include <iostream>
#include <wiringPi.h>
#include <vector>

using namespace std;

class MotionDetector {
protected:
    bool motionDetected;
public:
    virtual void detectMotion() = 0;
    virtual bool isMotionDetected() const { return motionDetected; }
    virtual ~MotionDetector() {}
};

class PIRSensor : public MotionDetector {
private:
    int pin;
public:
    PIRSensor(int p) : pin(p) {
        wiringPiSetup();
        pinMode(pin, INPUT);
    }
    void detectMotion() override {
        motionDetected = digitalRead(pin);
    }
};

class MotionSystem {
private:
    vector<MotionDetector*> detectors;
public:
    void addDetector(MotionDetector* detector) {
        detectors.push_back(detector);
    }
    void monitor() {
        while (true) {
            bool detected = false;
            for (auto& detector : detectors) {
                detector->detectMotion();
                if (detector->isMotionDetected()) {
                    detected = true;
                }
            }
            cout << (detected ? "Motion Detected! Alert Triggered!" : "No Motion Detected.") << endl;
            delay(500);
        }
    }
    ~MotionSystem() {
        for (auto& detector : detectors) {
            delete detector;
        }
    }
};

int main() {
    PIRSensor pir1(7);
    PIRSensor pir2(8);
    PIRSensor pir3(9);
    PIRSensor pir4(10);
    
    MotionSystem system;
    system.addDetector(&pir1);
    system.addDetector(&pir2);
    system.addDetector(&pir3);
    system.addDetector(&pir4);
    
    system.monitor();
    return 0;
}
