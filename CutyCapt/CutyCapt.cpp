#include <QtWebKit>
#include <QtGui>
#include <QSvgGenerator>
#include "CutyCapt.h"
#include "CutyExt.h"

#ifdef STATIC_PLUGINS
  Q_IMPORT_PLUGIN(qjpeg)
  Q_IMPORT_PLUGIN(qgif)
  Q_IMPORT_PLUGIN(qtiff)
  Q_IMPORT_PLUGIN(qsvg)
  Q_IMPORT_PLUGIN(qmng)
  Q_IMPORT_PLUGIN(qico)
#endif

CutyCapt::CutyCapt()
{
}

CutyCapt::CutyCapt(CutyPage* page, const QString& output, int delay, OutputFormat format) {
  mPage = page;
  mOutput = output;
  mDelay = delay;
  mSawInitialLayout = false;
  mSawDocumentComplete = false;
  mFormat = format;
}

void CutyCapt::InitialLayoutCompleted() {
  mSawInitialLayout = true;

  if (mSawInitialLayout && mSawDocumentComplete)
    TryDelayedRender();
}

void CutyCapt::DocumentComplete(bool /*ok*/) {
  mSawDocumentComplete = true;

  if (mSawInitialLayout && mSawDocumentComplete)
    TryDelayedRender();
}

void CutyCapt::TryDelayedRender() {

  if (mDelay > 0) {
    QTimer::singleShot(mDelay, this, SLOT(Delayed()));
    return;
  }

  saveSnapshot();
  QApplication::exit();
}

void CutyCapt::Timeout() {
  saveSnapshot();
  QApplication::exit();
}

void CutyCapt::Delayed() {
  saveSnapshot();
  QApplication::exit();
}

void CutyCapt::saveSnapshot() {
    QWebFrame *mainFrame = mPage->mainFrame();
    QPainter painter;
    const char* format = NULL;

    for (int ix = 0; CutyExtMap[ix].id != OtherFormat; ++ix)
        if (CutyExtMap[ix].id == mFormat)
          format = CutyExtMap[ix].identifier; //, break;

      // TODO: sometimes contents/viewport can have size 0x0
      // in which case saving them will fail. This is likely
      // the result of the method being called too early. So
      // far I've been unable to find a workaround, except
      // using --delay with some substantial wait time. I've
      // tried to resize multiple time, make a fake render,
      // check for other events... This is primarily a problem
      // under my Ubuntu virtual machine.

      mPage->setViewportSize( mainFrame->contentsSize() );

      switch (mFormat) {
        case SvgFormat: {
          QSvgGenerator svg;
          svg.setFileName(mOutput);
          svg.setSize(mPage->viewportSize());
          painter.begin(&svg);
          mainFrame->render(&painter);
          painter.end();
          break;
        }
        case PdfFormat:
        case PsFormat: {
          QPrinter printer;
          printer.setPageSize(QPrinter::A4);
          printer.setOutputFileName(mOutput);
          // TODO: change quality here?
          mainFrame->print(&printer);
          break;
        }
        case RenderTreeFormat:
        case InnerTextFormat:
        case HtmlFormat: {
          QFile file(mOutput);
          file.open(QIODevice::WriteOnly | QIODevice::Text);
          QTextStream s(&file);
          s.setCodec("utf-8");
          s << (mFormat == RenderTreeFormat ? mainFrame->renderTreeDump() :
                mFormat == InnerTextFormat  ? mainFrame->toPlainText() :
                mFormat == HtmlFormat       ? mainFrame->toHtml() :
                "bug");
          break;
        }
        default: {
          QImage image(mPage->viewportSize(), QImage::Format_ARGB32);
          painter.begin(&image);
          mainFrame->render(&painter);
          painter.end();
          // TODO: add quality
          printf("%s", "Saving image...\n");
          image.save(mOutput, format, 10);
          emit imageWasSaved();
        }
      };
}
