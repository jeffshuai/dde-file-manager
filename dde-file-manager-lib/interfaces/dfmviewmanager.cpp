/**
 * Copyright (C) 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/
#include "dfmviewmanager.h"
#include "dfmbaseview.h"

#include "dfmviewfactory.h"
#include "dfileservices.h"

#include "views/dfileview.h"
#include "views/computerview.h"
#include "views/dfmvaultfileview.h"
#include "plugins/schemepluginmanager.h"
#include <QHash>

DFM_BEGIN_NAMESPACE

class DFMViewManagerPrivate
{
public:
    explicit DFMViewManagerPrivate(DFMViewManager *qq);

    DFMViewManager *q_ptr;

    QMultiHash<const DFMViewManager::KeyType, DFMViewManager::ViewCreatorType> controllerCreatorHash;
};

DFMViewManagerPrivate::DFMViewManagerPrivate(DFMViewManager *qq)
    : q_ptr(qq)
{

}

DFMViewManager *DFMViewManager::instance()
{
    static DFMViewManager manager;

    return &manager;
}

bool DFMViewManager::isRegisted(const QString &scheme, const QString &host, const std::type_info &info) const
{
    Q_D(const DFMViewManager);

    const KeyType &type = KeyType(scheme, host);

    for (const ViewCreatorType &value : d->controllerCreatorHash.values(type)) {
        if (value.first == info.name())
            return true;
    }

    return info == typeid(DFileView) && DFileService::instance()->isRegisted(scheme, host);
}

void DFMViewManager::clearUrlView(const QString &scheme, const QString &host)
{
    Q_D(DFMViewManager);

    const KeyType handler(scheme, host);

    d->controllerCreatorHash.remove(handler);
}
//NOTE [XIAO] 添加手机的DFileView
DFMBaseView *DFMViewManager::createViewByUrl(const DUrl &fileUrl) const
{
    Q_D(const DFMViewManager);
    QList<KeyType> handlerTypeList;

    handlerTypeList << KeyType(fileUrl.scheme(), fileUrl.host());
    handlerTypeList << KeyType(QString(), fileUrl.host());
    handlerTypeList << KeyType(fileUrl.scheme(), QString());

    for (const KeyType &handlerType : handlerTypeList) {
        const QList<ViewCreatorType> creatorList = d->controllerCreatorHash.values(handlerType);

        if (!creatorList.isEmpty()) {
            return (creatorList.first().second)();
        }

        if (DFileService::instance()->isRegisted(handlerType.first, handlerType.second)) {
            return new DFileView();
        }
    }
    return nullptr;
}

QString DFMViewManager::suitedViewTypeNameByUrl(const DUrl &fileUrl) const
{
    Q_D(const DFMViewManager);
    QList<KeyType> handlerTypeList;

    handlerTypeList << KeyType(fileUrl.scheme(), fileUrl.host());
    handlerTypeList << KeyType(QString(), fileUrl.host());
    handlerTypeList << KeyType(fileUrl.scheme(), QString());
    for (const KeyType &handlerType : handlerTypeList) {
        const QList<ViewCreatorType> creatorList = d->controllerCreatorHash.values(handlerType);

        if (!creatorList.isEmpty()) {
            return creatorList.first().first;
        }

        if (DFileService::instance()->isRegisted(handlerType.first, handlerType.second)) {
            return typeid(DFileView).name();
        }
    }

    return QString();
}

bool DFMViewManager::isSuited(const DUrl &fileUrl, const DFMBaseView *view) const
{
    const QString &type_name = suitedViewTypeNameByUrl(fileUrl);

    if (type_name == typeid(*view).name())
        return true;

    // plugin is suited
    return DFMViewFactory::viewIsSuitedWithUrl(view, fileUrl);
}

DFMViewManager::DFMViewManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DFMViewManagerPrivate(this))
{

    setObjectName(AC_FM_VIEW_MANAGER);

    dRegisterUrlView<ComputerView>(COMPUTER_SCHEME, QString());

    // vault view.
    dRegisterUrlView<DFMVaultFileView>(DFMVAULT_SCHEME, "");
    dRegisterUrlView<DFMVaultFileView>(DFMVAULT_SCHEME, "setup");
    dRegisterUrlView<DFMVaultFileView>(DFMVAULT_SCHEME, "delete");
    dRegisterUrlView<DFMVaultFileView>(DFMVAULT_SCHEME, "unlock");
    dRegisterUrlView<DFMVaultFileView>(DFMVAULT_SCHEME, "certificate");

    // register plugins
    // NOTE [XIAO] 注册手机的View
    for (const QString &key : DFMViewFactory::keys()) {
        const DUrl url(key);

        insertToCreatorHash(KeyType(url.scheme(), url.host()), ViewCreatorType(typeid(DFMViewFactory).name(), [key] {
            return DFMViewFactory::create(key);
        }));
    }

    //NOTE [XIAO] 从PLGUIN中加载View
    initViewFromPlugin();
}

//NOTE [XIAO] 从PLGUIN中加载View
void DFMViewManager::initViewFromPlugin()
{
   qWarning() << "[PLUGIN]" << "try to load plugin of view";
    for (auto plugin : SchemePluginManager::instance()->schemePlugins()){
        qWarning() << "[PLUGIN]" << "load view from plugin:" << plugin.first;
        insertToCreatorHash(KeyType(plugin.first, QString()), plugin.second->createViewTypeFunc());
    }
}

DFMViewManager::~DFMViewManager()
{

}

void DFMViewManager::insertToCreatorHash(const DFMViewManager::KeyType &type, const DFMViewManager::ViewCreatorType &creator)
{
    Q_D(DFMViewManager);

    d->controllerCreatorHash.insertMulti(type, creator);
}

DFM_END_NAMESPACE
