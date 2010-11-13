////////////////////////////////////////////////////////////////////
//
// CutyCapt - A Qt WebKit Web Page Rendering Capture Utility
//
// Copyright (C) 2003-2008 Bjoern Hoehrmann <bjoern@hoehrmann.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// $Id$
//
////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QtWebKit>
#include <QNetworkRequest>
#include "CutyArgs.h"
#include "CutyCapt.h"
#include "CutyHelp.h"
#include "CutyTimer.h"
#include "CutyExt.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    int argHelp = 0;
    int argDelay = 0;
    int argMaxWait = 90000;
    int quality = 0;
    int isVerbose = 0;

    const char* errMsg = NULL;
    char* argUrl = NULL;
    char* argUserStyle = NULL;
    char* argIconDbPath = NULL;

    QApplication app(argc, argv, true);
    CutyCapt::OutputFormat format = CutyCapt::OtherFormat;
    QString argOut = NULL; // holds the name of the output image
    CutyPage page;
    QNetworkAccessManager::Operation method = QNetworkAccessManager::GetOperation;
    QByteArray body;
    QNetworkRequest req;

    // insert mock from README file here if you don't want to type all args from the command line at every test...

    // simple mock for argv
    argc = 5;
    argv = new char*[100];
    argv[0] = (char *)"";
    argv[1] = (char *)"--url=http://stackoverflow.com";
    argv[2] = (char *)"--out=so.png";
    argv[3] = (char *)"--quality=7";
    argv[4] = (char *)"--method=get";

    CutyArgs::Parse(argc, argv, &argUrl, &errMsg, &argUserStyle, &argIconDbPath, argOut, body, &quality, &isVerbose, page, method, &argHelp, app);

    if (argUrl == NULL || argOut == NULL || argHelp == 1) {
        if(errMsg != NULL)
            printf("CutyCapt: %s\n", errMsg);
        CutyHelp::Show();
        return EXIT_FAILURE;
    }

    CutyTimer timer;
    timer.Start();

    req.setUrl( QUrl(argUrl) );

    CutyCapt main(&page, argOut, argDelay, format, quality, isVerbose);

    app.connect(&page, SIGNAL(loadFinished(bool)), &main, SLOT(DocumentComplete(bool)));
    app.connect(&main, SIGNAL(imageWasSaved()), &timer, SLOT(Stop()));
    app.connect(page.mainFrame(), SIGNAL(initialLayoutCompleted()), &main, SLOT(InitialLayoutCompleted()));

    if (argMaxWait > 0) {
      // TODO: Should this also register one for the application?
      QTimer::singleShot(argMaxWait, &main, SLOT(Timeout()));
    }

    if (!body.isNull()) {
        page.mainFrame()->load(req, method, body);
    }
    else {
        page.mainFrame()->load(req, method);
    }
    return app.exec();
}

