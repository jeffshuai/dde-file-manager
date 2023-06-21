// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "filetreewidget.h"
#include "utils/sidebarhelper.h"

#include <dfm-base/dfm_event_defines.h>
#include <dfm-base/utils/universalutils.h>

#include <dfm-framework/event/event.h>

#include <QTreeView>
#include <QDir>
#include <QVBoxLayout>
#include <QStandardItemModel>

namespace dfmplugin_sidebar {
DFMBASE_USE_NAMESPACE

static void buildDirectoryTreeLimited(const QString &path, QStandardItem *parentItem, int *count)
{
    (*count)++;

    if (*count > 10)
        return;

    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    foreach (const QFileInfo &entry, entries) {
        QStandardItem *item = new QStandardItem(entry.fileName());
        item->setEditable(false);
        item->setData(entry.absoluteFilePath(), Qt::UserRole);   // 保存文件路径到 UserRole

        parentItem->appendRow(item);
        buildDirectoryTreeLimited(entry.filePath(), item, count);   // 递归构建子目录
    }
}

static void buildDirectoryTree(const QString &path, QStandardItem *parentItem)
{
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    foreach (const QFileInfo &entry, entries) {
        int count = 0;
        QStandardItem *item = new QStandardItem(entry.fileName());
        item->setEditable(false);
        item->setData(entry.absoluteFilePath(), Qt::UserRole);   // 保存文件路径到 UserRole

        parentItem->appendRow(item);
        buildDirectoryTreeLimited(entry.filePath(), item, &count);   // 递归构建子目录
    }
}

FileTreeWidget::FileTreeWidget(QWidget *parent)
    : AbstractFrame(parent)
{
    initializeUi();
    initConnect();
}

void FileTreeWidget::setCurrentUrl(const QUrl &sidebarUrl)
{
    if (UniversalUtils::urlEquals(curUrl, sidebarUrl))
        return;
    curUrl = sidebarUrl;
    if (curUrl.path().startsWith(QDir::homePath()))
        selectAndExpandMatchingItems(sidebarUrl, homeItem->index());
    else
        selectAndExpandMatchingItems(sidebarUrl, model->index(0, 0));
}

QUrl FileTreeWidget::currentUrl() const
{
    return curUrl;
}

void FileTreeWidget::initializeUi()
{
    // 以下代码均为测试数据，不考虑功能、性能
    model = new QStandardItemModel;
    treeView = new QTreeView(this);
    treeView->setFrameShape(QFrame::Shape::NoFrame);
    treeView->setIconSize(QSize(16, 16));
    treeView->setHeaderHidden(true);
    treeView->setMouseTracking(true);
    treeView->setModel(model);
    windowId = SideBarHelper::windowId(this);

    // 创建第一个根 Item，显示 Linux 系统根目录的文件系统树形列表
    QStandardItem *rootItem = new QStandardItem("/");
    rootItem->setEditable(false);
    rootItem->setData("/", Qt::UserRole);   // 保存 Home 目录路径到 UserRole
    buildDirectoryTree("/", rootItem);
    model->invisibleRootItem()->appendRow(rootItem);

    // 创建第二个根 Item，显示当前用户 Home 目录的文件系统树形列表
    QString homePath = QDir::homePath();
    homeItem = new QStandardItem("Home");
    homeItem->setEditable(false);
    homeItem->setData(homePath, Qt::UserRole);   // 保存 Home 目录路径到 UserRole
    buildDirectoryTree(QDir::homePath(), homeItem);
    model->invisibleRootItem()->appendRow(homeItem);

    // 设置展开第2个根 Item
    treeView->expand(homeItem->index());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(treeView);
    setLayout(layout);
}

void FileTreeWidget::initConnect()
{
    // 连接 TreeView 的 clicked 信号到槽函数
    connect(treeView, &QTreeView::clicked, this, [&](const QModelIndex &index) {
        // 获取选中项的文件路径数据
        QVariant data = index.data(Qt::UserRole);
        if (data.isValid()) {
            QString filePath = data.toString();
            qDebug() << "Selected file path: " << filePath << windowId;
            // 在这里处理选中项的文件路径
            dpfSignalDispatcher->publish(GlobalEventType::kChangeCurrentUrl, SideBarHelper::windowId(this), QUrl::fromLocalFile(filePath));
        }
    });
}

void FileTreeWidget::selectAndExpandMatchingItems(const QUrl &path, const QModelIndex &parentIndex)
{
    QString parentFilePath = parentIndex.data(Qt::UserRole).toString();
    if (UniversalUtils::urlEquals(QUrl::fromLocalFile(parentFilePath), path)) {
        treeView->setCurrentIndex(parentIndex);   // 选中匹配的项
        treeView->expand(parentIndex);   // 展开匹配的项
        return;
    }

    int rowCount = model->rowCount(parentIndex);
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex index = model->index(row, 0, parentIndex);
        QString filePath = index.data(Qt::UserRole).toString();

        if (UniversalUtils::urlEquals(QUrl::fromLocalFile(filePath), path)) {
            treeView->setCurrentIndex(index);   // 选中匹配的项
            treeView->expand(index);   // 展开匹配的项
            return;
        }
        // 递归展开子项
        selectAndExpandMatchingItems(path, index);
    }
}

}   // dfmplugin_sidebar
