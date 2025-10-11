#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <qtmetamacros.h>
#include <qurl.h>
#include <qvariant.h>
#include <qwidget.h>

class HTTPRequest : public QNetworkAccessManager {
	Q_OBJECT
public:
  explicit HTTPRequest(const QUrl& url, QWidget* parent = nullptr);
  void postRequest(const QJsonObject& body);

protected:
  QUrl url;
};
