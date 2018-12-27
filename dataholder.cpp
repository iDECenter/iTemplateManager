#include "dataholder.h"

DataHolder::DataHolder(QTreeWidget *view) {
    this->view = view;
}

void DataHolder::unload() {

}

void DataHolder::loadDirectory(QDir *dir) {
    if (!dir->exists()) {
        unload(); return;
    }
}
