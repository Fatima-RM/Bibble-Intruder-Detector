// Base class for Motor (Abstraction & Encapsulation)
class MotorBase {
protected:
    int pin1, pin2, pin3, pin4;

public:
    MotorBase(int p1, int p2, int p3, int p4)
        : pin1(p1), pin2(p2), pin3(p3), pin4(p4) {}

    virtual ~MotorBase() {} // Virtual destructor
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

// Movement Classes
class Forward : public MotorControl {
public:
    Forward(int p1, int p2, int p3, int p4) : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        Serial.println("Moving Forward");
    }
};

class Backward : public MotorControl {
public:
    Backward(int p1, int p2, int p3, int p4) : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        Serial.println("Moving Backward");
    }
};

class TurnLeft : public MotorControl {
public:
    TurnLeft(int p1, int p2, int p3, int p4) : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        Serial.println("Turning Left");
    }
};

class TurnRight : public MotorControl {
public:
    TurnRight(int p1, int p2, int p3, int p4) : MotorControl(p1, p2, p3, p4) {}

    void move() override {
        digitalWrite(pin1, HIGH);
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
    UltrasonicSensor(int t, int e) : trig(t), echo(e) {}

    void init() {
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
    }

    float getDistance() {
        long sum = 0;
        for (int i = 0; i < 5; i++) {
            digitalWrite(trig, LOW);
            delayMicroseconds(2);
            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);
            sum += pulseIn(echo, HIGH) * 0.034 / 2;
            delay(20);
        }
        return sum / 5;
    }
};

// IR Sensor Class
class IRSensor {
private:
    int pin;

public:
    IRSensor(int p) : pin(p) {}

    void init() {
        pinMode(pin, INPUT);
    }

    bool isObstacleDetected() {
        return digitalRead(pin) == LOW;
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

    // Initialize sensors
    sensorLeft.init();
    sensorFront.init();
    sensorRight.init();
    leftIR.init();
    rightIR.init();
}

void loop() {
    self_driving();
}

void self_driving() {
    float distanceLeft = sensorLeft.getDistance();
    float distanceFront = sensorFront.getDistance();
    float distanceRight = sensorRight.getDistance();

    Serial.print("Front: "); Serial.print(distanceFront);
    Serial.print(" Left: "); Serial.print(distanceLeft);
    Serial.print(" Right: "); Serial.println(distanceRight);

    if (distanceFront > 30) {  // Move forward if clear
        forward.move();
    } else {
        backward.move();  // Move backward first before turning
        delay(500);
        backward.stop();
        delay(200);

        if (distanceLeft > 40 && distanceRight < 30) {  // Prefer left if more space
            left.move();
            delay(700);
        } else if (distanceRight > 40 && distanceLeft < 30) {  // Prefer right if more space
            right.move();
            delay(700);
        } else if (distanceLeft > 30 && distanceRight > 30) {  // Choose the better direction
            if (distanceLeft > distanceRight) {
                left.move();
                delay(700);
            } else {
                right.move();
                delay(700);
            }
        } else {  
            backward.move();  // If stuck, back up and try again
            delay(800);
        }
    }

    IR_control();
}

void IR_control() {
    if (leftIR.isObstacleDetected() && !rightIR.isObstacleDetected()) {
        Serial.println("Left IR detected an obstacle, turning right.");
        right.move();
        delay(500);
    } else if (rightIR.isObstacleDetected() && !leftIR.isObstacleDetected()) {
        Serial.println("Right IR detected an obstacle, turning left.");
        left.move();
        delay(500);
    } else if (leftIR.isObstacleDetected() && rightIR.isObstacleDetected()) {
        Serial.println("Both IR sensors detected obstacles, moving backward.");
        backward.move();
        delay(500);
    }
}
