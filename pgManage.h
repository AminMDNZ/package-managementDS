#ifndef pgManage_H
#define pgManage_H

#include<iostream>
#include <functional>
#include <string>
#include <limits>

#include "DS.h"
#include "package.h"
using namespace std;

class pgmanage {

public:
    pgmanage() {};
    struct ComparePackageByDistanceGreater {
        bool operator()(const package* a, const package* b) const {
            return a->getDistance() < b->getDistance();
        }
    };
    struct ComparePackageByDistanceLess {
        bool operator()(const package* a, const package* b) const {
            return a->getDistance() > b->getDistance();
        }
    };
    LinkedList<package*> allPgs;
    LinkedList<package*> proPgs;
    Queue<package*> pgQ;
    Vector<package*, ComparePackageByDistanceGreater> pgHeapMax;
    Vector<package*, ComparePackageByDistanceLess> pgHeapMin;
    package* pgSearch(LinkedList<package*>& LinkedList);
    
    void pgChgStatus();
    void man();
    void pgSendingQ();
    void pgSendingDis();
    void addPg();
    void track();
    void showStatus();
};

void pgmanage::man() {
    while (true) {
        // pgHeapMax.buildHeap();
        // pgHeapMin.buildHeap();
        string c, c1;
        cout << "1. adding new package\n2. sending package\n3. track a package\n4. update the status\n exit. goodbye\n";
        cin >> c;
        if (c == "1") {
            addPg();
        } else if (c == "2") {
            cout << "select your priority \n1. distance\n2. queue\nelse. return\n";
            cin >> c1;
            if (c1 == "1") {
                pgSendingDis();
            } else if (c1 == "2") {
                pgSendingQ();
            }
        } else if (c == "3") {
            showStatus();    
        } 
        else if(c == "4"){
            pgChgStatus();
        }
        else if(c == "exit"){
            break;
        }
    }
}

void pgmanage::showStatus() {
    package* pg = pgSearch(allPgs);
    if (pg == nullptr)
        return;
    Stack<string> st;
    while (!pg->status.empty()) {
        st.push(pg->status.reTop());
        pg->status.pop();
    }
    int i = 1;
    while (!st.empty()) {
        cout << i << "." << st.reTop() << endl;
        pg->status.push(st.reTop());
        st.pop();
    }
}

void pgmanage::pgChgStatus() {
    package* pg = pgSearch(allPgs);
    if (pg == nullptr)
        return;
    if (pg->ifrec()) {
        cout << "the package is received, you can't change the status.\n";
        return;
    }
    cout << "write new status\n";
    string st;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, st);
    bool check = pg->status.reTop() == "sent";
    pg->updateStatus(st);
    if(pg->ifrec() && check) return;
    if(pg->ifrec() || pg->status.reTop() == "sent"){
        proPgs.deleteNode(pg);
        int dist = pg->getDistance();
        pg->setDistance(INT_MAX);
        pgHeapMax.buildHeap();
        pgHeapMax.extractRoot();
        pg->setDistance(-1);
        pgHeapMin.buildHeap();
        pgHeapMin.extractRoot();  
        pg->setDistance(dist);
    }
}

package* pgmanage::pgSearch(LinkedList<package*>& LinkedList) {
    int tr;
    cout << "Enter the tracking code: ";
    cin >> tr;
    Node<package*>* cur = allPgs.reHead();
    while (cur != nullptr) {
        if (cur->data->getTrackingNumber() == tr) {
            return cur->data;
        }
        cur = cur->next;
    }
    delete cur;
    cout << "Package with tracking number " << tr << " not found." << endl;
    return nullptr;
}

void pgmanage::addPg() {
    string pgName, sender, receiver;
    long long dis;
    cout << "enter package name, sender, receiver and distance in order\n";
    cin >> pgName >> sender >> receiver >> dis;

    package* pg = new package(pgName, sender, receiver, dis);

    pgQ.enqueue(pg);
    allPgs.insert(pg);
    pgHeapMax.push(pg);
    pgHeapMin.push(pg);
    proPgs.insert(pg);
    pgHeapMax.buildHeap();
    pgHeapMin.buildHeap();
}

void pgmanage::pgSendingDis() {
    if (pgHeapMax.empty()) {
        cout << "no remaining package." << endl;
        return;
    }
    char c;
    cout<<"1.minimum distance\n2.maximum distance\nelse.return\n";
    cin>>c;
    if(c == '1'){
        package** pfg = pgHeapMin.get(0);
        (*pfg)->show();
        cout << "enter 'y' to send the package: ";
        cin >> c;
        if (c != 'y') return;

        package* pg = pgHeapMin.extractRoot();
        pg->updateStatus("sent");    
        int dis = pg->getDistance();
        pg->setDistance(INT_MAX);      
        proPgs.deleteNode(pg);
        pgHeapMax.buildHeap();
        pgHeapMax.extractRoot();
        pg->setDistance(dis);
        proPgs.deleteNode(pg);
        cout << "Package sent:" << endl;
        pg->show();
    }
    else if(c == '2'){
        package** pfg = pgHeapMax.get(0);
        (*pfg)->show();
        cout << "enter 'y' to send the package: ";
        cin >> c;
        if (c != 'y') return;
        
        package* pg = pgHeapMax.extractRoot();
        pg->updateStatus("sent");      
        int dis = pg->getDistance();
        pg->setDistance(-1);  
        pgHeapMin.buildHeap();
        pgHeapMin.extractRoot();
        pg->setDistance(dis);
        proPgs.deleteNode(pg);
        cout << "Package sent:" << endl;
        pg->show();
    }
}

void pgmanage::pgSendingQ() {
    if (proPgs.reHead() == nullptr) {
        cout << "no remaining package." << endl;
        return;
    }
    proPgs.reHead()->data->show();
    char c;
    cout << "y to send" << endl;
    cin >> c;
    if (c != 'y')
        return;
    long long dist = proPgs.reHead()->data->getDistance();
    proPgs.reHead()->data->setDistance(-1);
    pgHeapMax.buildHeap();
    pgHeapMin.buildHeap();
    pgHeapMin.extractRoot();
    proPgs.reHead()->data->setDistance(INT_MAX);
    pgHeapMax.extractRoot();
    proPgs.reHead()->data->setDistance(dist);
    proPgs.reHead()->data->updateStatus("sent");
    cout<<"Package sent:";
    proPgs.reHead()->data->show();
    proPgs.pop();

}

#endif