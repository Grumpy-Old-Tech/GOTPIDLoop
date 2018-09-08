# GOTPIDLoop
This library implements a general purpose PID loop. Tuning, deadband, output action and output limit functionality exists. The loop processing frequency can also be set.

## LOOP EXECUTION
Loop control action will be processed at the time interval specified when the PID Loop is instaniated in milliSeconds (mS). It is important to implement the PID Loop as follows:
1. Instaniate the PID Loop with a interval time in milliseconds (mS).
2. The loop tuning and other parameters setup function should be called during the setup() using the following functions.
    setTuningParameters(float p, float i, float d, bool action);
    setDeadband(float db);
    setOutputLimited(float opMin, float opMax);
3. Call the reset() function after setting all the values.
4. The execute() function should be called in the loop() function. PID control action will only be calculated when the set time interval is complete.

## SETPOINT AND PROCESS VARIABLE
The Set Point (setpoint) and Process Variable (processVariable) properties should set set prior to calling the execute function.

## MANUAL CONTROL AND OUTPUT
After the execute function has been called the Output (output) property can be directly read. 
At any time the output can be placed in Manual mode and the output set manually using the following functions. When the loop is in manual mode the automated adjustment of the output property is disabled.
setManualMode();
setAutoMode();
setManualValue(float opValue);

Additionally a reset() function is included to allow Integral Windup to be zeroed where required.
