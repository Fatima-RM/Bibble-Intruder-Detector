#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <wiringPi.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

using namespace std;

class Robot {
protected:
    int FB_speed = 90, LR_speed = 100;
    int pin1 = 3, pin2 = 5, pin3 = 6, pin4 = 9;
    int trig1 = 2, echo1 = 4, trig2 = 7, echo2 = 8, trig3 = 10, echo3 = 11;
    int leftir = 12, rightir = 13;
    int speaker = 14;
    cv::VideoCapture webcam;
    float duration;
    float distance1, distance2, distance3;
    const float set_distance1 = 14, set_distance2 = 14, set_distance3 = 14;
    vector<string> registered_users;
    
public:
    Robot() : webcam(0) {
        load_registered_users();
    }
    
    void setup();
    void loop();
    void self_driving();
    void face_recognition();
    void voice_alert();
    void gui_update(string status);
    void move_forward();
    void turn_right();
    void turn_left();
    void move_backward_until_clear();
    void IR();
    float dist_measure(int trig, int echo);
    void load_registered_users();
    void log_entry(const string& user);
};

void Robot::setup() {
    wiringPiSetup();
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(trig3, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    pinMode(echo3, INPUT);
    pinMode(leftir, INPUT);
    pinMode(rightir, INPUT);
    pinMode(speaker, OUTPUT);
}

void Robot::loop() {
    self_driving();
    face_recognition();
}

void Robot::self_driving() {
    distance1 = dist_measure(trig1, echo1);
    distance2 = dist_measure(trig2, echo2);
    distance3 = dist_measure(trig3, echo3);

    if (distance2 > set_distance2) {
        move_forward();
    } else if (distance1 > set_distance1 && distance1 > distance3) {
        turn_left();
    } else if (distance3 > set_distance3 && distance3 > distance1) {               
        turn_right();
    } else {
        move_backward_until_clear();
    }
    IR();
}

void Robot::move_forward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    cout << "Moving Forward" << endl;
}

void Robot::turn_right() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    cout << "Turning Right" << endl;
    delay(300);
}

void Robot::turn_left() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    delay(300);
    cout << "Turning Left" << endl;
}

void Robot::move_backward_until_clear() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    cout << "Moving Backward" << endl;
}

float Robot::dist_measure(int trig, int echo) {
    duration = 0;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    return ((duration * 0.034) / 2);
}

void Robot::face_recognition() {
    cv::Mat frame;
    if (webcam.isOpened()) {
        webcam.read(frame);
        if (!frame.empty()) {
            string detected_user = "Unknown";
            if (find(registered_users.begin(), registered_users.end(), detected_user) != registered_users.end()) {
                cout << "Welcome, " << detected_user << "!" << endl;
                log_entry(detected_user);
                gui_update("Welcome " + detected_user);
            } else {
                cv::imwrite("intruder.jpg", frame);
                cout << "Intruder detected! Picture saved." << endl;
                voice_alert();
                gui_update("Intruder detected!");
            }
        }
    }
}

void Robot::voice_alert() {
    cout << "Intrusion detected! Playing alert..." << endl;
    digitalWrite(speaker, HIGH);
    delay(1000);
    digitalWrite(speaker, LOW);
}

void Robot::gui_update(string status) {
    QApplication app(argc, argv);
    QLabel label(QString::fromStdString("Status: " + status));
    label.show();
    app.exec();
}

void Robot::load_registered_users() {
    ifstream file("registered_users.txt");
    string user;
    while (getline(file, user)) {
        registered_users.push_back(user);
    }
    file.close();
}

void Robot::log_entry(const string& user) {
    ofstream log("entry_log.txt", ios::app);
    time_t now = time(0);
    log << user << " entered at " << ctime(&now);
    log.close();
}

int main(int argc, char *argv[]) {
    Robot robot;
    robot.setup();
    while (true) {
        robot.loop();
    }
    return 0;
}