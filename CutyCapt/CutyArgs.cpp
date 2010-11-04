#include "CutyArgs.h"
#include "CutyPage.h"
#include "CutyCapt.h"
#include "CutyExt.h"
#include "CutyUtil.h"

#include <QApplication>
#include <QtWebKit>
#include <QNetworkRequest>
#include <stdio.h>
#include <QNetworkAccessManager>
#include <iostream>

#define INVALID_ARGS "No valid arguments were supplied (try --help)."
#define INVALID_HEADER "HTTP header supplied is not valid (try --help)."

using namespace std;

void CutyArgs::Parse(int argc, char *argv[], char **argUrl, const char **errMsg, char **argUserStyle, char **argIconDbPath, QString &argOut, QByteArray &body, int *quality, CutyPage &page, QNetworkAccessManager::Operation &method, int argHelp, QApplication &app){
    int argDelay = 0;
    int argMinWidth = 800;
    int argDefHeight = 600;
    int argMaxWait = 90000;

    QNetworkRequest req;

    CutyCapt::OutputFormat format = CutyCapt::OtherFormat;

    // Parse command line parameters
    for (int ax = 1; ax < argc; ++ax) {
       size_t nlen;

       const char* s = argv[ax];
       char* value;

       // boolean options
       if (strcmp("--help", s) == 0) {
         ++argHelp;
         break;
       }

       value = strchr(s, '=');
       if (value == NULL) {
         *errMsg = INVALID_ARGS;
         argHelp = 1;
         break;
       }

       nlen = value++ - s;

       // --name=value options
       if (strncmp("--url", s, nlen) == 0) {
           *argUrl = value;
           printf("CutyCapt: loading URL: %s \n", *argUrl);
       } else if (strncmp("--out-quality", s, nlen) == 0) {
           CutyUtil::CustomAtoi(value, quality);
       } else if (strncmp("--min-width", s, nlen) == 0) {
           CutyUtil::CustomAtoi(value, &argMinWidth);
       } else if (strncmp("--delay", s, nlen) == 0) {
           CutyUtil::CustomAtoi(value, &argDelay);
       } else if (strncmp("--max-wait", s, nlen) == 0) {
           CutyUtil::CustomAtoi(value, &argMaxWait);
       } else if (strncmp("--out", s, nlen) == 0) {
         argOut = value;
         if (format == CutyCapt::OtherFormat)
           for (int ix = 0; CutyExtMap[ix].id != CutyCapt::OtherFormat; ++ix)
             if (argOut.endsWith(CutyExtMap[ix].extension))
               format = CutyExtMap[ix].id;

       } else if (strncmp("--user-styles", s, nlen) == 0) {
         *argUserStyle = value;

       } else if (strncmp("--icon-database-path", s, nlen) == 0) {
         *argIconDbPath = value;

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
           *errMsg = INVALID_ARGS;
           argHelp = 1;
           break;
         }

       } else if (strncmp("--header", s, nlen) == 0) {
         const char* hv = strchr(value, ':');

         if (hv == NULL) {
           *errMsg = (char *)INVALID_HEADER;
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


    if (argUserStyle != NULL)
      // TODO: does this need any syntax checking?
      page.settings()->setUserStyleSheetUrl( QUrl(*argUserStyle) );

    if (argIconDbPath != NULL)
      // TODO: does this need any syntax checking?
      page.settings()->setIconDatabasePath(*argUserStyle);

    // The documentation does not say, but it seems the mainFrame
    // will never change, so we can set this here. Otherwise we'd
    // have to set this in snapshot and trigger an update, which
    // is not currently possible (Qt 4.4.0) as far as I can tell.
    page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    page.setViewportSize( QSize(argMinWidth, argDefHeight) );
}


