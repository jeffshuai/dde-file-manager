#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#define private public
#define protected public

#include "views/dfilemanagerwindow.h"
#include "views/dfmsidebar.h"
#include "interfaces/dfmsidebaritem.h"
#include "controllers/dfmsidebardeviceitemhandler.h"
#include "dfmstandardpaths.h"
#include "stub.h"

DFM_USE_NAMESPACE

using namespace testing;
namespace  {
    class TestDFMSideBarDeviceItemHandler : public Test
    {
    public:
        TestDFMSideBarDeviceItemHandler():Test()
        {
            m_handler = nullptr;
        }

        virtual void SetUp() override {
            m_handler = new DFMSideBarDeviceItemHandler;
        }

        virtual void TearDown() override {
            delete  m_handler;
        }

        DFMSideBarDeviceItemHandler * m_handler;
    };
}

TEST_F(TestDFMSideBarDeviceItemHandler, create_unmount_action)
{
    QString testFile = DFMStandardPaths::location(DFMStandardPaths::PicturesPath) + "/utFile";

    QString cmdTouch = QString("touch ") + testFile;
    QString cmdRm = QString("rm ") + testFile;

    QProcess::execute(cmdTouch);

    testFile = "file://" + testFile;
    DViewItemAction *action = m_handler->createUnmountOrEjectAction(testFile, true);
    action->trigger();
    ASSERT_NE(action, nullptr);

    action->deleteLater();

    QProcess::execute(cmdRm);
}

TEST_F(TestDFMSideBarDeviceItemHandler, create_item)
{
    QString testFile = DFMStandardPaths::location(DFMStandardPaths::PicturesPath) + "/utFile";

    QString cmdTouch = QString("touch ") + testFile;
    QString cmdRm = QString("rm ") + testFile;

    QProcess::execute(cmdTouch);

    testFile = "file://" + testFile;
    DFMSideBarItem *item = m_handler->createItem(testFile);
    EXPECT_NE(nullptr, item);

    if (item)
        delete item;

    QProcess::execute(cmdRm);
}

TEST_F(TestDFMSideBarDeviceItemHandler, context_menu)
{
    Stub stub;
    void (*ut_openNewTab)() = [](){};
    // to avoid broken in DFileManagerWindow
    stub.set(ADDR(DFileManagerWindow, openNewTab), ut_openNewTab);

    DFileManagerWindow window;
    const DFMSideBar *bar = window.getLeftSideBar();

    QString testFile = DFMStandardPaths::location(DFMStandardPaths::PicturesPath) + "/utFile";

    QString cmdTouch = QString("touch ") + testFile;
    QString cmdRm = QString("rm ") + testFile;

    QProcess::execute(cmdTouch);

    testFile = "file://" + testFile;
    DFMSideBarItem *item = m_handler->createItem(testFile);
    EXPECT_NE(nullptr, item);

    if (item) {
        QMenu *menu = m_handler->contextMenu(bar, item);

        EXPECT_NE(menu, nullptr);

        delete item;
        delete menu;
    }
    QProcess::execute(cmdRm);
}

TEST_F(TestDFMSideBarDeviceItemHandler, reset_name)
{
    Stub stub;
    void (*ut_openNewTab)() = [](){};
    // to avoid broken in DFileManagerWindow
    stub.set(ADDR(DFileManagerWindow, openNewTab), ut_openNewTab);

    DFileManagerWindow window;

    QString testFile = DFMStandardPaths::location(DFMStandardPaths::PicturesPath) + "/utFile";

    QString cmdTouch = QString("touch ") + testFile;
    QString cmdRm = QString("rm ") + testFile;

    QProcess::execute(cmdTouch);

    testFile = "file://" + testFile;
    DFMSideBarItem *item = m_handler->createItem(testFile);
    EXPECT_NE(nullptr, item);

    if (item) {
        m_handler->rename(item, "renamed");
        delete item;
    }
    QProcess::execute(cmdRm);
}
