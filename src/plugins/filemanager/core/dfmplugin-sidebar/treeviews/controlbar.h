// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "dfmplugin_sidebar_global.h"

#include <DToolButton>

#include <QButtonGroup>
#include <QWidget>

namespace dfmplugin_sidebar {

class ControlBar : public QWidget
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);

private:
    void initializeUi();
    void initConnect();

Q_SIGNALS:
    void reqSwitchToGroupWidget();
    void reqSwitchToFileTreeWidget();

private:
    QButtonGroup *buttonGroup { nullptr };
    DTK_WIDGET_NAMESPACE::DToolButton *groupWidgetButton { nullptr };
    DTK_WIDGET_NAMESPACE::DToolButton *fileTreeWidgetButton { nullptr };
};

}   // namespace dfmplugin_sidebar

#endif   // CONTROLBAR_H
