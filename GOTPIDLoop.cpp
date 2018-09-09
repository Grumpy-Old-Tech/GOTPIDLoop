//
//    GOTPIDLoop.cpp
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

#include "Arduino.h"
#include "GOTPIDLoop.h"

// Instantiate and set to process loop every loopTime - specify in mS
GOTPIDLoop::GOTPIDLoop(unsigned long loopTime) {
    timeToProcess = loopTime;
    lastTimeProcessed = millis();
    iMemory = 0;
    lastError = 0;
    outputMin = 0;
    outputMax = 100;
    deadband = 0;
    revAction = 0;
    inManual = false;
}

void GOTPIDLoop::reset() {
    
    iMemory = (outputMax - outputMin) / 2;
}

void GOTPIDLoop::setTuningParameters(float p, float i, float d, bool action) {
    pTerm = p;
    iTerm = i;
    dTerm = d;
    revAction = action;
}

void GOTPIDLoop::setDeadband(float db) {
    deadband = db;
}

void GOTPIDLoop::setOutputLimited(float opMin, float opMax) {
    outputMin = opMin;
    outputMax = opMax;
    iMemory = constrain(output, outputMin, outputMax);
}

void GOTPIDLoop::setManualMode() {
    
    iMemory = 0;
    inManual = true;
}

void GOTPIDLoop::setAutoMode() {
    
    iMemory = output;
    inManual = false;
}

void GOTPIDLoop::setManualValue(float opValue) {
    
    output = constrain(opValue, outputMin, outputMax);
}

void GOTPIDLoop::execute() {
    
    unsigned long loopTime = millis();
    float error;
    float pValue;
    float iValue;
    float dValue;
    float iTime;
    
    unsigned long loopDuration = loopTime - lastTimeProcessed;
    if (loopDuration > timeToProcess) {
        
        error = processVariable - setpoint;
        
        iTime = loopDuration / 1000.0;
        
        pValue = pTerm * error;
        iValue = constrain(iMemory + iTerm * error * iTime, outputMin, outputMax);
        dValue = dTerm * (error - lastError);
        
        iMemory = iValue;
        lastError = error;
        lastTimeProcessed = loopTime;
        
        if (!inManual) {
            
            output = constrain(pValue + iValue + dValue, outputMin, outputMax);
            
            if (output < deadband && output > -deadband) {
                output = 0;
            }
            
            if (revAction) {
                
                float opMidValue (outputMax - outputMin) / 2;
                float valFromMidValue = output - opMidValue;
                output = opMidValue - valFromMidValue;
            }
        }
    }
}
