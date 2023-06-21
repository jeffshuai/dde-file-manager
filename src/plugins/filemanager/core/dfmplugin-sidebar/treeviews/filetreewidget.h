// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FILETREEWIDGET_H
#define FILETREEWIDGET_H

#include "dfmplugin_sidebar_global.h"

#include <dfm-base/interfaces/abstractframe.h>

class QStandardItemModel;
class QTreeView;
class QStandardItem;

namespace dfmplugin_sidebar {

class FileTreeWidget : public DFMBASE_NAMESPACE::AbstractFrame
{
    Q_OBJECT

public:
    explicit FileTreeWidget(QWidget *parent = nullptr);
    void setCurrentUrl(const QUrl &sidebarUrl) override;
    QUrl currentUrl() const override;

private:
    void initializeUi();
    void initConnect();
    void selectAndExpandMatchingItems(const QUrl &path, const QModelIndex &parentIndex);

private:
    quint64 windowId { 0 };
    QStandardItemModel *model { nullptr };
    QTreeView *treeView;
    QStandardItem *homeItem { nullptr };
    QUrl curUrl;
};

}   // dfmplugin_sidebar

#endif   // FILETREEWIDGET_H
