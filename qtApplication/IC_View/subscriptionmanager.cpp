#include "subscriptionmanager.h"

SubscriptionManager::SubscriptionManager(QObject *parent)
    : QObject{parent},filepath("./subscription")
{
    watcher = new QFileSystemWatcher(this);
    watcher->addPath(filepath);

    jsonFileRegex = QRegularExpression(".*\\.json$", QRegularExpression::CaseInsensitiveOption);

    connect(watcher,&QFileSystemWatcher::fileChanged,
            this,&SubscriptionManager::onFileUpdated);
}

void SubscriptionManager::readJson()
{
    QDir dir(filepath);
    QStringList filter;
    filter<<"*.json";

    QStringList files;
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    files = dir.entryList(filter);

    if(dir.exists())
    {
        qDebug()<< "Dirctory exist";
        for(const QString &filename:files)
        {
            qDebug()<<filename;
        }
    }
}

void SubscriptionManager::onFileUpdated(const QString &fileName)
{
    qDebug()<< "File updated"<<fileName;
    if (jsonFileRegex.match(fileName).hasMatch()) {

        qDebug()<<fileName;
    }
//    if(watcher->files().contains(filepath))
    /*if(QFile::exists(filepath))
    {
        watcher->addPath(filepath);
        readJson();

    }*/

}
