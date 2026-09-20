#ifndef STOP_SIGNAL_H
#define STOP_SIGNAL_H

void installStopHandler();

void waitForStopSignal();

void signalShutdownComplete();

#endif