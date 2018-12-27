#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog {
    Q_OBJECT

private:
    static AboutWindow *window;

public:
    static void showAboutWindow();

private:
    Ui::AboutWindow *ui;

    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();
};

#endif // HELPWINDOW_H
