/*
    This file is part of Akregator.

    Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#include "kernel.h"

#include "feedlist.h"
#include "fetchqueue.h"
#include "framemanager.h"

using namespace Akregator;

Kernel *Kernel::m_self = nullptr;

Kernel *Kernel::self()
{
    static Kernel self;
    if (!m_self) {
        m_self = &self;
    }
    return m_self;
}

class Kernel::KernelPrivate
{
public:

    Backend::Storage *storage = nullptr;
    QSharedPointer<FeedList> feedList;
    FetchQueue *fetchQueue = nullptr;
    FrameManager *frameManager = nullptr;
};

Kernel::Kernel() : d(new KernelPrivate)
{
    d->fetchQueue = new FetchQueue();
    d->frameManager = new FrameManager();
    d->storage = nullptr;
}

Kernel::~Kernel()
{
    delete d->fetchQueue;
    delete d->frameManager;
    delete d;
    d = nullptr;
}

Backend::Storage *Kernel::storage()
{
    return d->storage;
}

void Kernel::setStorage(Backend::Storage *storage)
{
    d->storage = storage;
}

QSharedPointer<FeedList> Kernel::feedList() const
{
    return d->feedList;
}

void Kernel::setFeedList(const QSharedPointer<FeedList> &feedList)
{
    d->feedList = feedList;
}

FetchQueue *Kernel::fetchQueue() const
{
    return d->fetchQueue;
}

FrameManager *Kernel::frameManager() const
{
    return d->frameManager;
}
