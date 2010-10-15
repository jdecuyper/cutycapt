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
#include "CutyCapt.h"
#include "CutyHelp.h"
#include "CutyExt.h"

int main(int argc, char *argv[])
{

    int argHelp = 0;
    int argDelay = 0;
    int argSilent = 0;
    int argMinWidth = 800;
    int argDefHeight = 600;
    int argMaxWait = 90000;
    int argVerbosity = 0;

    const char* argUrl = NULL;
    const char* argUserStyle = NULL;
    const char* argIconDbPath = NULL;
    QString argOut;

    CutyCapt::OutputFormat format = CutyCapt::OtherFormat;

    QApplication app(argc, argv, true);
    CutyPage page;

    QNetworkAccessManager::Operation method = QNetworkAccessManager::GetOperation;
    QByteArray body;
    QNetworkRequest req;

    // Parse command line parameters
    for (int ax = 1; ax < argc; ++ax) {
      size_t nlen;

      const char* s = argv[ax];
      const char* value;

      // boolean options
      if (strcmp("--silent", s) == 0) {
        argSilent = 1;
        continue;

      } else if (strcmp("--help", s) == 0) {
        argHelp = 1;
        break;

      } else if (strcmp("--verbose", s) == 0) {
        argVerbosity++;
        continue;
      }

      value = strchr(s, '=');

      if (value == NULL) {
        // TODO: error
        argHelp = 1;
        break;
      }

      nlen = value++ - s;

      // --name=value options
      if (strncmp("--url", s, nlen) == 0) {
        argUrl = value;

      } else if (strncmp("--min-width", s, nlen) == 0) {
        // TODO: add error checking here?
        argMinWidth = (unsigned int)atoi(value);

      } else if (strncmp("--delay", s, nlen) == 0) {
        // TODO: see above
        argDelay = (unsigned int)atoi(value);

      } else if (strncmp("--max-wait", s, nlen) == 0) {
        // TODO: see above
        argMaxWait = (unsigned int)atoi(value);

      } else if (strncmp("--out", s, nlen) == 0) {
        argOut = value;

        if (format == CutyCapt::OtherFormat)
          for (int ix = 0; CutyExtMap[ix].id != CutyCapt::OtherFormat; ++ix)
            if (argOut.endsWith(CutyExtMap[ix].extension))
              format = CutyExtMap[ix].id; //, break;

      } else if (strncmp("--user-styles", s, nlen) == 0) {
        argUserStyle = value;

      } else if (strncmp("--icon-database-path", s, nlen) == 0) {
        argIconDbPath = value;

      } else if (strncmp("--auto-load-images", s, nlen) == 0) {
        page.setAttribute(QWebSettings::AutoLoadImages, value);

      } else if (strncmp("--javascript", s, nlen) == 0) {
        page.setAttribute(QWebSettings::JavascriptEnabled, value);

      } else if (strncmp("--java", s, nlen) == 0) {
        page.setAttribute(QWebSettings::JavaEnabled, value);

      } else if (strncmp("--plugins", s, nlen) == 0) {
        page.setAttribute(QWebSettings::PluginsEnabled, value);

      } else if (strncmp("--private-browsing", s, nlen) == 0) {
        page.setAttribute(QWebSettings::PrivateBrowsingEnabled, value);

      } else if (strncmp("--js-can-open-windows", s, nlen) == 0) {
        page.setAttribute(QWebSettings::JavascriptCanOpenWindows, value);

      } else if (strncmp("--js-can-access-clipboard", s, nlen) == 0) {
        page.setAttribute(QWebSettings::JavascriptCanAccessClipboard, value);

      } else if (strncmp("--developer-extras", s, nlen) == 0) {
        page.setAttribute(QWebSettings::DeveloperExtrasEnabled, value);

      } else if (strncmp("--links-included-in-focus-chain", s, nlen) == 0) {
        page.setAttribute(QWebSettings::LinksIncludedInFocusChain, value);

      } else if (strncmp("--app-name", s, nlen) == 0) {
        app.setApplicationName(value);

      } else if (strncmp("--app-version", s, nlen) == 0) {
        app.setApplicationVersion(value);

      } else if (strncmp("--body-base64", s, nlen) == 0) {
        body = QByteArray::fromBase64(value);

      } else if (strncmp("--body-string", s, nlen) == 0) {
        body = QByteArray(value);

      } else if (strncmp("--user-agent", s, nlen) == 0) {
        page.setUserAgent(value);

      } else if (strncmp("--out-format", s, nlen) == 0) {
        for (int ix = 0; CutyExtMap[ix].id != CutyCapt::OtherFormat; ++ix)
          if (strcmp(value, CutyExtMap[ix].identifier) == 0)
            format = CutyExtMap[ix].id; //, break;

        if (format == CutyCapt::OtherFormat) {
          // TODO: error
          argHelp = 1;
          break;
        }

      } else if (strncmp("--header", s, nlen) == 0) {
        const char* hv = strchr(value, ':');

        if (hv == NULL) {
          // TODO: error
          argHelp = 1;
          break;
        }

        req.setRawHeader(QByteArray(value, hv - value), hv + 1);

      } else if (strncmp("--method", s, nlen) == 0) {
        if (strcmp("value", "get") == 0)
          method = QNetworkAccessManager::GetOperation;
        else if (strcmp("value", "put") == 0)
          method = QNetworkAccessManager::PutOperation;
        else if (strcmp("value", "post") == 0)
          method = QNetworkAccessManager::PostOperation;
        else if (strcmp("value", "head") == 0)
          method = QNetworkAccessManager::HeadOperation;
        else
          (void)0; // TODO: ...

      } else {
        // TODO: error
        argHelp = 1;
      }
    }

    if (argUrl == NULL || argOut == NULL || argHelp) {
        CutyHelp::Show();
        return EXIT_FAILURE;
    }

    req.setUrl( QUrl(argUrl) );

    CutyCapt main(&page, argOut, argDelay, format);

    app.connect(&page,
      SIGNAL(loadFinished(bool)),
      &main,
      SLOT(DocumentComplete(bool)));

    app.connect(page.mainFrame(),
      SIGNAL(initialLayoutCompleted()),
      &main,
      SLOT(InitialLayoutCompleted()));

    if (argMaxWait > 0) {
      // TODO: Should this also register one for the application?
      QTimer::singleShot(argMaxWait, &main, SLOT(Timeout()));
    }

    if (argUserStyle != NULL)
      // TODO: does this need any syntax checking?
      page.settings()->setUserStyleSheetUrl( QUrl(argUserStyle) );

    if (argIconDbPath != NULL)
      // TODO: does this need any syntax checking?
      page.settings()->setIconDatabasePath(argUserStyle);

    // The documentation does not say, but it seems the mainFrame
    // will never change, so we can set this here. Otherwise we'd
    // have to set this in snapshot and trigger an update, which
    // is not currently possible (Qt 4.4.0) as far as I can tell.
    page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    page.setViewportSize( QSize(argMinWidth, argDefHeight) );

    if (!body.isNull())
      page.mainFrame()->load(req, method, body);
    else
      page.mainFrame()->load(req, method);

    return app.exec();
}
