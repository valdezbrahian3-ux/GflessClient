#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Windows.h>
#include <QRandomGenerator>
#include <QString>
#include <QDateTime>
#include <QTimeZone>
#include <QLocale>
#include <QDebug>
#include <QCryptographicHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "syncnetworkaccessmanager.h"

class Fingerprint
{
public:
    Fingerprint() {};

    Fingerprint(
        const QJsonObject& fp,
        const QString& proxyIp,
        const QString& proxyPort,
        const QString& proxyUsername,
        const QString& proxyPassword,
        const bool useProxy
    );

    QJsonObject json() const;

    QString toString() const;

    void updateVector();

    // Always advance the fingerprint vector (ignores the 1s gate in updateVector).
    // Needed so consecutive iovation requests do not reuse a near-identical blackbox.
    void forceRotateVector();

    void updateCreation();

    void updateServerTime();

    void updateTimings();

    void setRequest(const QJsonValue& request);

private:
    static const int VERSION = 7;
    static const int UUID_LENGTH = 27;
    static const int VECTOR_LENGTH = 100;
    static const QString SERVER_FILE_GAME1_FILE;

    QJsonObject fingerprint;
    QString ip;
    QString port;
    QString username;
    QString password;
    bool proxy;

    QByteArray generateUuid() const;

    QByteArray generateVector() const;

    char randomAsciiCharacter() const;

    QByteArray randomString(int size) const;

    QString getServerDate() const;
};

#endif // FINGERPRINT_H
