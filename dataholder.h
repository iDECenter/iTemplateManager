#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <QTreeWidget>
#include <QDir>

class DataHolder {
private:
    QTreeWidget *view;

public:
    DataHolder(QTreeWidget *view);

    void unload();
    void loadDirectory(QDir *dir);
};

#endif // DATAHOLDER_H
