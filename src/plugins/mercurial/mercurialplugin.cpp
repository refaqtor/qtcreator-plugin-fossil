** Copyright (C) 2015 Brian McGillion
** Contact: http://www.qt.io/licensing
** This file is part of Qt Creator.
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
****************************************************************************/
#include <coreplugin/idocument.h>
#include <coreplugin/documentmanager.h>
#include <coreplugin/locator/commandlocator.h>
#include <vcsbase/vcsbaseconstants.h>
#include <vcsbase/vcsoutputwindow.h>
#include <QtPlugin>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QtGlobal>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#ifdef WITH_TESTS
#include <QTest>
#endif
using namespace VcsBase;
using namespace Utils;
namespace Mercurial {
namespace Internal {
static const VcsBaseEditorParameters editorParameters[] = {
{
    LogOutput,
    Constants::LOGAPP},

{   AnnotateOutput,
    Constants::ANNOTATELOG_ID,
    Constants::ANNOTATELOG_DISPLAY_NAME,
    Constants::ANNOTATEAPP},

{   DiffOutput,
    Constants::DIFFAPP}
static const VcsBaseSubmitEditorParameters submitEditorParameters = {
    VcsBaseSubmitEditorParameters::DiffFiles
        m_menuAction(0),
        m_submitActionTriggered(false)
    Core::Context context(Constants::MERCURIAL_CONTEXT);
    m_client = new MercurialClient;
    initializeVcs(new MercurialControl(m_client), context);
    addAutoReleasedObject(new OptionsPage(versionControl()));
    connect(m_client, SIGNAL(needUpdate()), this, SLOT(update()));
    const int editorCount = sizeof(editorParameters)/sizeof(editorParameters[0]);
    const auto widgetCreator = []() { return new MercurialEditorWidget; };
        addAutoReleasedObject(new VcsEditorFactory(editorParameters + i, widgetCreator, m_client, describeSlot));
    addAutoReleasedObject(new VcsSubmitEditorFactory(&submitEditorParameters,
        []() { return new CommitEditor(&submitEditorParameters); }));
    m_commandLocator = new Core::CommandLocator("Mercurial", prefix, prefix);
    createMenu(context);
void MercurialPlugin::createMenu(const Core::Context &context)
    m_mercurialContainer = Core::ActionManager::createMenu("Mercurial.MercurialMenu");
    QMenu *menu = m_mercurialContainer->menu();
    menu->setTitle(tr("Me&rcurial"));
    m_mercurialContainer->addSeparator(context);
    m_mercurialContainer->addSeparator(context);
    m_mercurialContainer->addSeparator(context);
    Core::ActionContainer *toolsMenu = Core::ActionManager::actionContainer(Core::Id(Core::Constants::M_TOOLS));
    toolsMenu->addMenu(m_mercurialContainer);
    m_menuAction = m_mercurialContainer->menu()->menuAction();
    annotateFile = new ParameterAction(tr("Annotate Current File"), tr("Annotate \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(annotateFile, Core::Id(Constants::ANNOTATE), context);
    m_mercurialContainer->addAction(command);
    diffFile = new ParameterAction(tr("Diff Current File"), tr("Diff \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(diffFile, Core::Id(Constants::DIFF), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+D") : tr("Alt+G,Alt+D")));
    m_mercurialContainer->addAction(command);
    logFile = new ParameterAction(tr("Log Current File"), tr("Log \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(logFile, Core::Id(Constants::LOG), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+L") : tr("Alt+G,Alt+L")));
    m_mercurialContainer->addAction(command);
    statusFile = new ParameterAction(tr("Status Current File"), tr("Status \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(statusFile, Core::Id(Constants::STATUS), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+S") : tr("Alt+G,Alt+S")));
    m_mercurialContainer->addAction(command);
    m_mercurialContainer->addSeparator(context);
    m_addAction = new ParameterAction(tr("Add"), tr("Add \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(m_addAction, Core::Id(Constants::ADD), context);
    m_mercurialContainer->addAction(command);
    m_deleteAction = new ParameterAction(tr("Delete..."), tr("Delete \"%1\"..."), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(m_deleteAction, Core::Id(Constants::DELETE), context);
    connect(m_deleteAction, &QAction::triggered, this, &MercurialPlugin::promptToDeleteCurrentFile);
    m_mercurialContainer->addAction(command);
    revertFile = new ParameterAction(tr("Revert Current File..."), tr("Revert \"%1\"..."), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(revertFile, Core::Id(Constants::REVERT), context);
    m_mercurialContainer->addAction(command);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    int currentLine = -1;
    if (Core::IEditor *editor = Core::EditorManager::currentEditor())
        currentLine = editor->currentLine();
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    m_client->annotate(state.currentFileTopLevel(), state.relativeCurrentFile(), QString(), currentLine);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    RevertDialog reverter(Core::ICore::dialogParent());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    auto action = new QAction(tr("Diff"), this);
    Core::Command *command = Core::ActionManager::registerAction(action, Core::Id(Constants::DIFFMULTI), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::LOGMULTI), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::REVERTMULTI), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::STATUSMULTI), context);
    m_mercurialContainer->addAction(command);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    RevertDialog reverter(Core::ICore::dialogParent());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    auto action = new QAction(tr("Pull..."), this);
    Core::Command *command = Core::ActionManager::registerAction(action, Core::Id(Constants::PULL), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::PUSH), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::UPDATE), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::IMPORT), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::INCOMING), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::OUTGOING), context);
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::COMMIT), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+C") : tr("Alt+G,Alt+C")));
    m_mercurialContainer->addAction(command);
    command = Core::ActionManager::registerAction(m_createRepositoryAction, Core::Id(Constants::CREATE_REPOSITORY), context);
    connect(m_createRepositoryAction, &QAction::triggered, this, &MercurialPlugin::createRepository);
    m_mercurialContainer->addAction(command);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    SrcDestDialog dialog(SrcDestDialog::incoming, Core::ICore::dialogParent());
    m_client->synchronousPull(dialog.workingDir(), dialog.getRepositoryString());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    SrcDestDialog dialog(SrcDestDialog::outgoing, Core::ICore::dialogParent());
    m_client->synchronousPush(dialog.workingDir(), dialog.getRepositoryString());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    RevertDialog updateDialog(Core::ICore::dialogParent());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    QFileDialog importDialog(Core::ICore::dialogParent());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    SrcDestDialog dialog(SrcDestDialog::incoming, Core::ICore::dialogParent());
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    editorCommit = new QAction(VcsBaseSubmitEditor::submitIcon(), tr("Commit"), this);
    Core::Command *command = Core::ActionManager::registerAction(editorCommit, Core::Id(Constants::COMMIT), context);
    editorDiff = new QAction(VcsBaseSubmitEditor::diffIcon(), tr("Diff &Selected Files"), this);
    Core::ActionManager::registerAction(editorDiff, Core::Id(Constants::DIFFEDITOR), context);
    Core::ActionManager::registerAction(editorUndo, Core::Id(Core::Constants::UNDO), context);
    Core::ActionManager::registerAction(editorRedo, Core::Id(Core::Constants::REDO), context);
    if (raiseSubmitEditor())
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    connect(m_client, &MercurialClient::parsedStatus, this, &MercurialPlugin::showCommitWidget);
void MercurialPlugin::showCommitWidget(const QList<VcsBaseClient::StatusItem> &status)
    disconnect(m_client, &MercurialClient::parsedStatus, this, &MercurialPlugin::showCommitWidget);
        VcsOutputWindow::appendError(tr("There are no changes to commit."));
    // Start new temp file
    TempFileSaver saver;
    // Keep the file alive, else it removes self and forgets its name
    saver.setAutoRemove(false);
    if (!saver.finalize()) {
        VcsOutputWindow::appendError(saver.errorString());
    Core::IEditor *editor = Core::EditorManager::openEditor(saver.fileName(),
                                                            Constants::COMMIT_ID);
        VcsOutputWindow::appendError(tr("Unable to create an editor for the commit."));
    QTC_ASSERT(qobject_cast<CommitEditor *>(editor), return);
    setSubmitEditor(commitEditor);

    commitEditor->registerActions(editorUndo, editorRedo, editorCommit, editorDiff);
    connect(commitEditor, &VcsBaseSubmitEditor::diffSelectedFiles,
            this, &MercurialPlugin::diffFromEditorSelected);
    commitEditor->setCheckScriptWorkingDirectory(m_submitRepository);
    commitEditor->document()->setPreferredDisplayName(msg);
    QString branch = versionControl()->vcsTopic(m_submitRepository);
                            m_client->settings().stringValue(MercurialSettings::userNameKey),
                            m_client->settings().stringValue(MercurialSettings::userEmailKey), status);
    // Close the submit editor
    m_submitActionTriggered = true;
    QTC_ASSERT(submitEditor(), return);
    Core::EditorManager::closeDocument(submitEditor()->document());
