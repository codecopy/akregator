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
#include "storagefactorymk4impl.h"
#include "storagemk4impl.h"

#include <KLocalizedString>
#include <QString>
#include <QStringList>

namespace Akregator {
namespace Backend {
Storage *StorageFactoryMK4Impl::createStorage(const QStringList &params) const
{
    Storage *storage = new StorageMK4Impl;
    storage->initialize(params);
    return storage;
}

QString StorageFactoryMK4Impl::key() const
{
    return QStringLiteral("metakit");
}

QString StorageFactoryMK4Impl::name() const
{
    return i18n("Metakit");
}

void StorageFactoryMK4Impl::configure()
{
}
} // namespace Backend
} // namespace Akregator
