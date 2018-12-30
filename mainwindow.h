#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataholder.h"

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString source();

private slots:
    void treeItemClicked(QTreeWidgetItem *item, int column);
    void selectSource();

    void setSource(QString source);

private:
    Ui::MainWindow *ui;
    DataHolder *holder;
};

#endif // MAINWINDOW_H
