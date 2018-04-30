#ifndef FOLDERMODEL_H
#define FOLDERMODEL_H

#include <QSortFilterProxyModel>
#include <QDir>

class QFileSystemModel;
class QFileIconProvider;

class FolderModel : public QSortFilterProxyModel
{
public:
    explicit FolderModel(QObject *parent = Q_NULLPTR);
    ~FolderModel();

    using QSortFilterProxyModel::index;
    QModelIndex index(const QString &path, int column = 0) const;

    void setSorting(QDir::SortFlags sort);
    QDir::SortFlags sorting() const;

    void setDotFirst(bool enable);
    bool dotFirst();

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE;

    void refresh();

    // QFileSystemModel specific API
    QModelIndex setRootPath(const QString &path);
    QString rootPath() const;
    QDir rootDirectory() const;

    void setIconProvider(QFileIconProvider *provider);
    QFileIconProvider *iconProvider() const;

    void setFilter(QDir::Filters filters);
    QDir::Filters filter() const;

    void setResolveSymlinks(bool enable);
    bool resolveSymlinks() const;

    void setReadOnly(bool enable);
    bool isReadOnly() const;

    void setNameFilterDisables(bool enable);
    bool nameFilterDisables() const;

    void setNameFilters(const QStringList &filters);
    QStringList nameFilters() const;

    QString filePath(const QModelIndex &index) const;
    bool isDir(const QModelIndex &index) const;
    qint64 size(const QModelIndex &index) const;
    QString type(const QModelIndex &index) const;
    QDateTime lastModified(const QModelIndex &index) const;

    QModelIndex mkdir(const QModelIndex &parent, const QString &name);
    bool rmdir(const QModelIndex &index);
    inline QString fileName(const QModelIndex &index) const;
    inline QIcon fileIcon(const QModelIndex &index) const;
    QFile::Permissions permissions(const QModelIndex &index) const;
    QFileInfo fileInfo(const QModelIndex &index) const;
    bool remove(const QModelIndex &index);

private:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;

    // don't use
    Qt::CaseSensitivity sortCaseSensitivity() const;
    void setSortCaseSensitivity(Qt::CaseSensitivity cs);

    QFileSystemModel* fsModel_;
    QDir::SortFlags sortFlags_;
    Qt::SortOrder sortOrder_;
    bool dotFirst_;
};

#endif // FOLDERMODEL_H
