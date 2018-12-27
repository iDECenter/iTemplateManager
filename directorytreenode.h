#ifndef DIRECTORYTREENODE_H
#define DIRECTORYTREENODE_H

#include <QTreeWidget>
#include <QStringList>

class DirectoryTreeNode : public QTreeWidgetItem {
public:
    DirectoryTreeNode(QTreeWidget *parent, QString name);
    DirectoryTreeNode(DirectoryTreeNode *parent, QString name);

    bool ignored, shared;

    void sharedClicked();
    void ignoredClicked();

    bool isShared();
    bool isIgnored();

    void setShared(bool val);
    void setIgnored(bool val);

    void init();
};

#endif // DIRECTORYTREENODE_H
