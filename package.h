#ifndef package_H
#define package_H

#include<iostream>
#include <ctime> 

#include "DS.h"  // Including header file for data structures
using namespace std;

class package {
private:
    string packageName;
    string sender;
    string receiver;
    long long dist;
    int trackingNumber;

public:
    Stack<string> status;  // Status implemented using a stack

    // Constructor for the package class
    package(string packageName, string sender, string receiver, long long dist)
        : packageName(packageName), sender(sender), receiver(receiver), dist(dist) {
        // Generating a random tracking number when a package is created
        trackingNumber = 100000 + std::rand() % 900000;
        // Initial status is set to "added"
        status.push("added");
        cout << getTrackingNumber() << endl;  // Displaying the tracking number
    }

    // Overloading the less than operator for comparison based on distance
    bool operator<(const package& other) const {
        return this->dist < other.dist;
    }

    // Getter methods for package attributes
    string getPackageName() const { return packageName; }

    string getSender() const { return sender; }

    string getReceiver() const { return receiver; }

    long long getDistance() const { return dist; }

    int getTrackingNumber() const { return trackingNumber; }

    // Setter methods for package attributes
    void setPackageName(string name) { packageName = name; }

    void setSender(string s) { sender = s; }

    void setReceiver(string r) { receiver = r; }

    void setDistance(long long d) { dist = d; }

    void setTrackingNumber(int number) { trackingNumber = number; }

    // Method to update the status of the package
    void updateStatus(string t) {
        status.push(t);
    }

    // Method to check if the package has been received
    bool ifrec() { return (status.reTop()) == "received"; }

    // Method to display package details
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
