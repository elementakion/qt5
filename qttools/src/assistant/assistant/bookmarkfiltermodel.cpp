/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bookmarkfiltermodel.h"

#include "bookmarkitem.h"
#include "bookmarkmodel.h"

BookmarkFilterModel::BookmarkFilterModel(QObject *parent)
    : QAbstractProxyModel(parent)
    , hideBookmarks(true)
    , sourceModel(0)
{
}

void BookmarkFilterModel::setSourceModel(QAbstractItemModel *_sourceModel)
{
    beginResetModel();

    if (sourceModel) {
        disconnect(sourceModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
            this, SLOT(changed(QModelIndex, QModelIndex)));
        disconnect(sourceModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(rowsInserted(QModelIndex, int, int)));
        disconnect(sourceModel,
            SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
            SLOT(rowsAboutToBeRemoved(QModelIndex, int, int)));
        disconnect(sourceModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
            this, SLOT(rowsRemoved(QModelIndex, int, int)));
        disconnect(sourceModel, SIGNAL(layoutAboutToBeChanged()), this,
            SLOT(layoutAboutToBeChanged()));
        disconnect(sourceModel, SIGNAL(layoutChanged()), this,
            SLOT(layoutChanged()));
        disconnect(sourceModel, SIGNAL(modelAboutToBeReset()), this,
            SLOT(modelAboutToBeReset()));
        disconnect(sourceModel, SIGNAL(modelReset()), this, SLOT(modelReset()));
    }

    QAbstractProxyModel::setSourceModel(sourceModel);
    sourceModel = qobject_cast<BookmarkModel*> (_sourceModel);

    connect(sourceModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
        SLOT(changed(QModelIndex, QModelIndex)));

    connect(sourceModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
        this, SLOT(rowsInserted(QModelIndex, int, int)));

    connect(sourceModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
        this, SLOT(rowsAboutToBeRemoved(QModelIndex, int, int)));
    connect(sourceModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
        SLOT(rowsRemoved(QModelIndex, int, int)));

    connect(sourceModel, SIGNAL(layoutAboutToBeChanged()), this,
        SLOT(layoutAboutToBeChanged()));
    connect(sourceModel, SIGNAL(layoutChanged()), this,
        SLOT(layoutChanged()));

    connect(sourceModel, SIGNAL(modelAboutToBeReset()), this,
        SLOT(modelAboutToBeReset()));
    connect(sourceModel, SIGNAL(modelReset()), this, SLOT(modelReset()));

    if (sourceModel)
        setupCache(sourceModel->index(0, 0, QModelIndex()).parent());

    endResetModel();
}

int BookmarkFilterModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return cache.count();
}

int BookmarkFilterModel::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    if (sourceModel)
        return sourceModel->columnCount();
    return 0;
}

QModelIndex BookmarkFilterModel::mapToSource(const QModelIndex &proxyIndex) const
{
    const int row = proxyIndex.row();
    if (proxyIndex.isValid() && row >= 0 && row < cache.count())
        return cache[row];
    return QModelIndex();
}

QModelIndex BookmarkFilterModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return index(cache.indexOf(sourceIndex), 0, QModelIndex());
}

QModelIndex BookmarkFilterModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

QModelIndex BookmarkFilterModel::index(int row, int column,
    const QModelIndex &index) const
{
    Q_UNUSED(index)
    if (row < 0 || column < 0 || cache.count() <= row
        || !sourceModel || sourceModel->columnCount() <= column) {
        return QModelIndex();
    }
    return createIndex(row, 0);
}

Qt::DropActions BookmarkFilterModel::supportedDropActions () const
{
    if (sourceModel)
        return sourceModel->supportedDropActions();
    return Qt::IgnoreAction;
}

Qt::ItemFlags BookmarkFilterModel::flags(const QModelIndex &index) const
{
    if (sourceModel)
        return sourceModel->flags(index);
    return Qt::NoItemFlags;
}

QVariant BookmarkFilterModel::data(const QModelIndex &index, int role) const
{
    if (sourceModel)
        return sourceModel->data(mapToSource(index), role);
    return QVariant();
}

bool BookmarkFilterModel::setData(const QModelIndex &index, const QVariant &value,
    int role)
{
    if (sourceModel)
        return sourceModel->setData(mapToSource(index), value, role);
    return false;
}

