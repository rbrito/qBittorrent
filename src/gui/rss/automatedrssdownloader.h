/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2010  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef AUTOMATEDRSSDOWNLOADER_H
#define AUTOMATEDRSSDOWNLOADER_H

#include <QDialog>
#include <QHideEvent>
#include <QPair>
#include <QSet>
#include <QShortcut>
#include <QShowEvent>
#include <QString>
#include <QWeakPointer>

#include "base/rss/rssdownloadrule.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AutomatedRssDownloader;
}
QT_END_NAMESPACE

namespace Rss
{
    class DownloadRuleList;
    class Manager;
}

QT_BEGIN_NAMESPACE
class QListWidgetItem;
class QRegularExpression;
QT_END_NAMESPACE

class AutomatedRssDownloader: public QDialog
{
    Q_OBJECT

public:
    explicit AutomatedRssDownloader(const QWeakPointer<Rss::Manager> &manager, QWidget *parent = 0);
    ~AutomatedRssDownloader();
    bool isRssDownloaderEnabled() const;

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

protected slots:
    void loadSettings();
    void saveSettings();
    void loadRulesList();
    void handleRuleCheckStateChange(QListWidgetItem *rule_item);
    void handleFeedCheckStateChange(QListWidgetItem *feed_item);
    void updateRuleDefinitionBox(QListWidgetItem *selected = 0);
    void clearRuleDefinitionBox();
    void saveEditedRule();
    void loadFeedList();
    void updateFeedList(QListWidgetItem *selected = 0);

private slots:
    void displayRulesListMenu(const QPoint &pos);
    void on_addRuleBtn_clicked();
    void on_removeRuleBtn_clicked();
    void on_browseSP_clicked();
    void on_exportBtn_clicked();
    void on_importBtn_clicked();
    void renameSelectedRule();
    void updateMatchingArticles();
    void updateFieldsToolTips(bool regex);
    void updateMustLineValidity();
    void updateMustNotLineValidity();
    void updateEpisodeFilterValidity();
    void onFinished(int result);

private:
    Rss::DownloadRulePtr getCurrentRule() const;
    void initCategoryCombobox();
    void addFeedArticlesToTree(const Rss::FeedPtr &feed, const QStringList &articles);
    void disconnectRuleFeedSlots();
    void connectRuleFeedSlots();

private:
    Ui::AutomatedRssDownloader *ui;
    QWeakPointer<Rss::Manager> m_manager;
    QListWidgetItem *m_editedRule;
    Rss::DownloadRuleList *m_ruleList;
    Rss::DownloadRuleList *m_editableRuleList;
    QRegularExpression *m_episodeRegex;
    QShortcut *editHotkey;
    QShortcut *deleteHotkey;
    QSet<QPair<QString, QString >> m_treeListEntries;
};

#endif // AUTOMATEDRSSDOWNLOADER_H
