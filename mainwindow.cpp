#include <QDir>
#include <QDebug>
#include <QStorageInfo>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "foldermodel.h"

using namespace Farman;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    folderModel_(new FolderModel())
{
    ui->setupUi(this);

    connect(folderModel_,
            SIGNAL(directoryLoaded(const QString&)),
            this,
            SLOT(onDirectoryLoaded(const QString&)));
//    connect(folderModel_,
//            SIGNAL(layoutChanged(const QList<QPersistentModelIndex>&, QAbstractItemModel::LayoutChangeHint)),
//            this,
//            SLOT(onLayoutChanged(const QList<QPersistentModelIndex>&, QAbstractItemModel::LayoutChangeHint)));

    for(const QStorageInfo& volume : QStorageInfo::mountedVolumes())
    {
        qDebug() << "Name : " << volume.name();
        qDebug() << "Display Name : " << volume.displayName();
        qDebug() << "Device:" << volume.device();
        qDebug() << "Root path:" << volume.rootPath();
        qDebug() << "File system type:" << volume.fileSystemType();
        qDebug() << "Is valid" << volume.isValid();
        qDebug() << "Is root" << volume.isRoot();
        qDebug() << "Is ready" << volume.isReady();
        qDebug() << "Is read only" << volume.isReadOnly();
        qDebug() << QString("Bytes available: %L1 Bytes").arg(volume.bytesAvailable());
        qDebug() << QString("Bytes free: %L1 Bytes").arg(volume.bytesFree());
        qDebug() << QString("Bytes total: %L1 Bytes").arg(volume.bytesTotal()) << endl;

        if(volume.isValid() && volume.isReady()
#ifdef Q_OS_LINUX
            && (volume.isRoot() || volume.rootPath().startsWith("/media"))
#endif
          )
        {
            ui->storageComboBox->addItem(volume.rootPath());
        }
    }

    folderModel_->setFilterFlags(FilterFlag::System);
    folderModel_->setDynamicSortFilter(false);
    folderModel_->setSortSectionType(SectionType::FileName);
    folderModel_->setSortCaseSensitivity(Qt::CaseInsensitive);
    folderModel_->setFilterKeyColumn(0);
    folderModel_->setNameFilterDisables(false);

    ui->tableView->setModel(folderModel_);

    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);

    folderModel_->setRootPath(ui->storageComboBox->itemText(0));
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

    folderModel_->setRootPath(path);
}

void MainWindow::on_caseSensitiveCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Case insensitive.";
        folderModel_->setSortCaseSensitivity(Qt::CaseInsensitive);
    }
    else
    {
        qDebug() << "Case sensitive.";
        folderModel_->setSortCaseSensitivity(Qt::CaseSensitive);
    }

    if(ui->tableView->horizontalHeader()->sortIndicatorSection() == 0)
    {
        folderModel_->refresh();
    }
}

void MainWindow::on_dirsIgnoreRadioButton_clicked()
{
    qDebug() << "Dirs ignore.";
    folderModel_->setSortDirsType(SortDirsType::NoSpecify);

    folderModel_->refresh();
}

void MainWindow::on_dirsFirstRadioButton_clicked()
{
    qDebug() << "Dirs first.";
    folderModel_->setSortDirsType(SortDirsType::First);

    folderModel_->refresh();
}

void MainWindow::on_dirsLastRadioButton_clicked()
{
    qDebug() << "Dirs last.";
    folderModel_->setSortDirsType(SortDirsType::Last);

    folderModel_->refresh();
}

void MainWindow::on_dotFirstCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Dot isn't first.";
        folderModel_->setSortDotFirst(false);
    }
    else
    {
        qDebug() << "Dot is first.";
        folderModel_->setSortDotFirst(true);
    }

    folderModel_->refresh();
}

void MainWindow::on_filterLineEdit_textEdited(const QString &arg1)
{
    folderModel_->setNameFilters(arg1.split(','));
}

void MainWindow::on_showHiddenCheckBox_stateChanged(int arg1)
{
    FilterFlags filters = folderModel_->getFilterFlags();
    if(arg1 == Qt::Unchecked)
    {
        qDebug() << "Don't show hidden file.";
        filters &= ~static_cast<uint>(FilterFlag::Hidden);
    }
    else
    {
        qDebug() << "Show hidden file.";
        filters |= FilterFlag::Hidden;
    }
    folderModel_->setFilterFlags(filters);
}

void MainWindow::on_storageComboBox_currentIndexChanged(int index)
{
    folderModel_->setRootPath(ui->storageComboBox->itemText(index));
}

void MainWindow::onDirectoryLoaded(const QString& path)
{
    qDebug() << "directory loaded." << path;

    QModelIndex newRootIndex = folderModel_->index(path);

    ui->tableView->setRootIndex(newRootIndex);
}

void MainWindow::onLayoutChanged(const QList<QPersistentModelIndex> &parents/* = QList<QPersistentModelIndex>()*/, QAbstractItemModel::LayoutChangeHint hint/* = QAbstractItemModel::NoLayoutChangeHint*/)
{
    qDebug() << "onLayoutChanged() parents : " << parents << ", hint : " << hint;


}

