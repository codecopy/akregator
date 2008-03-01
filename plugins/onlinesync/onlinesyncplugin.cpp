/*
    This file is part of Akregator.

    Copyright (C) 2008 Frank Osterfeld <osterfeld@kde.org>

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

#include "onlinesyncplugin.h"

#include <KActionCollection>
#include <KGenericFactory>
#include <KLocalizedString>

#include <QAction>

using namespace Akregator;

K_PLUGIN_FACTORY(OnlineSyncPluginFactory, registerPlugin<Akregator::OnlineSyncPlugin>();)
K_EXPORT_PLUGIN(OnlineSyncPluginFactory( "akregator_onlinesync_plugin" ) )

OnlineSyncPlugin::OnlineSyncPlugin( QObject* parent, const QVariantList& list ) : KParts::Plugin( parent )
{    
    Q_UNUSED( list )
    QAction* const action = actionCollection()->addAction( "file_onlinesync_sync" );
    action->setText( i18n( "Synchronize Feeds" ) );
    connect( action, SIGNAL( triggered( bool ) ), 
             this, SLOT( doSynchronize() ) );
 
    setXMLFile( "akregator_onlinesync_plugin.rc" , /*merge=*/true );
}

OnlineSyncPlugin::~OnlineSyncPlugin()
{
}

void OnlineSyncPlugin::doInitialize()
{
}

void OnlineSyncPlugin::doSynchronize()
{
}

#include "onlinesyncplugin.moc"