// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GROUPTREEWIDGET_H
#define GROUPTREEWIDGET_H

#include "dfmplugin_sidebar_global.h"

#include <dfm-base/interfaces/abstractframe.h>

class QAbstractItemView;

namespace dfmplugin_sidebar {

class SideBarView;
class SideBarModel;
class SideBarItem;
class GroupTreeWidget : public DFMBASE_NAMESPACE::AbstractFrame
{
    Q_OBJECT

public:
    explicit GroupTreeWidget(QWidget *parent = nullptr);
    void setCurrentUrl(const QUrl &sidebarUrl) override;
    QUrl currentUrl() const override;

    QAbstractItemView *view();

    int addItem(SideBarItem *item);
    bool insertItem(const int index, SideBarItem *item);
    bool removeItem(const QUrl &url);

    void updateItem(const QUrl &url, const ItemInfo &newInfo);
    int findItem(const QUrl &url) const;
    QModelIndex findItemIndex(const QUrl &url) const;
    void editItem(const QUrl &url);
    void setItemVisiable(const QUrl &url, bool visible);
    void updateItemVisiable(const QVariantMap &states);
    QList<QUrl> findItems(const QString &group) const;
    void updateSelection();
    void saveStateWhenClose();

private Q_SLOTS:
    void onItemActived(const QModelIndex &index);
    void customContextMenuCall(const QPoint &pos);
    void onItemRenamed(const QModelIndex &index, const QString &newName);

private:
    void initializeUi();
    void initDefaultModel();
    void initConnect();

private:
    SideBarView *sidebarView { nullptr };
    static QSharedPointer<SideBarModel> kSidebarModelIns;
    QStringList currentGroups;
    QMap<QString, QString> groupDisplayName;
};

}   // namespce dfmplugin_sidebars

#endif   // GROUPTREEWIDGET_H
