#include <QDir>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "foldermodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    folderModel_(new FolderModel())
{
    ui->setupUi(this);

    folderModel_->setRootPath(QDir::homePath());
    folderModel_->setFilter(QDir::NoDot | QDir::AllDirs | QDir::Files);
    folderModel_->setDynamicSortFilter(false);
    folderModel_->setSorting(QDir::Name | QDir::IgnoreCase);
    folderModel_->setFilterKeyColumn(0);
    folderModel_->setNameFilterDisables(false);

    ui->tableView->setModel(folderModel_);
    ui->tableView->setRootIndex(folderModel_->index(folderModel_->rootPath()));

    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(!folderModel_->isDir(index))
    {
        qDebug() << "not directory.";

        return;
    }

    QString path = folderModel_->filePath(index);
    qDebug() << "dir : " << path;

    ui->tableView->setRootIndex(folderModel_->setRootPath(path));
}

void MainWindow::on_caseSensitiveCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Case insensitive.";
        QDir::SortFlags sorting = folderModel_->sorting();
        sorting |= QDir::IgnoreCase;
        folderModel_->setSorting(sorting);
    }
    else
    {
        qDebug() << "Case sensitive.";
        QDir::SortFlags sorting = folderModel_->sorting();
        sorting &= ~QDir::IgnoreCase;
        folderModel_->setSorting(sorting);
    }

    if(ui->tableView->horizontalHeader()->sortIndicatorSection() == 0)
    {
        folderModel_->refresh();
    }
}

void MainWindow::on_dirsIgnoreRadioButton_clicked()
{
    qDebug() << "Dirs ignore.";
    QDir::SortFlags sorting = folderModel_->sorting();
    sorting &= ~(QDir::DirsFirst | QDir::DirsLast);
    folderModel_->setSorting(sorting);

    folderModel_->refresh();
}

void MainWindow::on_dirsFirstRadioButton_clicked()
{
    qDebug() << "Dirs first.";
    QDir::SortFlags sorting = folderModel_->sorting();
    sorting &= ~(QDir::DirsFirst | QDir::DirsLast);
    sorting |= QDir::DirsFirst;
    folderModel_->setSorting(sorting);

    folderModel_->refresh();
}

void MainWindow::on_dirsLastRadioButton_clicked()
{
    qDebug() << "Dirs last.";
    QDir::SortFlags sorting = folderModel_->sorting();
    sorting &= ~(QDir::DirsFirst | QDir::DirsLast);
    sorting |= QDir::DirsLast;
    folderModel_->setSorting(sorting);

    folderModel_->refresh();
}

void MainWindow::on_dotFirstCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Dot isn't first.";
        folderModel_->setDotFirst(false);
    }
    else
    {
        qDebug() << "Dot is first.";
        folderModel_->setDotFirst(true);
    }

    folderModel_->refresh();
}

void MainWindow::on_filterLineEdit_textEdited(const QString &arg1)
{
    folderModel_->setNameFilters(arg1.split(','));
}

void MainWindow::on_showHiddenCheckBox_stateChanged(int arg1)
{
    QDir::Filters filters = folderModel_->filter();
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Don't show hidden file.";
        filters &= ~QDir::Hidden;
    }
    else
    {
        qDebug() << "Show hidden file.";
        filters |= QDir::Hidden;
    }
    folderModel_->setFilter(filters);
}
