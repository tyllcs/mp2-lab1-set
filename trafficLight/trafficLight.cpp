#include <iostream>
using namespace std;
#include "trafficLight.h"

pLight::pLight() : state(2), size(2)
{
    state.InsElem(1);
};
void pLight::switchLight() { // 0 - green 1 - red
    if (state.IsMember(0)) {
        state.DelElem(0);
        state.InsElem(1);
    }
    else {
        state.DelElem(1);
        state.InsElem(0);
    }
}

bool pLight::isGreen() const { return state.IsMember(0); };
bool pLight::isYellow() const { return false; };
bool pLight::isRed() const { return state.IsMember(1); };

cLight::cLight() : state(3), size(3) // 0 - green 1 - yellow 2 - red
{
    state.InsElem(0);
}
void cLight::switchLight() { 
    if (state.IsMember(0)) {
        state.DelElem(0);
        state.InsElem(2);
    }
    else if (state.IsMember(2)) {
        state.DelElem(2);
        state.InsElem(1);
    }
    else if (state.IsMember(1)) {
        state.DelElem(1);
        state.InsElem(0);
    }
}
bool cLight::isGreen() const { return state.IsMember(0); };
bool cLight::isYellow() const { return state.IsMember(1); };
bool cLight::isRed() const { return state.IsMember(2); };

Crossroad::Crossroad() {
    while (!cl.isRed()) { cl.switchLight(); }
    while (!pl.isGreen()) { pl.switchLight(); }
}

void Crossroad::switchLight() {
    cl.switchLight();
    if (cl.isRed()) {
        while (!pl.isGreen()) {
            pl.switchLight();
        }
    }
    else {
        while (!pl.isRed()) {
            pl.switchLight();
        }
    }
}

ostream& Crossroad::printL(ostream& out, const Light& l) const {
    if (l.isGreen()) out << "Green";
    else if (l.isYellow()) out << "Yellow";
    else if (l.isRed()) out << "Red";
    return out;
}

ostream& operator<< (ostream& out, const Crossroad& r) {
    out << "P : "; r.printL(out, r.pl) << endl;
    out << "C : "; r.printL(out, r.cl) << endl;
    return out;
}