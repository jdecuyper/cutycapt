#ifndef CUTYPAGE_H
#define CUTYPAGE_H

#include <QWebPage>

class CutyPage : public QWebPage {
    Q_OBJECT

    public:
        void setAttribute(QWebSettings::WebAttribute option, const QString& value);
        void setUserAgent(const QString& userAgent);
    protected:
        QString chooseFile(QWebFrame *frame, const QString& suggestedFile);
        void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);
        bool javaScriptPrompt(QWebFrame* frame, const QString& msg, const QString& defaultValue, QString* result);
        void javaScriptAlert(QWebFrame* frame, const QString& msg);
        bool javaScriptConfirm(QWebFrame* frame, const QString& msg);
        QString userAgentForUrl(const QUrl& url) const;
        QString mUserAgent;
};

#endif // CUTYPAGE_H
