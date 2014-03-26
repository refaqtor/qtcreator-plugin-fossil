** Copyright (c) 2014 Brian McGillion
** Contact: http://www.qt-project.org/legal
** This file is part of Qt Creator.
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
****************************************************************************/
#include <coreplugin/documentmanager.h>
#include <QtPlugin>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QtGlobal>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
using namespace VcsBase;
using namespace Utils;
static const VcsBaseEditorParameters editorParameters[] = {
    LogOutput,
    Constants::LOGAPP},
{   AnnotateOutput,
    Constants::ANNOTATELOG_ID,
    Constants::ANNOTATELOG_DISPLAY_NAME,
    Constants::ANNOTATELOG,
    Constants::ANNOTATEAPP},
{   DiffOutput,
    Constants::DIFFAPP}
static const VcsBaseSubmitEditorParameters submitEditorParameters = {
    Constants::COMMIT_ID,
    VcsBase::VcsBaseSubmitEditorParameters::DiffFiles
        m_menuAction(0),
        m_submitActionTriggered(false)
    typedef VcsEditorFactory<MercurialEditor> MercurialEditorFactory;
    connect(m_client, SIGNAL(needUpdate()), this, SLOT(update()));
    const int editorCount = sizeof(editorParameters)/sizeof(editorParameters[0]);
    addAutoReleasedObject(new VcsSubmitEditorFactory<CommitEditor>(&submitEditorParameters));
    m_commandLocator = new Locator::CommandLocator("Mercurial", prefix, prefix);
const MercurialSettings &MercurialPlugin::settings()
    return m_instance->mercurialSettings;
    if (settings != m_instance->mercurialSettings) {
        m_instance->mercurialSettings = settings;
        static_cast<MercurialControl *>(m_instance->versionControl())->emitConfigurationChanged();
    mercurialContainer = Core::ActionManager::createMenu("Mercurial.MercurialMenu");
    menu->setTitle(tr("Me&rcurial"));
    mercurialContainer->addSeparator(context);
    mercurialContainer->addSeparator(context);
    mercurialContainer->addSeparator(context);
    mercurialContainer->addSeparator(context);
    Core::ActionContainer *toolsMenu = Core::ActionManager::actionContainer(Core::Id(Core::Constants::M_TOOLS));
    annotateFile = new ParameterAction(tr("Annotate Current File"), tr("Annotate \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(annotateFile, Core::Id(Constants::ANNOTATE), context);
    diffFile = new ParameterAction(tr("Diff Current File"), tr("Diff \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(diffFile, Core::Id(Constants::DIFF), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+D") : tr("Alt+H,Alt+D")));
    logFile = new ParameterAction(tr("Log Current File"), tr("Log \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(logFile, Core::Id(Constants::LOG), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+L") : tr("Alt+H,Alt+L")));
    statusFile = new ParameterAction(tr("Status Current File"), tr("Status \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(statusFile, Core::Id(Constants::STATUS), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+S") : tr("Alt+H,Alt+S")));
    mercurialContainer->addSeparator(context);
    m_addAction = new ParameterAction(tr("Add"), tr("Add \"%1\""), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(m_addAction, Core::Id(Constants::ADD), context);
    m_deleteAction = new ParameterAction(tr("Delete..."), tr("Delete \"%1\"..."), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(m_deleteAction, Core::Id(Constants::DELETE), context);
    revertFile = new ParameterAction(tr("Revert Current File..."), tr("Revert \"%1\"..."), ParameterAction::EnabledWithParameter, this);
    command = Core::ActionManager::registerAction(revertFile, Core::Id(Constants::REVERT), context);
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
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::DIFFMULTI), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::LOGMULTI), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::REVERTMULTI), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::STATUSMULTI), context);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    Core::Command *command = Core::ActionManager::registerAction(action, Core::Id(Constants::PULL), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::PUSH), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::UPDATE), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::IMPORT), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::INCOMING), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::OUTGOING), context);
    command = Core::ActionManager::registerAction(action, Core::Id(Constants::COMMIT), context);
    command->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+H,Meta+C") : tr("Alt+H,Alt+C")));
    command = Core::ActionManager::registerAction(m_createRepositoryAction, Core::Id(Constants::CREATE_REPOSITORY), context);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    editorCommit = new QAction(VcsBaseSubmitEditor::submitIcon(), tr("Commit"), this);
    command = Core::ActionManager::registerAction(editorCommit, Core::Id(Constants::COMMIT), context);
    editorDiff = new QAction(VcsBaseSubmitEditor::diffIcon(), tr("Diff &Selected Files"), this);
    command = Core::ActionManager::registerAction(editorDiff, Core::Id(Constants::DIFFEDITOR), context);
    command = Core::ActionManager::registerAction(editorUndo, Core::Id(Core::Constants::UNDO), context);
    command = Core::ActionManager::registerAction(editorRedo, Core::Id(Core::Constants::REDO), context);
    if (raiseSubmitEditor())
    const VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    connect(m_client, SIGNAL(parsedStatus(QList<VcsBase::VcsBaseClient::StatusItem>)),
            this, SLOT(showCommitWidget(QList<VcsBase::VcsBaseClient::StatusItem>)));
void MercurialPlugin::showCommitWidget(const QList<VcsBaseClient::StatusItem> &status)
    VcsBaseOutputWindow *outputWindow = VcsBaseOutputWindow::instance();
    disconnect(m_client, SIGNAL(parsedStatus(QList<VcsBase::VcsBaseClient::StatusItem>)),
               this, SLOT(showCommitWidget(QList<VcsBase::VcsBaseClient::StatusItem>)));
    // Start new temp file
    Utils::TempFileSaver saver;
    // Keep the file alive, else it removes self and forgets its name
    saver.setAutoRemove(false);
    if (!saver.finalize()) {
        VcsBase::VcsBaseOutputWindow::instance()->appendError(saver.errorString());
    Core::IEditor *editor = Core::EditorManager::openEditor(saver.fileName(),
                                                            Constants::COMMIT_ID);
    QTC_ASSERT(qobject_cast<CommitEditor *>(editor), return);
    setSubmitEditor(commitEditor);

    commitEditor->registerActions(editorUndo, editorRedo, editorCommit, editorDiff);
    connect(commitEditor, SIGNAL(diffSelectedFiles(QStringList)),
            this, SLOT(diffFromEditorSelected(QStringList)));
    commitEditor->setCheckScriptWorkingDirectory(m_submitRepository);
    commitEditor->document()->setDisplayName(msg);
    // Close the submit editor
    m_submitActionTriggered = true;
    Core::EditorManager::closeEditor();
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
        m_client->commit(m_submitRepository, files, editorFile->filePath(),
    //    Core::Command *command = Core::ActionManager::registerAction(action, Constants::BRANCH, context);
void MercurialPlugin::updateActions(VcsBasePlugin::ActionState as)
#ifdef WITH_TESTS
#include <QTest>

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
    MercurialEditor editor(editorParameters + 2, 0);
    editor.testDiffFileResolving();
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
    MercurialEditor editor(editorParameters, 0);
    editor.testLogResolving(data, "18473:692cbda1eb50", "18472:37100f30590f");
}
#endif
