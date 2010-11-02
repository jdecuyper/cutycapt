#ifndef CUTYARGS_H
#define CUTYARGS_H

#include "CutyPage.h"
#include <QApplication>
#include <QNetworkAccessManager>

class CutyArgs {
    public:
        static void Parse(int argc, char *argv[], char **argUrl, const char **errMsg, char **argUserStyle, char **argIconDbPath, QString &argOut, QByteArray &body, int *quality, CutyPage &page, QNetworkAccessManager::Operation &method, int argHelp, QApplication &app);
};

#endif // CUTYARGS_H
