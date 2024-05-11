#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileSystemWatcher>
#include <QList>
#include <QDebug>

class SubscriptionManager : public QObject
{
    Q_OBJECT
public:
    explicit SubscriptionManager(QObject *parent = nullptr);

    void readJson();


private:
    QFileSystemWatcher* watcher;
    QDir* dir;
    QStringList filenames;
    QString filepath;


public slots:
    void onFileUpdated(const QString &fileNam);

signals:
    void UpdateFeatureList();

};

#endif // SUBSCRIPTIONMANAGER_H
