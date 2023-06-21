// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "controlbar.h"

#include <QHBoxLayout>

namespace dfmplugin_sidebar {

DWIDGET_USE_NAMESPACE

ControlBar::ControlBar(QWidget *parent)
    : QWidget(parent)
{
    initializeUi();
    initConnect();
}

void ControlBar::initializeUi()
{
    setFixedHeight(40);

    auto layout { new QHBoxLayout };
    buttonGroup = new QButtonGroup { this };
    groupWidgetButton = new DToolButton;
    fileTreeWidgetButton = new DToolButton;

    groupWidgetButton->setCheckable(true);
    groupWidgetButton->setChecked(true);
    groupWidgetButton->setIcon(QIcon::fromTheme("dfm_viewlist_icons"));
    fileTreeWidgetButton->setCheckable(true);
    fileTreeWidgetButton->setIcon(QIcon::fromTheme("dfm_viewlist_details"));

    buttonGroup->addButton(groupWidgetButton);
    buttonGroup->addButton(fileTreeWidgetButton);

    layout->setSpacing(4);
    layout->addWidget(groupWidgetButton);
    layout->addWidget(fileTreeWidgetButton);
    layout->addStretch(1);
    setLayout(layout);
}

void ControlBar::initConnect()
{
    connect(groupWidgetButton, &DToolButton::clicked, this, [this](bool checked) {
        if (checked)
            Q_EMIT reqSwitchToGroupWidget();
    });

    connect(fileTreeWidgetButton, &DToolButton::clicked, this, [this](bool checked) {
        if (checked)
            Q_EMIT reqSwitchToFileTreeWidget();
    });
}

}   // namespace dfmplugin_sidebar
