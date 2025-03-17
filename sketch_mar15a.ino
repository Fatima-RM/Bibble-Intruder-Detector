// Base class for Motor (Abstraction & Encapsulation)
class MotorBase {
protected:
    int pin1, pin2, pin3, pin4;

public:
    MotorBase(int p1, int p2, int p3, int p4)
        : pin1(p1), pin2(p2), pin3(p3), pin4(p4) {}

    virtual void move() = 0; // Pure virtual function (Polymorphism)
};

// Motor Control Class
class MotorControl : public MotorBase {
public:
    MotorControl(int p1, int p2, int p3, int p4)
        : MotorBase(p1, p2, p3, p4) {}

    void stop() {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        Serial.println("Motors Stopped");
    }
};

// Forward Movement Class
class Forward : public MotorControl {
public:
    Forward(int p1, int p2, int p3, int p4)
        : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        Serial.println("Moving Forward");
    }
};

// Backward Movement Class
class Backward : public MotorControl {
public:
    Backward(int p1, int p2, int p3, int p4)
        : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        Serial.println("Moving Backward");
    }
};

// Turn Left Movement Class
class TurnLeft : public MotorControl {
public:
    TurnLeft(int p1, int p2, int p3, int p4)
        : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        Serial.println("Turning Left");
    }
};

// Turn Right Movement Class
class TurnRight : public MotorControl {
public:
    TurnRight(int p1, int p2, int p3, int p4)
        : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        Serial.println("Turning Right");
    }
};

// Ultrasonic Sensor Class
class UltrasonicSensor {
private:
    int trig, echo;

public:
    UltrasonicSensor(int t, int e) : trig(t), echo(e) {
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
    }

    float getDistance() {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        return (pulseIn(echo, HIGH) * 0.034) / 2;
    }
};

// IR Sensor Class
class IRSensor {
private:
    int pin;

public:
    IRSensor(int p) : pin(p) {
        pinMode(pin, INPUT);
    }

    bool isObstacleDetected() {
        return !digitalRead(pin);
    }
};

// Object Declarations
Forward forward(3, 6, 9, 10);
Backward backward(3, 6, 9, 10);
TurnLeft left(3, 6, 9, 10);
TurnRight right(3, 6, 9, 10);

UltrasonicSensor sensorLeft(2, 4), sensorFront(7, 8), sensorRight(A0, A1);
IRSensor leftIR(A2), rightIR(A3);

void setup() {
    Serial.begin(9600);

    // Set motor pins as output
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
}

void loop() {
    self_driving();
}

void self_driving() {
    float distance1 = sensorLeft.getDistance();
    float distance2 = sensorFront.getDistance();
    float distance3 = sensorRight.getDistance();

    if (distance2 > 20) { // Increased threshold from 14 cm to 20 cm
        forward.move();
    } else if (distance1 > 20 && distance1 > distance3) { // Increased threshold
        left.move();
    } else if (distance3 > 20 && distance3 > distance1) { // Increased threshold
        right.move();
    } else {
        backward.move();
    }

    IR_control();
}

void IR_control() {
    if (leftIR.isObstacleDetected()) {
        forward.move();
    }
    if (rightIR.isObstacleDetected()) {
        backward.move();
    }
}
