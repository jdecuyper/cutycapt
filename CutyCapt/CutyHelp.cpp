#include "CutyHelp.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void CutyHelp::Show(){
    printf("%s",
         " -----------------------------------------------------------------------------\n"
         " Usage: CutyCapt --url=http://www.google.com/ --out=google.png                \n"
         " -----------------------------------------------------------------------------\n"
         "  --help                         Print this help page and exit                \n"
         "  --url=<url>                    The URL to capture (http:...|file:...|...)   \n"
         "  --out=<path>                   The target file (.png|pdf|ps|svg|jpeg|...)   \n"
         "  --out-format=<f>               Like extension in --out, overrides heuristic \n"
         "  --quality=<int>            Output format quality from 1 to 10           \n"
         "  --min-width=<int>              Minimal width for the image (default: 800)   \n"
         "  --max-wait=<ms>                Don't wait more than (default: 90000, inf: 0)\n"
         "  --delay=<ms>                   After successful load, wait (default: 0)     \n"
         "  --user-styles=<url>            Location of user style sheet, if any         \n"
         "  --header=<name>:<value>        request header; repeatable; some can't be set\n"
         "  --method=<get|post|put>        Specifies the request method (default: get)  \n"
         "  --body-string=<string>         Unencoded request body (default: none)       \n"
         "  --body-base64=<base64>         Base64-encoded request body (default: none)  \n"
         "  --app-name=<name>              appName used in User-Agent; default is none  \n"
         "  --app-version=<version>        appVers used in User-Agent; default is none  \n"
         "  --user-agent=<string>          Override the User-Agent header Qt would set  \n"
     // The --wait-for-alert functionality could also be offered by passing a QObject to js
     //  "  --wait-for-alert=<string>      Capture and exit on script alert('string')   \n"
         "  --javascript=<on|off>          JavaScript execution (default: on)           \n"
         "  --java=<on|off>                Java execution (default: unknown)            \n"
         "  --plugins=<on|off>             Plugin execution (default: unknown)          \n"
         "  --private-browsing=<on|off>    Private browsing (default: unknown)          \n"
         "  --auto-load-images=<on|off>    Automatic image loading (default: on)        \n"
         "  --js-can-open-windows=<on|off> Script can open windows? (default: unknown)  \n"
         "  --js-can-access-clipboard=<on|off> Script clipboard privs (default: unknown)\n"
         " -----------------------------------------------------------------------------\n"
         "  <f> is svg,ps,pdf,itext,html,rtree,png,jpeg,mng,tiff,gif,bmp,ppm,xbm,xpm    \n"
         " -----------------------------------------------------------------------------\n"
         " http://cutycapt.sf.net - (c) 2003-2008 Bjoern Hoehrmann - bjoern@hoehrmann.de\n"
         "");
};
