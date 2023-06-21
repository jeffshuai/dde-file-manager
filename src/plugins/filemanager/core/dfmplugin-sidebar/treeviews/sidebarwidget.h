// SPDX-FileCopyrightText: 2021 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include "dfmplugin_sidebar_global.h"
#include "treeviews/grouptreewidget.h"
#include "treeviews/filetreewidget.h"

#include <dfm-base/interfaces/abstractframe.h>

class QAbstractItemView;
class QStackedLayout;

namespace dfmplugin_sidebar {

class SideBarWidget : public DFMBASE_NAMESPACE::AbstractFrame
{
    Q_OBJECT
public:
    explicit SideBarWidget(QFrame *parent = nullptr);

    void setCurrentUrl(const QUrl &sidebarUrl) override;
    QUrl currentUrl() const override;

    GroupTreeWidget *groupTreeWidget() const;
    FileTreeWidget *fileTreeWidget() const;

private:
    void initializeUi();
    void initConnect();

private:
    QStackedLayout *subWidgetsStackLayout { nullptr };
    GroupTreeWidget *groupWidget { nullptr };
    FileTreeWidget *fileWidget { nullptr };
};

}   // namespace dfmplugin_sidebar

#endif   // SIDEBARWIDGET_H
