//
//    GOTPIDLoop.h
//
//    MIT License
//
//    Copyright (c) Saturday 1st September 2018, Neville Kripp (Grumpy Old Tech)
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.

#ifndef GOTPIDLOOP_H
#define GOTPIDLOOP_H

#include "Arduino.h"

class GOTPIDLoop
{
public:
    GOTPIDLoop(unsigned long loopTime);
    void reset();
    void setTuningParameters(float p, float i, float d, bool action);
    void setDeadband(float db);
    void setOutputLimited(float opMin, float opMax);
    void setManualMode();
    void setAutoMode();
    void setManualValue(float opValue);
    void execute();
    
private:
    unsigned long   timeToProcess;
    unsigned long   lastTimeProcessed;
    float           pTerm;
    float           iTerm;
    float           dTerm;
    bool            revAction;
    float           iMemory;
    float           lastError;
    float           outputMin;
    float           outputMax;
    float           deadband;
    bool            inManual;
    
public:
    float           setpoint;
    float           processVariable;
    float           output;
    
};

#endif
