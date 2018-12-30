#include "dataholder.h"

#include "directorytreenode.h"

#include <QDebug>

DataHolder::DataHolder(QTreeWidget *view) {
    this->view = view;
}

void DataHolder::unload() {
    view->clear();
}

DirectoryTreeNode* fromDirToNode(const QDir & dir, DirectoryTreeNode *parent, QTreeWidget *parentr = nullptr) {
    DirectoryTreeNode *rv;

    if (parent) rv = new DirectoryTreeNode(parent, dir.dirName());
    else rv = new DirectoryTreeNode(parentr, dir.dirName());

    for (auto nd : dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot)) {
        rv->addChild(fromDirToNode(QDir(dir.filePath(nd)), rv));
    }

    return rv;
}

void DataHolder::loadDirectory(const QDir & dir) {
    unload();

    if (!dir.exists()) return;

    for (auto nd : dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot)) {
        view->addTopLevelItem(fromDirToNode(QDir(dir.filePath(nd)), nullptr, view));
    }
}

struct exportNodeResult {
    QJsonObject obj;
    bool useDefault;
};

exportNodeResult exportNode(DirectoryTreeNode *node, QString path) {
    QJsonObject rv, sub;

    rv.insert("path", path);

    qDebug() << path;

    bool shared = node->data(1, Qt::CheckStateRole).toBool();
    bool ignored = node->data(2, Qt::CheckStateRole).toBool();

    if (shared) {
        rv.insert("shared", true);
        rv.insert("readonly", true);
        return { rv, false };
    } else if (ignored) {
        rv.insert("ignored", true);
        return { rv, false };
    }

    bool useDefault = true;
    int count = node->childCount();
    for (int i = 0; i < count; ++i) {
        DirectoryTreeNode *nxt = reinterpret_cast<DirectoryTreeNode *>(node->child(i));
        QString subPath = nxt->text(0);
        exportNodeResult rs = exportNode(nxt, path + "/" + subPath);

        if (rs.useDefault) continue;
        else useDefault = false;
        sub.insert(subPath, rs.obj);
    }

    if (sub.count()) rv.insert("sub", sub);
    return { rv, useDefault };
}

QJsonObject DataHolder::toExport(const QString & templateName) {
    QJsonObject rv, root;
    QJsonObject sub;
    QString path = "./template/" + templateName;

    root.insert("path", path);

    int count = view->topLevelItemCount();
    for (int i = 0; i < count; ++i) {
        DirectoryTreeNode *nxt = reinterpret_cast<DirectoryTreeNode *>(view->topLevelItem(i));
        QString subPath = nxt->text(0);
        exportNodeResult rs = exportNode(nxt, path + "/" + subPath);

        if (rs.useDefault) continue;
        sub.insert(subPath, rs.obj);
    }

    if (sub.count()) root.insert("sub", sub);
    rv.insert("root", root);
    rv.insert("name", templateName);

    return rv;
}
