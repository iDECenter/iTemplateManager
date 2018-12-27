#include "aboutwindow.h"
#include "ui_aboutwindow.h"

#include "defs.h"

#include <QLayout>

AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutWindow) {
    ui->setupUi(this);

    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle("About " PROGRAM_NAME);

    ui->copyright->setText(COPYRIGHT);
    ui->version->setText(PROGRAM_NAME " " VERSION_TEXT);
    ui->description->setText(DESCRIPTION);

    connect(ui->close, &QPushButton::clicked, this, &QDialog::close);
}

AboutWindow::~AboutWindow() {
    delete ui;

    if (window != nullptr) delete window;
}

AboutWindow* AboutWindow::window = nullptr;

void AboutWindow::showAboutWindow() {
    if (window == nullptr) window = new AboutWindow();

    window->show();
}
