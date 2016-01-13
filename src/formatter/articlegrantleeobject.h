/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ARTICLEGRANTLEEOBJECT_H
#define ARTICLEGRANTLEEOBJECT_H

#include <QObject>
#include <article.h>
#include "articleformatter.h"


namespace Akregator
{
class ArticleGrantleeObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString strippedTitle READ strippedTitle)
    Q_PROPERTY(QString author READ author)
    Q_PROPERTY(QString content READ content)
    Q_PROPERTY(QString articleLinkUrl READ articleLinkUrl)
    Q_PROPERTY(QString articlePubDate READ articlePubDate)
    Q_PROPERTY(QString enclosure READ enclosure)
    Q_PROPERTY(QString articleCompleteStoryLink READ articleCompleteStoryLink)
    Q_PROPERTY(QString imageFeed READ imageFeed)

public:
    explicit ArticleGrantleeObject(const QUrl &imageDir, const Article &article, ArticleFormatter::IconOption icon, QObject *parent = Q_NULLPTR);
    ~ArticleGrantleeObject();
    QString strippedTitle() const;
    QString author() const;
    QString content() const;
    QString articleLinkUrl() const;
    QString articlePubDate() const;
    QString enclosure() const;
    QString articleCompleteStoryLink() const;
    QString imageFeed() const;
private:
    Article mArticle;
    ArticleFormatter::IconOption mArticleFormatOption;
    QUrl mImageDir;
};
}
#endif // ARTICLEGRANTLEEOBJECT_H
