A git-svn import of Björn Höhrmann's CutyCapt.

// simple mock for argv
argc = 5;
argv = new char*[100];
argv[0] = (char *)"";
argv[1] = (char *)"--url=http://stackoverflow.com";
argv[2] = (char *)"--out=so.jpg";
argv[3] = (char *)"--quality=7";
argv[4] = (char *)"--method=get";