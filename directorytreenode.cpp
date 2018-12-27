#include "directorytreenode.h"

#include <QMessageBox>

DirectoryTreeNode::DirectoryTreeNode(QTreeWidget *parent, QString name)
    : QTreeWidgetItem(parent, QStringList { name }) {
    init();
}

DirectoryTreeNode::DirectoryTreeNode(DirectoryTreeNode *parent, QString name)
    : QTreeWidgetItem(parent, QStringList { name }) {
    init();
}

void DirectoryTreeNode::sharedClicked() {
    if (this->isShared()) {
        if (!this->isIgnored()) {
            int count = this->childCount();
            for (int i = 0; i < count; ++i) {
                this->child(i)->setHidden(true);
            }
        }

        this->setIgnored(false);
    } else {
        if (!this->isIgnored()) {
            int count = this->childCount();
            for (int i = 0; i < count; ++i) {
                this->child(i)->setHidden(false);
            }
        }
    }
}

void DirectoryTreeNode::ignoredClicked() {
    if (this->isIgnored()) {
        if (!this->isShared()) {
            int count = this->childCount();
            for (int i = 0; i < count; ++i) {
                this->child(i)->setHidden(true);
            }
        }

        this->setShared(false);
    } else {
        if (!this->isShared()) {
            int count = this->childCount();
            for (int i = 0; i < count; ++i) {
                this->child(i)->setHidden(false);
            }
        }
    }
}

bool DirectoryTreeNode::isShared() {
    return this->data(1, Qt::CheckStateRole).toBool();
}

bool DirectoryTreeNode::isIgnored() {
    return this->data(2, Qt::CheckStateRole).toBool();
}

void DirectoryTreeNode::setShared(bool val) {
    this->setData(1, Qt::CheckStateRole, val);
}

void DirectoryTreeNode::setIgnored(bool val) {
    this->setData(2, Qt::CheckStateRole, val);
}

void DirectoryTreeNode::init() {
    this->setData(1, Qt::CheckStateRole, false);
    this->setData(2, Qt::CheckStateRole, false);
}
