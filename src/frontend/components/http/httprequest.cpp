#include "httprequest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkrequest.h>
#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qlogging.h>
#include <qstringview.h>
#include <qurl.h>
#include <qvariant.h>
#include <qwidget.h>

HTTPRequest::HTTPRequest(const QUrl &url, QWidget *parent)
    : QNetworkAccessManager(parent), url(url) {}

void HTTPRequest::postRequest(const QJsonObject &body) {
  QNetworkRequest request(this->url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                       QNetworkRequest::NoLessSafeRedirectPolicy);
  QJsonDocument doc(body);
  QByteArray bodyArray = QJsonDocument(body).toJson(QJsonDocument::Compact);

  QNetworkReply *reply = this->post(request, bodyArray);
  // Logs útiles
  QObject::connect(reply, &QNetworkReply::errorOccurred,
                   [reply](QNetworkReply::NetworkError code) {
                     qWarning() << "[POST] errorOccurred:" << code
                                << reply->errorString();
                   });

  QObject::connect(reply, &QNetworkReply::sslErrors,
                   [reply](const QList<QSslError> &errs) {
                     for (const auto &e : errs)
                       qWarning() << "[POST] SSL error:" << e.errorString();
                     // reply->ignoreSslErrors(); // solo si sabes lo que haces
                   });

  QObject::connect(reply, &QNetworkReply::redirected, [](const QUrl &to) {
    qDebug() << "[POST] redirected to" << to;
  });

  QObject::connect(reply, &QNetworkReply::readyRead, [reply]() {
    qDebug() << "[POST] readyRead bytes:" << reply->bytesAvailable();
  });

  connect(reply, &QNetworkReply::finished, [reply]() {
    if (reply->error() == QNetworkReply::NoError) {
      QByteArray responseBytes = reply->readAll();
      QString responseText = QString::fromUtf8(responseBytes);
      qDebug() << "response: " << responseText;
    } else {
      qWarning() << "POST error: " << reply->errorString();
    }
    reply->deleteLater();
  });
}
