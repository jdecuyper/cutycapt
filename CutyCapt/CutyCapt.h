#ifndef CUTYCAPT_H
#define CUTYCAPT_H

#include <QObject>
#include "CutyPage.h"

class CutyCapt : public QObject {
  Q_OBJECT

public:

  // TODO: This should really be elsewhere and be named differently
  enum OutputFormat { SvgFormat, PdfFormat, PsFormat, InnerTextFormat, HtmlFormat,
    RenderTreeFormat, PngFormat, JpegFormat, MngFormat, TiffFormat, GifFormat,
    BmpFormat, PpmFormat, XbmFormat, XpmFormat, OtherFormat };
  CutyCapt();
  CutyCapt(CutyPage* page, const QString& output, int delay, OutputFormat format);

private slots:
  void DocumentComplete(bool ok);
  void InitialLayoutCompleted();
  void Timeout();
  void Delayed();

private:
  void TryDelayedRender();
  void saveSnapshot();
  bool mSawInitialLayout;
  bool mSawDocumentComplete;

protected:
  QString      mOutput;
  int          mDelay;
  CutyPage*    mPage;
  OutputFormat mFormat;

};

#endif // CUTYCAPT_H
