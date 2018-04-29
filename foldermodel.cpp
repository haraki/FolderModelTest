#include <QFileSystemModel>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include "foldermodel.h"

FolderModel::FolderModel(QObject *parent/* = Q_NULLPTR*/) :
    QSortFilterProxyModel(parent),
    fsModel_(new QFileSystemModel())
{
    qDebug() << __FUNCTION__;
    fsModel_->setRootPath(QDir::currentPath());
    fsModel_->setFilter(QDir::NoDot | QDir::AllDirs | QDir::Files);

    setSourceModel(fsModel_);
}

FolderModel::~FolderModel()
{
    qDebug() << __FUNCTION__;
}

QModelIndex FolderModel::index(const QString &path, int column/* = 0*/) const
{
    qDebug() << __FUNCTION__;
    return mapFromSource(fsModel_->index(path, column));
}

// QFileSystemModel specific API
QModelIndex FolderModel::setRootPath(const QString &path)
{
    qDebug() << __FUNCTION__;
    return mapFromSource(fsModel_->setRootPath(path));
}

QString FolderModel::rootPath() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->rootPath();
}

QDir FolderModel::rootDirectory() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->rootDirectory();
}

void FolderModel::setIconProvider(QFileIconProvider *provider)
{
    qDebug() << __FUNCTION__;
    fsModel_->setIconProvider(provider);
}

QFileIconProvider* FolderModel::iconProvider() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->iconProvider();
}

void FolderModel::setFilter(QDir::Filters filters)
{
    qDebug() << __FUNCTION__;
    fsModel_->setFilter(filters);
}

QDir::Filters FolderModel::filter() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->filter();
}

void FolderModel::setResolveSymlinks(bool enable)
{
    qDebug() << __FUNCTION__;
    fsModel_->setResolveSymlinks(enable);
}

bool FolderModel::resolveSymlinks() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->resolveSymlinks();
}

void FolderModel::setReadOnly(bool enable)
{
    qDebug() << __FUNCTION__;
    fsModel_->setReadOnly(enable);
}

bool FolderModel::isReadOnly() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->isReadOnly();
}

void FolderModel::setNameFilterDisables(bool enable)
{
    qDebug() << __FUNCTION__;
    fsModel_->setNameFilterDisables(enable);
}

bool FolderModel::nameFilterDisables() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->nameFilterDisables();
}

void FolderModel::setNameFilters(const QStringList &filters)
{
    qDebug() << __FUNCTION__;
    return fsModel_->setNameFilters(filters);
}

QStringList FolderModel::nameFilters() const
{
    qDebug() << __FUNCTION__;
    return fsModel_->nameFilters();
}

QString FolderModel::filePath(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->filePath(mapToSource(index));
}

bool FolderModel::isDir(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->isDir(mapToSource(index));
}

qint64 FolderModel::size(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->size(mapToSource(index));
}

QString FolderModel::type(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->type(mapToSource(index));
}

QDateTime FolderModel::lastModified(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->lastModified(mapToSource(index));
}

QModelIndex FolderModel::mkdir(const QModelIndex &parent, const QString &name)
{
    qDebug() << __FUNCTION__;
    return mapFromSource(fsModel_->mkdir(mapToSource(parent), name));
}

bool FolderModel::rmdir(const QModelIndex &index)
{
    qDebug() << __FUNCTION__;
    return fsModel_->rmdir(mapToSource(index));
}

QString FolderModel::fileName(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->fileName(mapToSource(index));
}

QIcon FolderModel::fileIcon(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->fileIcon(mapToSource(index));
}

QFile::Permissions FolderModel::permissions(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->permissions(mapToSource(index));
}

QFileInfo FolderModel::fileInfo(const QModelIndex &index) const
{
    qDebug() << __FUNCTION__;
    return fsModel_->fileInfo(mapToSource(index));
}

bool FolderModel::remove(const QModelIndex &index)
{
    qDebug() << __FUNCTION__;
    return fsModel_->remove(mapToSource(index));
}
