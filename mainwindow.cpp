#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QDir>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileSystemModel_ = new QFileSystemModel(this);
    fileSystemModel_->setRootPath(QDir::homePath());
    fileSystemModel_->setFilter(QDir::NoDot | QDir::AllDirs | QDir::Files);

    sortFilterProxy_ = new QSortFilterProxyModel();
    sortFilterProxy_->setSourceModel(fileSystemModel_);
    sortFilterProxy_->setDynamicSortFilter(true);
    sortFilterProxy_->setSortCaseSensitivity(Qt::CaseInsensitive);
    sortFilterProxy_->setFilterKeyColumn(0);

    ui->tableView->setModel(sortFilterProxy_);
    ui->tableView->setRootIndex(sortFilterProxy_->mapFromSource(fileSystemModel_->index(fileSystemModel_->rootPath())));

    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex i = sortFilterProxy_->mapToSource(index);
    if(!i.isValid())
    {
        qDebug() << "invalid.";

        return;
    }

    if(!fileSystemModel_->isDir(i))
    {
        qDebug() << "not directory.";

        return;
    }

    QString path = fileSystemModel_->filePath(i);
    qDebug() << "dir : " << path;

    ui->tableView->setRootIndex(sortFilterProxy_->mapFromSource(fileSystemModel_->setRootPath(path)));
}

void MainWindow::on_caseSensitiveCheckBox_stateChanged(int arg1)
{
    if(ui->caseSensitiveCheckBox->isChecked())
    {
        qDebug() << "Case sensitive.";
        sortFilterProxy_->setSortCaseSensitivity(Qt::CaseSensitive);
    }
    else
    {
        qDebug() << "Case insensitive.";
        sortFilterProxy_->setSortCaseSensitivity(Qt::CaseInsensitive);
    }

    if(ui->tableView->horizontalHeader()->sortIndicatorSection() == 0)
    {
        sortFilterProxy_->sort(0, ui->tableView->horizontalHeader()->sortIndicatorOrder());
    }
}
