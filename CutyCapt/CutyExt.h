#ifndef CUTYEXT_H
#define CUTYEXT_H

#include "CutyCapt.h"

struct CutyExtMap {
    CutyCapt::OutputFormat id;
    const char* extension;
    const char* identifier;
}

const CutyExtMap[] = {
    { CutyCapt::SvgFormat,         ".svg",        "svg"   },
    { CutyCapt::PdfFormat,         ".pdf",        "pdf"   },
    { CutyCapt::PsFormat,          ".ps",         "ps"    },
    { CutyCapt::InnerTextFormat,   ".txt",        "itext" },
    { CutyCapt::HtmlFormat,        ".html",       "html"  },
    { CutyCapt::RenderTreeFormat,  ".rtree",      "rtree" },
    { CutyCapt::JpegFormat,        ".jpeg",       "jpeg"  },
    { CutyCapt::PngFormat,         ".png",        "png"   },
    { CutyCapt::MngFormat,         ".mng",        "mng"   },
    { CutyCapt::TiffFormat,        ".tiff",       "tiff"  },
    { CutyCapt::GifFormat,         ".gif",        "gif"   },
    { CutyCapt::BmpFormat,         ".bmp",        "bmp"   },
    { CutyCapt::PpmFormat,         ".ppm",        "ppm"   },
    { CutyCapt::XbmFormat,         ".xbm",        "xbm"   },
    { CutyCapt::XpmFormat,         ".xpm",        "xpm"   },
    { CutyCapt::OtherFormat,       "",            ""      }
};

#endif // CUTYEXT_H
