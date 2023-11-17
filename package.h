#ifndef package_H
#define package_H

#include<iostream>
#include <ctime>

#include "DS.h"
using namespace std;

class package {
private:
    string packageName;
    string sender;
    string receiver;
    long long dist;
    int trackingNumber;

public:
    Stack<string> status;

    package(string packageName, string sender, string receiver, long long dist)
        : packageName(packageName), sender(sender), receiver(receiver), dist(dist) {
        trackingNumber =  100000 + std::rand() % 900000;
        status.push("added");
        cout << getTrackingNumber() << endl;
    }

    bool operator<(const package& other) const {
        return this->dist < other.dist;
    }

    string getPackageName() const { return packageName; }

    string getSender() const { return sender; }

    string getReceiver() const { return receiver; }

    long long getDistance() const { return dist; }

    int getTrackingNumber() const { return trackingNumber; }

    void setPackageName(string name) { packageName = name; }

    void setSender(string s) { sender = s; }

    void setReceiver(string r) { receiver = r; }

    void setDistance(long long d) { dist = d; }

    void setTrackingNumber(int number) { trackingNumber = number; }

    void updateStatus(string t) {
        status.push(t);
    }

    bool ifrec() { return (status.reTop()) == "received"; }

    void show() {
        cout << "Sender: " << getSender() << "\n"
            << "Receiver: " << getReceiver() << "\n"
            << "Package Name: " << getPackageName() << "\n"
            << "Tracking Number: " << getTrackingNumber() << "\n"
            << "Distance: " << getDistance() << "\n"
            << "Status: " << status.reTop() << "\n";
    }
};
#endif