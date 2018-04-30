#include <QFileSystemModel>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include "foldermodel.h"

FolderModel::FolderModel(QObject *parent/* = Q_NULLPTR*/) :
    QSortFilterProxyModel(parent),
    fsModel_(new QFileSystemModel()),
    sortFlags_(QDir::Name | QDir::IgnoreCase),
    sortOrder_(Qt::AscendingOrder),
    dotFirst_(true)
{
    fsModel_->setRootPath(QDir::currentPath());
    fsModel_->setFilter(QDir::AllDirs | QDir::Files);

    setSourceModel(fsModel_);
}

FolderModel::~FolderModel()
{
    delete fsModel_;
}

QModelIndex FolderModel::index(const QString &path, int column/* = 0*/) const
{
    return mapFromSource(fsModel_->index(path, column));
}

void FolderModel::setSorting(QDir::SortFlags sort)
{
    sortFlags_ = sort;
}

QDir::SortFlags FolderModel::sorting() const
{
    return sortFlags_;
}

void FolderModel::setDotFirst(bool enable)
{
    dotFirst_ = enable;
}

bool FolderModel::dotFirst()
{
    return dotFirst_;
}

void FolderModel::sort(int column, Qt::SortOrder order/* = Qt::AscendingOrder*/)
{
    sortFlags_ &= ~(QDir::Name | QDir::Size | QDir::Type | QDir::Time);
    switch(column)
    {
    case 0:
        sortFlags_ |= QDir::Name;
        break;
    case 1:
        sortFlags_ |= QDir::Size;
        break;
    case 2:
        sortFlags_ |= QDir::Type;
        break;
    case 3:
        sortFlags_ |= QDir::Time;
        break;
    }

    sortOrder_ = order;

    refresh();
}

void FolderModel::refresh()
{
    QSortFilterProxyModel::sort(0, sortOrder_);
}

bool FolderModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QFileInfo l_info = fsModel_->fileInfo(source_left);
    QFileInfo r_info = fsModel_->fileInfo(source_right);
    bool ascOrder = (sortOrder_ == Qt::AscendingOrder);

    if(dotFirst_)
    {
        if(l_info.fileName() == ".")
        {
            return ascOrder;
        }
        else if(r_info.fileName() == ".")
        {
            return !ascOrder;
        }
        else if(l_info.fileName() == ".." && r_info.fileName() != ".")
        {
            return ascOrder;
        }
        else if(r_info.fileName() == ".." && l_info.fileName() != ".")
        {
            return !ascOrder;
        }
    }

    if(sortFlags_ & QDir::DirsFirst)
    {
        if(!l_info.isDir() && r_info.isDir())
        {
            return !ascOrder;
        }
        else if(l_info.isDir() && !r_info.isDir())
        {
            return ascOrder;
        }
    }
    else if(sortFlags_ & QDir::DirsLast)
    {
        if(!l_info.isDir() && r_info.isDir())
        {
            return ascOrder;
        }
        else if(l_info.isDir() && !r_info.isDir())
        {
            return !ascOrder;
        }
    }

    if(sortFlags_ & QDir::Size)
    {
        return l_info.size() < r_info.size();
    }
    else if(sortFlags_ & QDir::Type)
    {
        return l_info.completeSuffix() < r_info.completeSuffix();
    }
    else if(sortFlags_ & QDir::Time)
    {
        return l_info.lastModified() < r_info.lastModified();
    }
    else
    {
        if(sortFlags_ & QDir::IgnoreCase)
        {
            return l_info.fileName().toLower() < r_info.fileName().toLower();
        }
        else
        {
            return l_info.fileName() < r_info.fileName();
        }
    }

    return false;
}

// QFileSystemModel specific API
QModelIndex FolderModel::setRootPath(const QString &path)
{
    return mapFromSource(fsModel_->setRootPath(path));
}

QString FolderModel::rootPath() const
{
    return fsModel_->rootPath();
}

QDir FolderModel::rootDirectory() const
{
    return fsModel_->rootDirectory();
}

void FolderModel::setIconProvider(QFileIconProvider *provider)
{
    fsModel_->setIconProvider(provider);
}

QFileIconProvider* FolderModel::iconProvider() const
{
    return fsModel_->iconProvider();
}

void FolderModel::setFilter(QDir::Filters filters)
{
    fsModel_->setFilter(filters);
}

QDir::Filters FolderModel::filter() const
{
    return fsModel_->filter();
}

void FolderModel::setResolveSymlinks(bool enable)
{
    fsModel_->setResolveSymlinks(enable);
}

bool FolderModel::resolveSymlinks() const
{
    return fsModel_->resolveSymlinks();
}

void FolderModel::setReadOnly(bool enable)
{
    fsModel_->setReadOnly(enable);
}

bool FolderModel::isReadOnly() const
{
    return fsModel_->isReadOnly();
}

void FolderModel::setNameFilterDisables(bool enable)
{
    fsModel_->setNameFilterDisables(enable);
}

bool FolderModel::nameFilterDisables() const
{
    return fsModel_->nameFilterDisables();
}

void FolderModel::setNameFilters(const QStringList &filters)
{
    return fsModel_->setNameFilters(filters);
}

QStringList FolderModel::nameFilters() const
{
    return fsModel_->nameFilters();
}

QString FolderModel::filePath(const QModelIndex &index) const
{
    return fsModel_->filePath(mapToSource(index));
}

bool FolderModel::isDir(const QModelIndex &index) const
{
    return fsModel_->isDir(mapToSource(index));
}

qint64 FolderModel::size(const QModelIndex &index) const
{
    return fsModel_->size(mapToSource(index));
}

QString FolderModel::type(const QModelIndex &index) const
{
    return fsModel_->type(mapToSource(index));
}

QDateTime FolderModel::lastModified(const QModelIndex &index) const
{
    return fsModel_->lastModified(mapToSource(index));
}

QModelIndex FolderModel::mkdir(const QModelIndex &parent, const QString &name)
{
    return mapFromSource(fsModel_->mkdir(mapToSource(parent), name));
}

bool FolderModel::rmdir(const QModelIndex &index)
{
    return fsModel_->rmdir(mapToSource(index));
}

QString FolderModel::fileName(const QModelIndex &index) const
{
    return fsModel_->fileName(mapToSource(index));
}

QIcon FolderModel::fileIcon(const QModelIndex &index) const
{
    return fsModel_->fileIcon(mapToSource(index));
}

QFile::Permissions FolderModel::permissions(const QModelIndex &index) const
{
    return fsModel_->permissions(mapToSource(index));
}

QFileInfo FolderModel::fileInfo(const QModelIndex &index) const
{
    return fsModel_->fileInfo(mapToSource(index));
}

bool FolderModel::remove(const QModelIndex &index)
{
    return fsModel_->remove(mapToSource(index));
}
