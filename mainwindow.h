#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>

namespace Ui {
class MainWindow;
}

namespace Farman
{
    class FolderModel;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_caseSensitiveCheckBox_stateChanged(int arg1);

    void on_dirsIgnoreRadioButton_clicked();

    void on_dirsFirstRadioButton_clicked();

    void on_dirsLastRadioButton_clicked();

    void on_dotFirstCheckBox_stateChanged(int arg1);

    void on_filterLineEdit_textEdited(const QString &arg1);

    void on_showHiddenCheckBox_stateChanged(int arg1);

    void on_storageComboBox_currentIndexChanged(int index);

private Q_SLOTS:
    void onDirectoryLoaded(const QString& path);
    void onLayoutChanged(const QList<QPersistentModelIndex> &parents = QList<QPersistentModelIndex>(), QAbstractItemModel::LayoutChangeHint hint = QAbstractItemModel::NoLayoutChangeHint);

private:
    Ui::MainWindow *ui;

    Farman::FolderModel* folderModel_ = Q_NULLPTR;
};

#endif // MAINWINDOW_H
