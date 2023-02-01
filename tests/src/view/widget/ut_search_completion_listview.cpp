// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_search_completion_listview.h"
#include "view/widget/search_completion_listview.h"

#include <QSignalSpy>
#include <QStandardItemModel>

ut_search_completion_listview_test::ut_search_completion_listview_test()
{

}

TEST_F(ut_search_completion_listview_test, initDelegate)
{
    SearchCompletionListView sv;
    sv.initDelegate();
    ASSERT_TRUE(sv.m_searchCompletionDelegate);
}


TEST_F(ut_search_completion_listview_test, mousePressEvent)
{

    SearchCompletionListView sv;
    QMouseEvent *evnPressEnter;
    evnPressEnter = new QMouseEvent( QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::NoButton, Qt::NoModifier );
    sv.mousePressEvent(evnPressEnter);
    ASSERT_TRUE(sv.m_bLeftMouse);
    delete evnPressEnter;

    evnPressEnter = new QMouseEvent( QEvent::MouseButtonPress, QPoint(0, 0), Qt::RightButton, Qt::NoButton, Qt::NoModifier );
    sv.mousePressEvent(evnPressEnter);
    ASSERT_FALSE(sv.m_bLeftMouse);
    delete evnPressEnter;
}

TEST_F(ut_search_completion_listview_test, mousePressEvent2)
{
    SearchCompletionListView sv;
    QTest::mouseClick(sv.window(), Qt::LeftButton);
    ASSERT_FALSE(sv.m_bLeftMouse);
    QTest::mouseClick(sv.window(), Qt::RightButton);
    ASSERT_FALSE(sv.m_bLeftMouse);
}

TEST_F(ut_search_completion_listview_test, setSelection)
{

    SearchCompletionListView *sv = new SearchCompletionListView();
    QSignalSpy spy(sv, SIGNAL(onClickSearchCompletionItem(QModelIndex)));
    QStandardItemModel *ItemModel = new QStandardItemModel(sv);

    QStringList strList;
    strList.append("A");

    int nCount = strList.size();
    for (int i = 0; i < nCount; i++) {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        ItemModel->appendRow(item);
    }
    sv->setModel(ItemModel);
    sv->setFixedSize(200, 300);
    QRect rect(10, 10, 200, 50);
    QItemSelectionModel::SelectionFlags command;
    sv->m_bLeftMouse = true;
    sv->setSelection(rect, command);
    qWarning() << spy.count();
    QList<QVariant> argu = spy.takeFirst();
    ASSERT_EQ(sv->visualRect(argu.at(0).toModelIndex()).width(), 200);
    sv->m_bLeftMouse = false;
    sv->setSelection(rect, command);
    ASSERT_EQ(spy.count(), 0);
    delete sv;
}
