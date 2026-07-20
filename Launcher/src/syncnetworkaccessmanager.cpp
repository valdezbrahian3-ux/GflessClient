#include "syncnetworkaccessmanager.h"
#include <QMessageBox>

SyncNetworAccesskManager::SyncNetworAccesskManager(QObject *parent) : QNetworkAccessManager(parent)
{

}

void SyncNetworAccesskManager::setErrorPopupsEnabled(bool enabled)
{
    showErrorPopups = enabled;
}

bool SyncNetworAccesskManager::errorPopupsEnabled() const
{
    return showErrorPopups;
}

void SyncNetworAccesskManager::connectErrorPopup(QNetworkReply* reply)
{
    connect(reply, &QNetworkReply::errorOccurred, this, [=]() {
        qDebug() << "Error code:" << reply->error();
        QString err = reply->errorString();
        if (showErrorPopups) {
            QMessageBox::critical(nullptr, "Error", err);
        }
    });
}

QNetworkReply* SyncNetworAccesskManager::post(const QNetworkRequest &request, const QByteArray &data)
{
    QNetworkReply* reply = QNetworkAccessManager::post(request, data);

    connectErrorPopup(reply);

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}

QNetworkReply* SyncNetworAccesskManager::get(const QNetworkRequest &request)
{
    QNetworkReply* reply = QNetworkAccessManager::get(request);

    connectErrorPopup(reply);

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}

QNetworkReply *SyncNetworAccesskManager::sendCustomRequest(const QNetworkRequest &request, const QByteArray &verb, QIODevice *data)
{
    QNetworkReply* reply = QNetworkAccessManager::sendCustomRequest(request, verb, data);

    connectErrorPopup(reply);

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}
