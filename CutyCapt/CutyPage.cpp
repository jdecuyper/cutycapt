#include "CutyPage.h"

void
CutyPage::setAttribute(QWebSettings::WebAttribute option, const QString& value) {

  if (value == "on")
    settings()->setAttribute(option, true);
  else if (value == "off")
    settings()->setAttribute(option, false);
  else
    (void)0; // TODO: ...
}

void
CutyPage::setUserAgent(const QString& userAgent) {
  mUserAgent = userAgent;
}

QString
CutyPage::chooseFile(QWebFrame* /*frame*/, const QString& /*suggestedFile*/) {
  return QString::null;
}

bool
CutyPage::javaScriptConfirm(QWebFrame* /*frame*/, const QString& /*msg*/) {
  return true;
}

bool
CutyPage::javaScriptPrompt(QWebFrame* /*frame*/,
                           const QString& /*msg*/,
                           const QString& /*defaultValue*/,
                           QString* /*result*/) {
  return true;
}

void
CutyPage::javaScriptConsoleMessage(const QString& /*message*/, int /*lineNumber*/, const QString& /*sourceID*/) {
  // noop
}

void
CutyPage::javaScriptAlert(QWebFrame* /*frame*/, const QString& /*msg*/) {
  // noop
}

QString
CutyPage::userAgentForUrl(const QUrl& url) const {

  if (!mUserAgent.isNull())
    return mUserAgent;

  return QWebPage::userAgentForUrl(url);
}