void BookmarkFilterModel::filterBookmarks()
{
    if (sourceModel) {
        beginResetModel();
        hideBookmarks = true;
        setupCache(sourceModel->index(0, 0, QModelIndex()).parent());
        endResetModel();
    }
}

void BookmarkFilterModel::filterBookmarkFolders()
{
    if (sourceModel) {
        beginResetModel();
        hideBookmarks = false;
        setupCache(sourceModel->index(0, 0, QModelIndex()).parent());
        endResetModel();
    }
}

void BookmarkFilterModel::changed(const QModelIndex &topLeft,
    const QModelIndex &bottomRight)
{
    emit dataChanged(mapFromSource(topLeft), mapFromSource(bottomRight));
}

void BookmarkFilterModel::rowsInserted(const QModelIndex &parent, int start,
    int end)
{
    if (!sourceModel)
        return;

    QModelIndex cachePrevious = parent;
    if (BookmarkItem *parentItem = sourceModel->itemFromIndex(parent)) {
        BookmarkItem *newItem = parentItem->child(start);

        // iterate over tree hirarchie to find the previous folder
        for (int i = 0; i < parentItem->childCount(); ++i) {
            if (BookmarkItem *child = parentItem->child(i)) {
                const QModelIndex &tmp = sourceModel->indexFromItem(child);
                if (tmp.data(UserRoleFolder).toBool() && child != newItem)
                    cachePrevious = tmp;
            }
        }

        const QModelIndex &newIndex = sourceModel->indexFromItem(newItem);
        const bool isFolder = newIndex.data(UserRoleFolder).toBool();
        if ((isFolder && hideBookmarks) || (!isFolder && !hideBookmarks)) {
            beginInsertRows(mapFromSource(parent), start, end);
            const int index = cache.indexOf(cachePrevious) + 1;
            if (cache.value(index, QPersistentModelIndex()) != newIndex)
                cache.insert(index, newIndex);
            endInsertRows();
        }
    }
}

void BookmarkFilterModel::rowsAboutToBeRemoved(const QModelIndex &parent,
    int start, int end)
{
    if (!sourceModel)
        return;

    if (BookmarkItem *parentItem = sourceModel->itemFromIndex(parent)) {
        if (BookmarkItem *child = parentItem->child(start)) {
            indexToRemove = sourceModel->indexFromItem(child);
            if (cache.contains(indexToRemove))
                beginRemoveRows(mapFromSource(parent), start, end);
        }
    }
}

void BookmarkFilterModel::rowsRemoved(const QModelIndex &/*parent*/, int, int)
{
    if (cache.contains(indexToRemove)) {
        cache.removeAll(indexToRemove);
        endRemoveRows();
    }
}

void BookmarkFilterModel::layoutAboutToBeChanged()
{
    // TODO: ???
}

void BookmarkFilterModel::layoutChanged()
{
    // TODO: ???
}

void BookmarkFilterModel::modelAboutToBeReset()
{
    beginResetModel();
}

void BookmarkFilterModel::modelReset()
{
    if (sourceModel)
        setupCache(sourceModel->index(0, 0, QModelIndex()).parent());
    endResetModel();
}

void BookmarkFilterModel::setupCache(const QModelIndex &parent)
{
    cache.clear();
    for (int i = 0; i < sourceModel->rowCount(parent); ++i)
        collectItems(sourceModel->index(i, 0, parent));
}

void BookmarkFilterModel::collectItems(const QModelIndex &parent)
{
    if (parent.isValid()) {
        bool isFolder = sourceModel->data(parent, UserRoleFolder).toBool();
        if ((isFolder && hideBookmarks) || (!isFolder && !hideBookmarks))
            cache.append(parent);

        if (sourceModel->hasChildren(parent)) {
            for (int i = 0; i < sourceModel->rowCount(parent); ++i)
                collectItems(sourceModel->index(i, 0, parent));
        }
    }
}

// -- BookmarkTreeModel

BookmarkTreeModel::BookmarkTreeModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

int BookmarkTreeModel::columnCount(const QModelIndex &parent) const
{
    return qMin(1, QSortFilterProxyModel::columnCount(parent));
}

bool BookmarkTreeModel::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    Q_UNUSED(row)
    BookmarkModel *model = qobject_cast<BookmarkModel*> (sourceModel());
    if (model->rowCount(parent) > 0
        && model->data(model->index(row, 0, parent), UserRoleFolder).toBool())
        return true;
    return false;
}