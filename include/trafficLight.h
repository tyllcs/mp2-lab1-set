#pragma once
#include <iostream>
#include "tset.h"
using namespace std;

class Light {
public:
    virtual bool isGreen() const = 0;
    virtual bool isYellow() const = 0;
    virtual bool isRed() const = 0;
    virtual void switchLight() = 0;
};

class pLight : public Light {
    int size;
    TSet state;
public:
    pLight();
    void switchLight();

    virtual bool isGreen() const;
    virtual bool isYellow() const;
    virtual bool isRed() const;
};

class cLight : public Light {
    TSet state;
    int size;
public:
    cLight();
    void switchLight();
    virtual bool isGreen() const;
    virtual bool isYellow() const;
    virtual bool isRed() const;
};

class Crossroad {
    pLight pl;
    cLight cl;
public:
    Crossroad();
    void switchLight();
    ostream& printL(ostream& out, const Light& l) const;
    friend ostream& operator<< (ostream& out, const Crossroad& r);
};