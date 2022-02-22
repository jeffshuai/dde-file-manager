/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     wangchunlin<wangchunlin@uniontech.com>
 *
 * Maintainer: wangchunlin<wangchunlin@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CANVASMODELPRIVATE_H
#define CANVASMODELPRIVATE_H

#include "canvasmodel.h"
#include "dfm-base/utils/traversaldirthread.h"
#include "dfm-base/interfaces/abstractfilewatcher.h"
#include <QMutex>
#include <QQueue>

DSB_D_BEGIN_NAMESPACE

class FileTreater;
class CanvasModelPrivate : public QObject
{
    Q_OBJECT
public:
    enum EventType {
        kAddFile,
        kRmFile,
        kReFile,
        kUpdateFile
    };

    explicit CanvasModelPrivate(CanvasModel *qq);
    virtual ~CanvasModelPrivate();

    void doFileDeleted(const QUrl &url);
    void doFileCreated(const QUrl &url);
    void doFileRename(const QUrl &oldUrl, const QUrl &newUrl);
    void doFileUpdated(const QUrl &url);
    bool fileDeletedFilter(const QUrl &url);
    bool fileCreatedFilter(const QUrl &url);
    bool fileRenameFilter(const QUrl &oldUrl, const QUrl &newUrl);
    bool fileUpdatedFilter(const QUrl &url);

    Q_INVOKABLE void doWatcherEvent();

public slots:
    void onTraversalFinished();

private:
    bool checkFileEventQueue();

public:
    CanvasModel *const q;
    QUrl rootUrl;
    QSharedPointer<FileTreater> fileTreater;

    QSharedPointer<dfmbase::TraversalDirThread> traversalThread;
    AbstractFileWatcherPointer watcher;
    QMutex watcherEventMutex;
    QQueue<QVariant> watcherEvent;
    QDir::Filters filters = QDir::NoFilter;

    QAtomicInteger<bool> canFetchMoreFlag = true;
    QAtomicInteger<bool> isUpdatedChildren = false;
    QAtomicInteger<bool> processFileEventRuning = false;
    QAtomicInteger<bool> whetherShowHiddenFile = false;
};
DSB_D_END_NAMESPACE

Q_DECLARE_METATYPE(dfm_service_desktop::CanvasModelPrivate::EventType);

#endif // CANVASMODELPRIVATE_H
