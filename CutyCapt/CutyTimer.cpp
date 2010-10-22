#include "CutyTimer.h"
#include <iostream>
#include <stdio.h>

using namespace std;

CutyTimer::CutyTimer(){
    timer.start.QuadPart=0;
    timer.stop.QuadPart=0;
    QueryPerformanceFrequency( &frequency ) ;
}

double CutyTimer::LIToSecs( LARGE_INTEGER & L) {
     return ((double)L.QuadPart /(double)frequency.QuadPart) ;
}

void CutyTimer::Start(){
    QueryPerformanceCounter(&timer.start);
}

void CutyTimer::Stop( ) {
     QueryPerformanceCounter(&timer.stop);
     cout << "Snapshot took: " << GetElapsedTime() << " seconds...\n";
}

double CutyTimer::GetElapsedTime(){
    LARGE_INTEGER time;
    time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
    return LIToSecs( time) ;
}
