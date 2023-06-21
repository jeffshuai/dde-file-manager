// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "filetreewidget.h"

namespace dfmplugin_sidebar {

FileTreeWidget::FileTreeWidget(QWidget *parent)
    : AbstractFrame(parent)
{
    initializeUi();
    initConnect();
}

void FileTreeWidget::setCurrentUrl(const QUrl &sidebarUrl)
{
}

QUrl FileTreeWidget::currentUrl() const
{
    return {};
}

void FileTreeWidget::initializeUi()
{
}

void FileTreeWidget::initConnect()
{
}

}   // dfmplugin_sidebar
