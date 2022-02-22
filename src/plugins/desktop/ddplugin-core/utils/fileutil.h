/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangyu<zhangyub@uniontech.com>
 *
 * Maintainer: zhangyu<zhangyub@uniontech.com>
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
#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "dfm_desktop_service_global.h"

#include "base/urlroute.h"

#include <QUrl>

DSB_D_BEGIN_NAMESPACE
#if 0 // destop should use file:// rather than desktop://.
inline QUrl covertDesktopUrlToFile(const QUrl &desktopUrl) {
    QUrl fileUrl = DFMBASE_NAMESPACE::UrlRoute::pathToUrl(
                DFMBASE_NAMESPACE::UrlRoute::urlToPath(desktopUrl),
                DFMBASE_NAMESPACE::SchemeTypes::kFile);
    return fileUrl;
}

static inline QUrl covertFileUrlToDesktop(const QUrl &fileUrl){
    QUrl desktopUrl = DFMBASE_NAMESPACE::UrlRoute::pathToReal(
                DFMBASE_NAMESPACE::UrlRoute::urlToPath(fileUrl));
    return desktopUrl;
}
#endif

DSB_D_END_NAMESPACE

#endif // FILEUTIL_H
