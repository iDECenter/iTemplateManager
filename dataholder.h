#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <QJsonObject>
#include <QTreeWidget>
#include <QDir>

class DataHolder {
private:
    QTreeWidget *view;

public:
    DataHolder(QTreeWidget *view);

    void unload();
    void loadDirectory(const QDir & dir);

    QJsonObject toExport(const QString & templateName);
};

#endif // DATAHOLDER_H
