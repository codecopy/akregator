/*
    This file is part of Akregator.

    Copyright (C) 2004 Frank Osterfeld <frank.osterfeld at kdemail.net>

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

#ifndef AKREGATORFEEDLIST_H
#define AKREGATORFEEDLIST_H

#include <qobject.h>

class QDomDocument;
class QDomNode;
class QString;
template <class T> class QValueList;

namespace Akregator
{

class Article;
class Feed;
class Folder;
class TreeNode;

/** The model of a feed tree, represents an OPML document. Contains an additional root node "All Feeds" which isn't stored. Note that a node instance must not be in more than one FeedList at a time! When deleting the feed list, all contained nodes are deleted! */

class FeedList : public QObject
{
Q_OBJECT
public:

    /** reads an OPML document and appends the items to this list
        @param doc the OPML document to parse
        @return whether parsing was successful or not (TODO: make errors more detailed)
    */
    bool readFromOPML(const QDomDocument& doc);

    FeedList(QObject *parent = 0, const char *name = 0);

    /** Destructor. Contained nodes are deleted! */
    ~FeedList();

    /** returns the root node ("All Feeds"). */
    Folder* rootNode() const;

    /** appends another feed list as sub tree. The root node of @c list is ignored. NOTE: nodes are _moved_ from @c list to this feed list, not copied */
    
    void append(FeedList* list, Folder* parent=0, TreeNode* after=0);

    /** returns the title of the feed list (as used in the OPML document) */
    const QString& title() const;

    /** sets the title of the feed list */
    void setTitle(const QString& name);

    /** exports the feed list as OPML. The root node ("All Feeds") is ignored! */
    QDomDocument toOPML() const;

    TreeNode* findByID(uint id) const;

    /** returns a feed object for a given feed URL. If the feed list does not contain a feed with @c url, NULL is returned. If it contains the same feed multiple times, any of the Feed objects is returned. */
    Feed* findByURL(const QString& feedURL) const;

    Article findArticle(const QString& feedURL, const QString& guid) const;
    
    /** returns whether the feed list is empty, root node is ignored */
    bool isEmpty() const;

    /** returns a flat list containing all nodes in the tree */
    const QValueList<TreeNode*>& asFlatList() const;

signals:
    void signalDestroyed(FeedList*);
    /** emitted when a node was added to this feed list */
    void signalNodeAdded(TreeNode*);
    /** emitted when a node was removed from this feed list */
    void signalNodeRemoved(TreeNode*);


protected slots:

    void slotNodeAdded(TreeNode* node);
//    void slotNodeChanged(TreeNode* node);
    void slotNodeDestroyed(TreeNode* node);
    void slotNodeRemoved(Folder* parent, TreeNode* node);
    
private:

    void parseChildNodes(QDomNode &node, Folder* parent);

    // never call these
    FeedList(const FeedList&) : QObject() {}
    FeedList& operator=(const FeedList&) { return *this; }

    friend class AddNodeVisitor;
    class AddNodeVisitor;

    friend class RemoveNodeVisitor;
    class RemoveNodeVisitor;
    
    class FeedListPrivate;
    FeedListPrivate* d;
};

}

#endif
