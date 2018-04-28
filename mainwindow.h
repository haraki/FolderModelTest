#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QFileSystemModel;
class QSortFilterProxyModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_caseSensitiveCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QFileSystemModel* fileSystemModel_ = Q_NULLPTR;
    QSortFilterProxyModel* sortFilterProxy_ = Q_NULLPTR;
};

#endif // MAINWINDOW_H
