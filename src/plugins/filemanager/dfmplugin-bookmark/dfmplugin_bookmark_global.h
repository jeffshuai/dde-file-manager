/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     gongheng <gongheng@uniontech.com>
 *
 * Maintainer: zhengyouge <zhengyouge@uniontech.com>
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
#ifndef DFMPLUGIN_BOOKMARK_GLOBAL_H
#define DFMPLUGIN_BOOKMARK_GLOBAL_H

#define DPBOOKMARK_NAMESPACE dfmplugin_bookmark

#define DPBOOKMARK_BEGIN_NAMESPACE namespace DPBOOKMARK_NAMESPACE {
#define DPBOOKMARK_END_NAMESPACE }
#define DPBOOKMARK_USE_NAMESPACE using namespace DPBOOKMARK_NAMESPACE;

DPBOOKMARK_BEGIN_NAMESPACE

namespace BookmarkActionId {
static constexpr char kActAddBookmarkKey[] { "add-bookmark" };
static constexpr char kActRemoveBookmarkKey[] { "remove-bookmark" };
}

DPBOOKMARK_END_NAMESPACE

#endif   // DFMPLUGIN_BOOKMARK_GLOBAL_H
