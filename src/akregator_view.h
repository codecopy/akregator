/***************************************************************************
 *   Copyright (C) 2004 by Stanislav Karchebny, Sashmit Bhaduri            *
 *   Stanislav.Karchebny@kdemail.net                                       *
 *   smt@vfemail.net (Sashmit Bhaduri)                                     *
 *                                                                         *
 *   Licensed under GPL.                                                   *
 ***************************************************************************/

#ifndef _AKREGATORVIEW_H_
#define _AKREGATORVIEW_H_

#include "feed.h"
#include "feedscollection.h"

#include <qwidget.h>
#include <kurl.h>


class QSplitter;
class QGrid;
class QTabWidget;
class QDomDocument;
class QDomElement;
class QToolButton;
class QListViewItem;
class KListViewItem;
class KListView;
class KFileItem;

namespace Akregator
{
    class aKregatorPart;
    class FeedsTree;
    class FeedsTreeViewItem;
    class ArticleList;
    class ArticleViewer;
}

namespace Akregator
{
    /**
     * This is a RSS Aggregator "Part". It does all the real work.
     * It is also embeddable into other applications (e.g. for use in Kontact).
     */
    class aKregatorView : public QWidget
    {
        Q_OBJECT
        public:
            enum ViewMode { NormalView=0, WidescreenView, CombinedView };

            /**
             * Default constructor.
             */
            aKregatorView(aKregatorPart *part, QWidget *parent, const char *wName);


            /**
             * Parse OPML presentation of feeds and read in articles archive, if present.
             * @param doc QDomDocument generated from OPML by openFile().
             */
            bool loadFeeds(const QDomDocument& doc);

            /**
             * Recursively parse child nodes of the opml document, building feeds tree.
             * @param node Current node to parse.
             * @param parent Parent listview item for newly created listview items.
             */
            void parseChildNodes(QDomNode &node, QListViewItem *parent = 0);


            /**
             * Write child items of item to node using QDom document document.
             * @param item Current feeds tree item which is being written.
             * @param node Parent node to append to.
             * @param document XML document used to create nodes.
             */
            void writeChildNodes( QListViewItem *item, QDomElement &node, QDomDocument &document );

            bool event(QEvent *e);

        public slots:
            /**
             * Current item has changed.
             */
            void slotItemChanged(QListViewItem*);

            void slotNormalView();
            void slotWidescreenView();
            void slotCombinedView();

            /**
             * Shows requested popup menu
             */
            void slotContextMenu(KListView*, QListViewItem*, const QPoint&);

            /**
             * Feed has been fetched, populate article view if needed and update counters.
             */
            void slotFeedFetched(Feed *);

            /**
             * Populate article view with articles from selected feed.
             */
            void slotUpdateArticleList(FeedGroup *, bool onlyUpdateNew=false);
            void slotUpdateArticleList(Feed *, bool clear=true, bool onlyUpdateNew=false);

            /**
             * Display article contents in ArticleViewer.
             */
            void slotArticleSelected(QListViewItem *);
            void slotArticleDoubleClicked(QListViewItem *, const QPoint &, int);

            /**
             * This slot is called when user renames a feed in feeds tree.
             */
            void slotItemRenamed( QListViewItem * item ); //, const QString & text, int col

            void slotFeedAdd();
            void slotFeedAddGroup();
            void slotFeedRemove();
            void slotFeedModify();
            void slotFetchCurrentFeed();
            void slotFetchAllFeeds();
            void slotFeedURLDropped (KURL::List &urls, QListViewItem *after, QListViewItem *parent);
            
            void slotMouseOverInfo(const KFileItem *kifi);
            
            void slotOpenTab(const KURL& url);
            void slotRemoveTab();
            void slotTabChanged(QWidget *w);
            
        private:
            /**
             * Reset to default values, removing all existing data.
             * @internal
             */
            void reset();


            void addFeed(QString url, QListViewItem *after, QListViewItem* parent);
            /**
             * Add feed to feeds tree, given the existing list view item and alot of
             * feed parameters. FIXME: parameters better be bundled to FeedData?
             * @return Newly created feed.
             */
            Feed *aKregatorView::addFeed_Internal(Feed *f, QListViewItem *elt, QString title,
                                                QString xmlUrl, QString htmlUrl,
                                                QString description, bool isLiveJournal,
                                                QString ljUserName,
                                                Feed::LJAuthMode ljAuthMode,
                                                QString ljLogin, QString ljPassword,
                                                bool updateTitle);


            /**
             * A tree of all feeds (Columns, Subscriptions).
             */
            FeedsTree *m_tree;

            /**
             * An internal collection of Feed items.
             */
            FeedsCollection m_feeds;

            /**
             * List of documents for currently selected feed.
             */
            ArticleList *m_articles;

            /**
             * Currently selected article renderer.
             */
            ArticleViewer *m_articleViewer;

            /**
             * A tab widget for multiple viewers.
             */
            QTabWidget *m_tabs;
            QToolButton *m_tabsClose;
            QGrid *m_mainTab;
            
            QSplitter *m_panner1, *m_panner2;
            QValueList<int> m_panner1Sep, m_panner2Sep;
            aKregatorPart *m_part;
            ViewMode m_viewMode;
    };
}

#endif // _AKREGATORVIEW_H_
