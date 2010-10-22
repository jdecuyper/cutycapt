#ifndef CUTYTIMER_H
#define CUTYTIMER_H

#include <windows.h>
#include <QObject>
#include <QApplication>

typedef struct {
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;

class CutyTimer : public QObject {

    Q_OBJECT

    private:
     stopWatch timer;
     LARGE_INTEGER frequency;
     double LIToSecs( LARGE_INTEGER & L) ;

    public slots:
      void Stop();

    public:
        CutyTimer();
        void Start();
        double GetElapsedTime();
};

#endif // CUTYTIMER_H
