#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutwindow.h"
#include "directorytreenode.h"

#include <QPushButton>
#include <QTreeWidget>
#include <QMessageBox>

#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, [](){ qApp->exit(0); });
    connect(ui->actionAbout, &QAction::triggered, [](){ AboutWindow::showAboutWindow(); });
    connect(ui->tree, &QTreeWidget::itemClicked, this, &MainWindow::treeItemClicked);

    ui->tree->setHeaderLabels(QStringList { "Directories", "Shared", "Ignored" });

    ui->tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tree->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tree->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    DirectoryTreeNode *item0 = new DirectoryTreeNode(ui->tree, "WINDOWS");
    DirectoryTreeNode *item00 = new DirectoryTreeNode(item0, "System32");
    DirectoryTreeNode *item000 = new DirectoryTreeNode(item00, "zh-cn");
    DirectoryTreeNode *item001 = new DirectoryTreeNode(item00, "en-us");
    DirectoryTreeNode *item01 = new DirectoryTreeNode(item0, "Fonts");
    DirectoryTreeNode *item1 = new DirectoryTreeNode(ui->tree, "Program Files");

    item00->addChild(item000);
    item00->addChild(item001);
    item0->addChild(item00);
    item0->addChild(item01);
    ui->tree->addTopLevelItem(item0);
    ui->tree->addTopLevelItem(item1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::treeItemClicked(QTreeWidgetItem *item, int column) {
    DirectoryTreeNode *tn = reinterpret_cast<DirectoryTreeNode*>(item);
    if (column > 0) {
        if (column == 1) tn->sharedClicked();
        if (column == 2) tn->ignoredClicked();
    }
}