bool MercurialPlugin::submitEditorAboutToClose()
    CommitEditor *commitEditor = qobject_cast<CommitEditor *>(submitEditor());
    QTC_ASSERT(commitEditor, return true);
    Core::IDocument *editorFile = commitEditor->document();
    QTC_ASSERT(editorFile, return true);
    bool dummyPrompt = false;
    const VcsBaseSubmitEditor::PromptSubmitResult response =
                                       &dummyPrompt, !m_submitActionTriggered);
    m_submitActionTriggered = false;
    case VcsBaseSubmitEditor::SubmitCanceled:
    case VcsBaseSubmitEditor::SubmitDiscarded:
        if (!Core::DocumentManager::saveDocument(editorFile))
        m_client->commit(m_submitRepository, files, editorFile->filePath().toString(),
    //    auto action = new QAction(tr("Branch"), this);
    //    Core::Command *command = Core::ActionManager::registerAction(action, Constants::BRANCH, context);
    //    m_mercurialContainer->addAction(command);
void MercurialPlugin::updateActions(VcsBasePlugin::ActionState as)
#ifdef WITH_TESTS

void MercurialPlugin::testDiffFileResolving_data()
{
    QTest::addColumn<QByteArray>("header");
    QTest::addColumn<QByteArray>("fileName");

    QTest::newRow("New") << QByteArray(
            "diff --git a/src/plugins/mercurial/mercurialeditor.cpp b/src/plugins/mercurial/mercurialeditor.cpp\n"
            "new file mode 100644\n"
            "--- /dev/null\n"
            "+++ b/src/plugins/mercurial/mercurialeditor.cpp\n"
            "@@ -0,0 +1,112 @@\n\n")
        << QByteArray("src/plugins/mercurial/mercurialeditor.cpp");
    QTest::newRow("Deleted") << QByteArray(
            "diff --git a/src/plugins/mercurial/mercurialeditor.cpp b/src/plugins/mercurial/mercurialeditor.cpp\n"
            "deleted file mode 100644\n"
            "--- a/src/plugins/mercurial/mercurialeditor.cpp\n"
            "+++ /dev/null\n"
            "@@ -1,112 +0,0 @@\n\n")
        << QByteArray("src/plugins/mercurial/mercurialeditor.cpp");
    QTest::newRow("Normal") << QByteArray(
            "diff --git a/src/plugins/mercurial/mercurialeditor.cpp b/src/plugins/mercurial/mercurialeditor.cpp\n"
            "--- a/src/plugins/mercurial/mercurialeditor.cpp\n"
            "+++ b/src/plugins/mercurial/mercurialeditor.cpp\n"
            "@@ -49,6 +49,8 @@\n\n")
        << QByteArray("src/plugins/mercurial/mercurialeditor.cpp");
}

void MercurialPlugin::testDiffFileResolving()
{
    VcsBaseEditorWidget::testDiffFileResolving(editorParameters[2].id);
}

void MercurialPlugin::testLogResolving()
{
    QByteArray data(
                "changeset:   18473:692cbda1eb50\n"
                "branch:      stable\n"
                "bookmark:    @\n"
                "tag:         tip\n"
                "user:        FUJIWARA Katsunori <foozy@lares.dti.ne.jp>\n"
                "date:        Wed Jan 23 22:52:55 2013 +0900\n"
                "summary:     revset: evaluate sub expressions correctly (issue3775)\n"
                "\n"
                "changeset:   18472:37100f30590f\n"
                "branch:      stable\n"
                "user:        Pierre-Yves David <pierre-yves.david@ens-lyon.org>\n"
                "date:        Sat Jan 19 04:08:16 2013 +0100\n"
                "summary:     test-rebase: add another test for rebase with multiple roots\n"
                );
    VcsBaseEditorWidget::testLogResolving(editorParameters[0].id, data, "18473:692cbda1eb50", "18472:37100f30590f");
}
#endif

} // namespace Internal
} // namespace Mercurial