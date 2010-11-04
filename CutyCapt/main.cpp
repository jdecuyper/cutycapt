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

    const char* errMsg = NULL;
    char* argUrl = NULL;
    char* argUserStyle = NULL;
    char* argIconDbPath = NULL;

    QApplication app(argc, argv, true);
    CutyCapt::OutputFormat format = CutyCapt::OtherFormat;
    QString argOut = NULL;
    CutyPage page;
    QNetworkAccessManager::Operation method = QNetworkAccessManager::GetOperation;
    QByteArray body;
    QNetworkRequest req;

    CutyArgs::Parse(argc, argv, &argUrl, &errMsg, &argUserStyle, &argIconDbPath, argOut, body, &quality, page, method, argHelp, app);

    if (argUrl == NULL || argOut == NULL || argHelp) {
        if(argc == 1){
            printf("CutyCapt: %s\n", errMsg);
        } else {
            printf("CutyCapt: yes\n");
            //CutyHelp::Show();
        }
        return EXIT_FAILURE;
    }

    CutyTimer timer;
    timer.Start();

    req.setUrl( QUrl(argUrl) );

    CutyCapt main(&page, argOut, argDelay, format, quality);

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

