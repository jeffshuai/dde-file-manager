// SPDX-FileCopyrightText: 2021 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "sidebarwidget.h"

#include "treeviews/controlbar.h"

#include <QStackedLayout>

using namespace dfmplugin_sidebar;
DFMBASE_USE_NAMESPACE

SideBarWidget::SideBarWidget(QFrame *parent)
    : AbstractFrame(parent)
{
    initializeUi();
    initConnect();
}

void SideBarWidget::setCurrentUrl(const QUrl &sidebarUrl)
{
    groupWidget->setCurrentUrl(sidebarUrl);
    fileWidget->setCurrentUrl(sidebarUrl);
}

QUrl SideBarWidget::currentUrl() const
{
    auto widget { qobject_cast<AbstractFrame *>(subWidgetsStackLayout->currentWidget()) };
    return widget->currentUrl();
}

GroupTreeWidget *SideBarWidget::groupTreeWidget() const
{
    Q_ASSERT(groupWidget);
    return groupWidget;
}

FileTreeWidget *SideBarWidget::fileTreeWidget() const
{
    Q_ASSERT(fileWidget);
    return fileWidget;
}

void SideBarWidget::initializeUi()
{
    // TODO: 这里为了性能，应该从配置读取当前sidebar类型，
    // 然后只对一个widget进行初始化
    auto layout { new QVBoxLayout };
    subWidgetsStackLayout = new QStackedLayout;
    groupWidget = new GroupTreeWidget;
    fileWidget = new FileTreeWidget;
    controlBar = new ControlBar;

    layout->setContentsMargins(0, 0, 0, 0);
    subWidgetsStackLayout->setSpacing(0);
    subWidgetsStackLayout->setContentsMargins(0, 0, 0, 0);

    subWidgetsStackLayout->addWidget(groupWidget);
    subWidgetsStackLayout->addWidget(fileWidget);
    subWidgetsStackLayout->setCurrentIndex(0);
    layout->addLayout(subWidgetsStackLayout);
    layout->addWidget(controlBar);

    setLayout(layout);
}

void SideBarWidget::initConnect()
{
    connect(controlBar, &ControlBar::reqSwitchToGroupWidget, this, [this]() {
        subWidgetsStackLayout->setCurrentIndex(0);
    });

    connect(controlBar, &ControlBar::reqSwitchToFileTreeWidget, this, [this]() {
        subWidgetsStackLayout->setCurrentIndex(1);
    });
}
