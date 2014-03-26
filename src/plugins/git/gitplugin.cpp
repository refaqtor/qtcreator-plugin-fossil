/****************************************************************************
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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
#include "gitorious/gitoriousclonewizard.h"
#include "logchangedialog.h"
#include "mergetool.h"
#include "gitutils.h"

#include "gerrit/gerritplugin.h"
#include <coreplugin/documentmanager.h>
#include <coreplugin/infobar.h>
#include <coreplugin/mimedatabase.h>
#include <coreplugin/vcsmanager.h>
#include <vcsbase/submitfilemodel.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QtPlugin>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QScopedPointer>
static const unsigned minimumRequiredVersion = 0x010702;
static const char RC_GIT_MIME_XML[] = ":/git/Git.mimetypes.xml";

static const VcsBase::VcsBaseEditorParameters editorParameters[] = {
    VcsBase::OtherContent,
    "text/vnd.qtcreator.git.commandlog"},
{   VcsBase::LogOutput,
    "text/vnd.qtcreator.git.log"},
{   VcsBase::AnnotateOutput,
    "text/vnd.qtcreator.git.annotation"},
{   VcsBase::DiffOutput,
    "text/x-patch"},
{   VcsBase::OtherContent,
    Git::Constants::GIT_COMMIT_TEXT_EDITOR_ID,
    Git::Constants::GIT_COMMIT_TEXT_EDITOR_DISPLAY_NAME,
    Git::Constants::C_GIT_COMMIT_TEXT_EDITOR,
    "text/vnd.qtcreator.git.commit"},
{   VcsBase::OtherContent,
    Git::Constants::GIT_REBASE_EDITOR_ID,
    Git::Constants::GIT_REBASE_EDITOR_DISPLAY_NAME,
    Git::Constants::C_GIT_REBASE_EDITOR,
    "text/vnd.qtcreator.git.rebase"},
static const VcsBase::VcsBaseSubmitEditorParameters submitParameters = {
    Git::Constants::C_GITSUBMITEDITOR,
    VcsBase::VcsBaseSubmitEditorParameters::DiffRows
        GitPlugin::createParameterAction(Core::ActionContainer *ac,
                                         const Core::Id &id, const Core::Context &context,
    Core::Command *command = Core::ActionManager::registerAction(action, id, context);
        GitPlugin::createFileAction(Core::ActionContainer *ac,
                                    const Core::Id &id, const Core::Context &context, bool addToLocator,
    const ParameterActionCommandPair rc = createParameterAction(ac, defaultText, parameterText, id, context, addToLocator);
        GitPlugin::createProjectAction(Core::ActionContainer *ac,
                                       const Core::Id &id, const Core::Context &context, bool addToLocator,
    const ParameterActionCommandPair rc = createParameterAction(ac, defaultText, parameterText, id, context, addToLocator);
        GitPlugin::createRepositoryAction(Core::ActionContainer *ac,
                                          const QString &text, const Core::Id &id,
    Core::Command *command = Core::ActionManager::registerAction(action, id, context);
    if (ac)
        ac->addAction(command);
        GitPlugin::createRepositoryAction(Core::ActionContainer *ac,
                                          const QString &text, const Core::Id &id,
    const ActionCommandPair rc = createRepositoryAction(ac, text, id, context, addToLocator);
    rc.first->setData(id.uniqueIdentifier());
        GitPlugin::createRepositoryAction(Core::ActionContainer *ac,
                                          const QString &text, const Core::Id &id,
    const ActionCommandPair rc = createRepositoryAction(ac, text, id, context, addToLocator);
    m_settings.readSettings(Core::ICore::settings());
    typedef VcsBase::VcsEditorFactory<GitEditor> GitEditorFactory;
    typedef VcsBase::VcsSubmitEditorFactory<GitSubmitEditor> GitSubmitEditorFactory;
    const int editorCount = sizeof(editorParameters)/sizeof(VcsBase::VcsBaseEditorParameters);
    m_commandLocator = new Locator::CommandLocator("Git", prefix, prefix);
        Core::ActionManager::actionContainer(Core::Constants::M_TOOLS);
    Core::ActionContainer *gitContainer = Core::ActionManager::createMenu("Git");
    /*  "Current File" menu */
    Core::ActionContainer *currentFileMenu = Core::ActionManager::createMenu("Git.CurrentFileMenu");
    currentFileMenu->menu()->setTitle(tr("Current &File"));
    gitContainer->addMenu(currentFileMenu);
    ParameterActionCommandPair parameterActionCommand
            = createFileAction(currentFileMenu,
                               "Git.Diff", globalcontext, true,
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+D") : tr("Alt+G,Alt+D")));
            = createFileAction(currentFileMenu,
                               "Git.Log", globalcontext, true, SLOT(logFile()));
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+L") : tr("Alt+G,Alt+L")));
    parameterActionCommand
                = createFileAction(currentFileMenu,
                                   tr("Blame Current File"), tr("Blame for \"%1\""),
                                   "Git.Blame",
                                   globalcontext, true, SLOT(blameFile()));
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+B") : tr("Alt+G,Alt+B")));
    currentFileMenu->addSeparator(globalcontext);
            = createFileAction(currentFileMenu,
                               "Git.Stage", globalcontext, true, SLOT(stageFile()));
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+A") : tr("Alt+G,Alt+A")));
            = createFileAction(currentFileMenu,
                               "Git.Unstage", globalcontext, true, SLOT(unstageFile()));
            = createFileAction(currentFileMenu,
                               "Git.UndoUnstaged", globalcontext,
            = createFileAction(currentFileMenu,
                               "Git.Undo", globalcontext,
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+U") : tr("Alt+G,Alt+U")));
    /* \"Current File" menu */

    /*  "Current Project" menu */
    Core::ActionContainer *currentProjectMenu = Core::ActionManager::createMenu("Git.CurrentProjectMenu");
    currentProjectMenu->menu()->setTitle(tr("Current &Project"));
    gitContainer->addMenu(currentProjectMenu);
            = createProjectAction(currentProjectMenu,
                                  "Git.DiffProject", globalcontext, true,
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+Shift+D") : tr("Alt+G,Alt+Shift+D")));
            = createProjectAction(currentProjectMenu,
                                  "Git.LogProject", globalcontext, true,
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+K") : tr("Alt+G,Alt+K")));
                = createProjectAction(currentProjectMenu,
                                      "Git.CleanProject", globalcontext,
    /* \"Current Project" menu */
    /*  "Local Repository" menu */
    Core::ActionContainer *localRepositoryMenu = Core::ActionManager::createMenu("Git.LocalRepositoryMenu");
    localRepositoryMenu->menu()->setTitle(tr("&Local Repository"));
    gitContainer->addMenu(localRepositoryMenu);
    createRepositoryAction(localRepositoryMenu,
                           tr("Diff"), "Git.DiffRepository",
                           globalcontext, true, SLOT(diffRepository()));
    createRepositoryAction(localRepositoryMenu,
                           tr("Log"), "Git.LogRepository",
                           globalcontext, true,
                           SLOT(logRepository()));
    createRepositoryAction(localRepositoryMenu,
                           tr("Reflog"), "Git.ReflogRepository",
                           globalcontext, true,
                           SLOT(reflogRepository()));
    createRepositoryAction(localRepositoryMenu,
                           tr("Clean..."), "Git.CleanRepository",
    createRepositoryAction(localRepositoryMenu,
                           tr("Status"), "Git.StatusRepository",
                           globalcontext, true, &GitClient::status);
    localRepositoryMenu->addSeparator(globalcontext);
    ActionCommandPair actionCommand = createRepositoryAction(localRepositoryMenu,
                                                             tr("Commit..."), "Git.Commit",
                                                             globalcontext, true, SLOT(startCommit()));
    actionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+C") : tr("Alt+G,Alt+C")));
    createRepositoryAction(localRepositoryMenu,
                           tr("Amend Last Commit..."), "Git.AmendCommit",
                           globalcontext, true, SLOT(startAmendCommit()));
    m_fixupCommitAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Fixup Previous Commit..."), "Git.FixupCommit",
                                   globalcontext, true, SLOT(startFixupCommit())).first;
    // --------------
    localRepositoryMenu->addSeparator(globalcontext);

    createRepositoryAction(localRepositoryMenu,
                           tr("Reset..."), "Git.Reset",
                           globalcontext, true, SLOT(resetRepository()));

    m_interactiveRebaseAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Interactive Rebase..."), "Git.InteractiveRebase",
                                   globalcontext, true, SLOT(startRebase())).first;

    m_submoduleUpdateAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Update Submodules"), "Git.SubmoduleUpdate",
                                   globalcontext, true, SLOT(updateSubmodules())).first;
    m_abortMergeAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Abort Merge"), "Git.MergeAbort",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_abortRebaseAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Abort Rebase"), "Git.RebaseAbort",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_abortCherryPickAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Abort Cherry Pick"), "Git.CherryPickAbort",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_abortRevertAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Abort Revert"), "Git.RevertAbort",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_continueRebaseAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Continue Rebase"), "Git.RebaseContinue",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_continueCherryPickAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Continue Cherry Pick"), "Git.CherryPickContinue",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;

    m_continueRevertAction =
            createRepositoryAction(localRepositoryMenu,
                                   tr("Continue Revert"), "Git.RevertContinue",
                                   globalcontext, true, SLOT(continueOrAbortCommand())).first;
    // --------------
    localRepositoryMenu->addSeparator(globalcontext);
    createRepositoryAction(localRepositoryMenu,
                           tr("Branches..."), "Git.BranchList",
                           globalcontext, true, SLOT(branchList()));
    localRepositoryMenu->addSeparator(globalcontext);
    // "Patch" menu
    Core::ActionContainer *patchMenu = Core::ActionManager::createMenu("Git.PatchMenu");
    patchMenu->menu()->setTitle(tr("&Patch"));
    localRepositoryMenu->addMenu(patchMenu);
            createParameterAction(patchMenu,
                                  "Git.ApplyCurrentFilePatch",
    createRepositoryAction(patchMenu,
                           tr("Apply from File..."), "Git.ApplyPatch",
    // "Stash" menu
    Core::ActionContainer *stashMenu = Core::ActionManager::createMenu("Git.StashMenu");
    stashMenu->menu()->setTitle(tr("&Stash"));
    localRepositoryMenu->addMenu(stashMenu);
    createRepositoryAction(stashMenu,
                           tr("Stashes..."), "Git.StashList",
    stashMenu->addSeparator(globalcontext);
    actionCommand = createRepositoryAction(stashMenu,
                                           tr("Stash"), "Git.Stash",
                                           globalcontext, true, SLOT(stash()));
    actionCommand = createRepositoryAction(stashMenu,
                                           tr("Take Snapshot..."), "Git.StashSnapshot",
    stashMenu->addSeparator(globalcontext);
    actionCommand = createRepositoryAction(stashMenu,
                                           tr("Stash Pop"), "Git.StashPop",
    /* \"Local Repository" menu */
    // --------------
    /*  "Remote Repository" menu */
    Core::ActionContainer *remoteRepositoryMenu = Core::ActionManager::createMenu("Git.RemoteRepositoryMenu");
    remoteRepositoryMenu->menu()->setTitle(tr("&Remote Repository"));
    gitContainer->addMenu(remoteRepositoryMenu);
    createRepositoryAction(remoteRepositoryMenu,
                           tr("Fetch"), "Git.Fetch",
    createRepositoryAction(remoteRepositoryMenu,
                           tr("Pull"), "Git.Pull",
    actionCommand = createRepositoryAction(remoteRepositoryMenu,
                                           tr("Push"), "Git.Push",
    // --------------
    remoteRepositoryMenu->addSeparator(globalcontext);
    // "Subversion" menu
    Core::ActionContainer *subversionMenu = Core::ActionManager::createMenu("Git.Subversion");
    subversionMenu->menu()->setTitle(tr("&Subversion"));
    remoteRepositoryMenu->addMenu(subversionMenu);
    createRepositoryAction(subversionMenu,
                           tr("Log"), "Git.Subversion.Log",
                           globalcontext, false, &GitClient::subversionLog);

    createRepositoryAction(subversionMenu,
                           tr("Fetch"), "Git.Subversion.Fetch",
                           globalcontext, false, &GitClient::synchronousSubversionFetch);

    // --------------
    remoteRepositoryMenu->addSeparator(globalcontext);

    createRepositoryAction(remoteRepositoryMenu,
                           tr("Manage Remotes..."), "Git.RemoteList",
                           globalcontext, false, SLOT(remoteList()));

    /* \"Remote Repository" menu */

    // --------------

    /*  Actions only in locator */
    createRepositoryAction(0, tr("Show..."), "Git.Show",
                           globalcontext, true, SLOT(startChangeRelatedAction()));

    createRepositoryAction(0, tr("Revert..."), "Git.Revert",
                           globalcontext, true, SLOT(startChangeRelatedAction()));

    createRepositoryAction(0, tr("Cherry Pick..."), "Git.CherryPick",
                           globalcontext, true, SLOT(startChangeRelatedAction()));

    createRepositoryAction(0, tr("Checkout..."), "Git.Checkout",
                           globalcontext, true, SLOT(startChangeRelatedAction()));

    createRepositoryAction(0, tr("Rebase..."), "Git.Rebase",
                           globalcontext, true, SLOT(branchList()));

    createRepositoryAction(0, tr("Merge..."), "Git.Merge",
                           globalcontext, true, SLOT(branchList()));

    /*  \Actions only in locator */

    // --------------

    /*  "Git Tools" menu */
    Core::ActionContainer *gitToolsMenu = Core::ActionManager::createMenu("Git.GitToolsMenu");
    gitToolsMenu->menu()->setTitle(tr("Git &Tools"));
    gitContainer->addMenu(gitToolsMenu);

    createRepositoryAction(gitToolsMenu,
                           tr("Gitk"), "Git.LaunchGitK",
                           globalcontext, true, &GitClient::launchGitK);

    parameterActionCommand
            = createFileAction(gitToolsMenu,
                               tr("Gitk Current File"), tr("Gitk of \"%1\""),
                               "Git.GitkFile", globalcontext, true, SLOT(gitkForCurrentFile()));

    parameterActionCommand
            = createFileAction(gitToolsMenu,
                               tr("Gitk for folder of Current File"), tr("Gitk for folder of \"%1\""),
                               "Git.GitkFolder", globalcontext, true, SLOT(gitkForCurrentFolder()));

    // --------------
    gitToolsMenu->addSeparator(globalcontext);

    createRepositoryAction(gitToolsMenu, tr("Git Gui"), "Git.GitGui",
                           globalcontext, true, SLOT(gitGui()));

    // --------------
    gitToolsMenu->addSeparator(globalcontext);

    m_repositoryBrowserAction
            = createRepositoryAction(gitToolsMenu,
                                     tr("Repository Browser"), "Git.LaunchRepositoryBrowser",
                                     globalcontext, true, &GitClient::launchRepositoryBrowser).first;

    m_mergeToolAction =
            createRepositoryAction(gitToolsMenu,
                                   tr("Merge Tool"), "Git.MergeTool",
                                   globalcontext, true, SLOT(startMergeTool())).first;

    /* \"Git Tools" menu */

    // --------------
    gitContainer->addSeparator(globalcontext);

    QAction *changesAction = new QAction(tr("Actions on Commits..."), this);
    Core::Command *changesCommand = Core::ActionManager::registerAction(changesAction, "Git.ChangeActions", globalcontext);
    connect(changesAction, SIGNAL(triggered()), this, SLOT(startChangeRelatedAction()));
    gitContainer->addAction(changesCommand);

    QAction *repositoryAction = new QAction(tr("Create Repository..."), this);
    Core::Command *createRepositoryCommand = Core::ActionManager::registerAction(repositoryAction, "Git.CreateRepository", globalcontext);
    connect(repositoryAction, SIGNAL(triggered()), this, SLOT(createRepository()));
    gitContainer->addAction(createRepositoryCommand);
    m_submitCurrentAction = new QAction(VcsBase::VcsBaseSubmitEditor::submitIcon(), tr("Commit"), this);
    Core::Command *command = Core::ActionManager::registerAction(m_submitCurrentAction, Constants::SUBMIT_CURRENT, submitContext);
    m_diffSelectedFilesAction = new QAction(VcsBase::VcsBaseSubmitEditor::diffIcon(), tr("Diff &Selected Files"), this);
    command = Core::ActionManager::registerAction(m_diffSelectedFilesAction, Constants::DIFF_SELECTED, submitContext);
    command = Core::ActionManager::registerAction(m_undoAction, Core::Constants::UNDO, submitContext);
    command = Core::ActionManager::registerAction(m_redoAction, Core::Constants::REDO, submitContext);
    connect(Core::VcsManager::instance(), SIGNAL(repositoryChanged(QString)),
            this, SLOT(updateContinueAndAbortCommands()));
    connect(Core::VcsManager::instance(), SIGNAL(repositoryChanged(QString)),
            this, SLOT(updateBranches(QString)), Qt::QueuedConnection);

    if (!Core::MimeDatabase::addMimeTypes(QLatin1String(RC_GIT_MIME_XML), errorMessage))
        return false;

    /* "Gerrit" */
    m_gerritPlugin = new Gerrit::Internal::GerritPlugin(this);
    const bool ok = m_gerritPlugin->initialize(remoteRepositoryMenu);
    m_gerritPlugin->updateActions(currentState().hasTopLevel());
    m_gerritPlugin->addToLocator(m_commandLocator);

    return ok;
    m_gitClient->diff(m_submitRepository, unstaged, staged);
}

void GitPlugin::submitEditorMerge(const QStringList &unmerged)
{
    m_gitClient->merge(m_submitRepository, unmerged);
}

static bool ensureAllDocumentsSaved()
{
    bool cancelled;
    Core::DocumentManager::saveModifiedDocuments(Core::DocumentManager::modifiedDocuments(),
                                                 &cancelled);
    return !cancelled;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    m_gitClient->diff(state.currentFileTopLevel(), state.relativeCurrentFile());
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasProject(), return);
    const QString relativeProject = state.relativeCurrentProject();
    m_gitClient->diff(state.currentProjectTopLevel(),
                      relativeProject.isEmpty() ? QStringList() : QStringList(relativeProject));
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->diff(state.topLevel(), QStringList());
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    m_gitClient->log(state.currentFileTopLevel(), state.relativeCurrentFile(), true);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    const int lineNumber = VcsBase::VcsBaseEditorWidget::lineNumberOfCurrentEditor(state.currentFile());
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasProject(), return);
void GitPlugin::logRepository()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->log(state.topLevel());
}

void GitPlugin::reflogRepository()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->reflog(state.topLevel());
}

    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    if (!ensureAllDocumentsSaved())
        return;
void GitPlugin::resetRepository()
{
    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    QString topLevel = state.topLevel();

    LogChangeDialog dialog(true, Core::ICore::mainWindow());
    dialog.setWindowTitle(tr("Undo Changes to %1").arg(QDir::toNativeSeparators(topLevel)));
    if (dialog.runDialog(topLevel))
        m_gitClient->reset(topLevel, dialog.resetFlag(), dialog.commit());
}

void GitPlugin::startRebase()
    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const QString topLevel = state.topLevel();
    if (topLevel.isEmpty() || !m_gitClient->canRebase(topLevel))
        return;
    if (!m_gitClient->beginStashScope(topLevel, QLatin1String("Rebase-i")))
        return;
    LogChangeDialog dialog(false, Core::ICore::mainWindow());
    dialog.setWindowTitle(tr("Interactive Rebase"));
    if (dialog.runDialog(topLevel, QString(), false))
        m_gitClient->interactiveRebase(topLevel, dialog.commit(), false);
    else
        m_gitClient->endStashScope(topLevel);
}

void GitPlugin::startChangeRelatedAction()
{
    const VcsBase::VcsBasePluginState state = currentState();
    if (!state.hasTopLevel())
        return;

    QAction *action = qobject_cast<QAction *>(sender());
    Core::Id id = action ? Core::Id::fromUniqueIdentifier(action->data().toInt()) : Core::Id();
    ChangeSelectionDialog dialog(state.topLevel(), id, Core::ICore::mainWindow());

    int result = dialog.exec();

    if (result == QDialog::Rejected)
        return;

    const QString workingDirectory = dialog.workingDirectory();
    const QString change = dialog.change();

    if (workingDirectory.isEmpty() || change.isEmpty())
        return;

    if (dialog.command() == Show) {
        m_gitClient->show(workingDirectory, change);
        return;
    }

    if (!ensureAllDocumentsSaved())
        return;
    bool (GitClient::*commandFunction)(const QString&, const QString&);
    switch (dialog.command()) {
    case CherryPick:
        commandFunction = &GitClient::synchronousCherryPick;
        break;
    case Revert:
        commandFunction = &GitClient::synchronousRevert;
        break;
    case Checkout:
        if (!m_gitClient->beginStashScope(workingDirectory, QLatin1String("Checkout")))
            return;
        commandFunction = &GitClient::synchronousCheckout;
        break;
    default:
    }

    (m_gitClient->*commandFunction)(workingDirectory, change);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
void GitPlugin::gitkForCurrentFile()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    m_gitClient->launchGitK(state.currentFileTopLevel(), state.relativeCurrentFile());
}

void GitPlugin::gitkForCurrentFolder()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);

    /*
     *  entire lower part of the code can be easily replaced with one line:
     *
     *  m_gitClient->launchGitK(dir.currentFileDirectory(), QLatin1String("."));
     *
     *  However, there is a bug in gitk in version 1.7.9.5, and if you run above
     *  command, there will be no documents listed in lower right section.
     *
     *  This is why I use lower combination in order to avoid this problems in gitk.
     *
     *  Git version 1.7.10.4 does not have this issue, and it can easily use
     *  one line command mentioned above.
     *
     */
    QDir dir(state.currentFileDirectory());
    if (QFileInfo(dir,QLatin1String(".git")).exists() || dir.cd(QLatin1String(".git"))) {
        m_gitClient->launchGitK(state.currentFileDirectory());
    } else {
        QString folderName = dir.absolutePath();
        dir.cdUp();
        folderName = folderName.remove(0, dir.absolutePath().length() + 1);
        m_gitClient->launchGitK(dir.absolutePath(), folderName);
    }
}

void GitPlugin::gitGui()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->launchGitGui(state.topLevel());
}

    startCommit(AmendCommit);
void GitPlugin::startFixupCommit()
    startCommit(FixupCommit);
void GitPlugin::startCommit()
    startCommit(SimpleCommit);
}
void GitPlugin::startCommit(CommitType commitType)
{
    if (raiseSubmitEditor())
        VcsBase::VcsBaseOutputWindow::instance()->appendWarning(tr("Another submit is currently being executed."));
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    CommitData data(commitType);
    if (!m_gitClient->getCommitData(state.topLevel(), &commitTemplate, data, &errorMessage)) {
        VcsBase::VcsBaseOutputWindow::instance()->appendError(errorMessage);
        VcsBase::VcsBaseOutputWindow::instance()->appendError(saver.errorString());
    openSubmitEditor(m_commitMessageFileName, data);
void GitPlugin::updateVersionWarning()
    unsigned version = m_gitClient->gitVersion();
    if (!version || version >= minimumRequiredVersion)
        return;
    Core::IDocument *curDocument = Core::EditorManager::currentDocument();
    if (!curDocument)
        return;
    Core::InfoBar *infoBar = curDocument->infoBar();
    Core::Id gitVersionWarning("GitVersionWarning");
    if (!infoBar->canInfoBeAdded(gitVersionWarning))
        return;
    infoBar->addInfo(Core::InfoBarEntry(gitVersionWarning,
                        tr("Unsupported version of Git found. Git %1 or later required.")
                        .arg(versionString(minimumRequiredVersion)),
                        Core::InfoBarEntry::GlobalSuppressionEnabled));
}

Core::IEditor *GitPlugin::openSubmitEditor(const QString &fileName, const CommitData &cd)
{
    Core::IEditor *editor = Core::EditorManager::openEditor(fileName, Constants::GITSUBMITEDITOR_ID);
    setSubmitEditor(submitEditor);
    QString title;
    switch (cd.commitType) {
    case AmendCommit:
        title = tr("Amend %1").arg(cd.amendSHA1);
        break;
    case FixupCommit:
        title = tr("Git Fixup Commit");
        break;
    default:
        title = tr("Git Commit");
    }
    submitEditor->document()->setDisplayName(title);
    connect(submitEditor, SIGNAL(merge(QStringList)), this, SLOT(submitEditorMerge(QStringList)));
    connect(submitEditor, SIGNAL(show(QString,QString)), m_gitClient, SLOT(show(QString,QString)));
    Core::EditorManager::closeEditor();
bool GitPlugin::submitEditorAboutToClose()
    GitSubmitEditor *editor = qobject_cast<GitSubmitEditor *>(submitEditor());
    QTC_ASSERT(editor, return true);
    Core::IDocument *editorDocument = editor->document();
    QTC_ASSERT(editorDocument, return true);
    const QFileInfo editorFile(editorDocument->filePath());
    VcsBase::VcsBaseSubmitEditor::PromptSubmitResult answer;
    if (editor->forceClose()) {
        answer = VcsBase::VcsBaseSubmitEditor::SubmitDiscarded;
    } else {
        bool promptData = false;
        answer = editor->promptSubmit(tr("Closing Git Editor"),
                     tr("Do you want to commit the change?"),
                     tr("Git will not accept this commit. Do you want to continue to edit it?"),
                     &promptData, !m_submitActionTriggered, false);
    }
    case VcsBase::VcsBaseSubmitEditor::SubmitCanceled:
    case VcsBase::VcsBaseSubmitEditor::SubmitDiscarded:


    VcsBase::SubmitFileModel *model = qobject_cast<VcsBase::SubmitFileModel *>(editor->fileModel());
    CommitType commitType = editor->commitType();
    QString amendSHA1 = editor->amendSHA1();
    if (model->hasCheckedFiles() || !amendSHA1.isEmpty()) {
        if (!Core::DocumentManager::saveDocument(editorDocument))
        closeEditor = m_gitClient->addAndCommit(m_submitRepository, editor->panelData(),
                                                commitType, amendSHA1,
                                                m_commitMessageFileName, model);
    if (!closeEditor)
        return false;
    cleanCommitMessageFile();
    if (commitType == FixupCommit) {
        if (!m_gitClient->beginStashScope(m_submitRepository, QLatin1String("Rebase-fixup"), NoPrompt))
            return false;
        m_gitClient->interactiveRebase(m_submitRepository, amendSHA1, true);
    } else {
        m_gitClient->continueCommandIfNeeded(m_submitRepository);
        if (editor->panelData().pushAction == NormalPush)
            m_gitClient->push(m_submitRepository);
        else if (editor->panelData().pushAction == PushToGerrit)
            connect(editor, SIGNAL(destroyed()), this, SLOT(delayedPushToGerrit()));
    }

    return true;
    m_gitClient->fetch(currentState().topLevel(), QString());
    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    QString topLevel = state.topLevel();
    bool rebase = m_settings.boolValue(GitSettings::pullRebaseKey);

    if (!rebase) {
        QString currentBranch = m_gitClient->synchronousCurrentLocalBranch(topLevel);
        if (!currentBranch.isEmpty()) {
            currentBranch.prepend(QLatin1String("branch."));
            currentBranch.append(QLatin1String(".rebase"));
            rebase = (m_gitClient->readConfigValue(topLevel, currentBranch) == QLatin1String("true"));
        }

    if (!m_gitClient->beginStashScope(topLevel, QLatin1String("Pull"), rebase ? Default : AllowUnstashed))
        return;
    m_gitClient->synchronousPull(topLevel, rebase);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->push(state.topLevel());
}

void GitPlugin::startMergeTool()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->merge(state.topLevel());
}

void GitPlugin::continueOrAbortCommand()
{
    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    QObject *action = QObject::sender();

    if (action == m_abortMergeAction)
        m_gitClient->synchronousMerge(state.topLevel(), QLatin1String("--abort"));
    else if (action == m_abortRebaseAction)
        m_gitClient->rebase(state.topLevel(), QLatin1String("--abort"));
    else if (action == m_abortCherryPickAction)
        m_gitClient->synchronousCherryPick(state.topLevel(), QLatin1String("--abort"));
    else if (action == m_abortRevertAction)
        m_gitClient->synchronousRevert(state.topLevel(), QLatin1String("--abort"));
    else if (action == m_continueRebaseAction)
        m_gitClient->rebase(state.topLevel(), QLatin1String("--continue"));
    else if (action == m_continueCherryPickAction)
        m_gitClient->synchronousCherryPick(state.topLevel(), QLatin1String("--continue"));
    else if (action == m_continueRevertAction)
        m_gitClient->synchronousRevert(state.topLevel(), QLatin1String("--continue"));

    updateContinueAndAbortCommands();
            if (v.canConvert<GitClientMemberFunc>())
                return qvariant_cast<GitClientMemberFunc>(v);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasProject(), return);
    const VcsBase::VcsBasePluginState state = currentState();
    QStringList ignoredFiles;
    const bool gotFiles = m_gitClient->synchronousCleanList(directory, &files, &ignoredFiles, &errorMessage);
    QWidget *parent = Core::ICore::mainWindow();
        QMessageBox::warning(parent, tr("Unable to retrieve file list"), errorMessage);
    if (files.isEmpty() && ignoredFiles.isEmpty()) {
    VcsBase::CleanDialog dialog(parent);
    dialog.setFileList(directory, files, ignoredFiles);
void GitPlugin::updateSubmodules()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->updateSubmodulesIfNeeded(state.topLevel(), false);
}

    Core::IDocument *document = Core::EditorManager::documentModel()->documentForFilePath(fileName);
    if (!document || !document->isModified())
    Core::DocumentManager::saveModifiedDocuments(QList<Core::IDocument *>() << document, &canceled);
    const VcsBase::VcsBasePluginState state = currentState();
    const VcsBase::VcsBasePluginState state = currentState();
    if (!m_gitClient->beginStashScope(workingDirectory, QLatin1String("Apply-Patch"), AllowUnstashed))
        file =  QFileDialog::getOpenFileName(Core::ICore::mainWindow(),
        if (file.isEmpty()) {
            m_gitClient->endStashScope(workingDirectory);
        }
    VcsBase::VcsBaseOutputWindow *outwin = VcsBase::VcsBaseOutputWindow::instance();
        if (errorMessage.isEmpty())
            outwin->appendMessage(tr("Patch %1 successfully applied to %2").arg(file, workingDirectory));
        else
            outwin->appendError(errorMessage);
    m_gitClient->endStashScope(workingDirectory);
    if (!ensureAllDocumentsSaved())
        return;
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);

    QString topLevel = state.topLevel();
    if (!m_gitClient->beginStashScope(topLevel, QString(), NoPrompt))
        return;
    if (m_gitClient->stashInfo(topLevel).result() == GitClient::StashInfo::Stashed && m_stashDialog)
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    const QString id = m_gitClient->synchronousStash(state.topLevel(), QString(),
                GitClient::StashImmediateRestore | GitClient::StashPromptDescription);
// Create a non-modal dialog with refresh function or raise if it exists
        dialog = new NonModalDialog(Core::ICore::mainWindow());
    showNonModalDialog(currentState().topLevel(), m_branchDialog);
void GitPlugin::updateActions(VcsBase::VcsBasePlugin::ActionState as)
    if (repositoryEnabled)
        updateVersionWarning();
    m_submoduleUpdateAction->setVisible(repositoryEnabled
            && !m_gitClient->submoduleList(currentState().topLevel()).isEmpty());

    updateContinueAndAbortCommands();
    updateRepositoryBrowserAction();

    m_gerritPlugin->updateActions(repositoryEnabled);
void GitPlugin::updateContinueAndAbortCommands()
    if (currentState().hasTopLevel()) {
        GitClient::CommandInProgress gitCommandInProgress =
                m_gitClient->checkCommandInProgress(currentState().topLevel());

        m_mergeToolAction->setVisible(gitCommandInProgress != GitClient::NoCommand);
        m_abortMergeAction->setVisible(gitCommandInProgress == GitClient::Merge);
        m_abortCherryPickAction->setVisible(gitCommandInProgress == GitClient::CherryPick);
        m_abortRevertAction->setVisible(gitCommandInProgress == GitClient::Revert);
        m_abortRebaseAction->setVisible(gitCommandInProgress == GitClient::Rebase
                                        || gitCommandInProgress == GitClient::RebaseMerge);
        m_continueCherryPickAction->setVisible(gitCommandInProgress == GitClient::CherryPick);
        m_continueRevertAction->setVisible(gitCommandInProgress == GitClient::Revert);
        m_continueRebaseAction->setVisible(gitCommandInProgress == GitClient::Rebase
                                           || gitCommandInProgress == GitClient::RebaseMerge);
        m_fixupCommitAction->setEnabled(gitCommandInProgress == GitClient::NoCommand);
        m_interactiveRebaseAction->setEnabled(gitCommandInProgress == GitClient::NoCommand);
    } else {
        m_mergeToolAction->setVisible(false);
        m_abortMergeAction->setVisible(false);
        m_abortCherryPickAction->setVisible(false);
        m_abortRevertAction->setVisible(false);
        m_abortRebaseAction->setVisible(false);
        m_continueCherryPickAction->setVisible(false);
        m_continueRevertAction->setVisible(false);
        m_continueRebaseAction->setVisible(false);
    }
}
void GitPlugin::delayedPushToGerrit()
{
    m_gerritPlugin->push(m_submitRepository);
}
void GitPlugin::updateBranches(const QString &repository)
{
    if (m_branchDialog && m_branchDialog->isVisible())
        m_branchDialog->refreshIfSame(repository);
}
void GitPlugin::updateRepositoryBrowserAction()
{
    const bool repositoryEnabled = currentState().hasTopLevel();
    const bool hasRepositoryBrowserCmd = !m_settings.stringValue(GitSettings::repositoryBrowserCmd).isEmpty();
    m_repositoryBrowserAction->setEnabled(repositoryEnabled && hasRepositoryBrowserCmd);
    updateRepositoryBrowserAction();
#ifdef WITH_TESTS

#include <QTest>

Q_DECLARE_METATYPE(FileStates)

void GitPlugin::testStatusParsing_data()
{
    QTest::addColumn<FileStates>("first");
    QTest::addColumn<FileStates>("second");

    QTest::newRow(" M") << FileStates(ModifiedFile) << FileStates(UnknownFileState);
    QTest::newRow(" D") << FileStates(DeletedFile) << FileStates(UnknownFileState);
    QTest::newRow("M ") << (ModifiedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("MM") << (ModifiedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("MD") << (ModifiedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("A ") << (AddedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("AM") << (AddedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("AD") << (AddedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("D ") << (DeletedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("DM") << (DeletedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("R ") << (RenamedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("RM") << (RenamedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("RD") << (RenamedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("C ") << (CopiedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("CM") << (CopiedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("CD") << (CopiedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("??") << FileStates(UntrackedFile) << FileStates(UnknownFileState);

    // Merges
    QTest::newRow("DD") << (DeletedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("AA") << (AddedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("UU") << (ModifiedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("AU") << (AddedFile | UnmergedFile | UnmergedUs) << FileStates(UnknownFileState);
    QTest::newRow("UD") << (DeletedFile | UnmergedFile | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("UA") << (AddedFile | UnmergedFile | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("DU") << (DeletedFile | UnmergedFile | UnmergedUs) << FileStates(UnknownFileState);
}

void GitPlugin::testStatusParsing()
{
    CommitData data;
    QFETCH(FileStates, first);
    QFETCH(FileStates, second);
    QString output = QLatin1String("## master...origin/master [ahead 1]\n");
    output += QString::fromLatin1(QTest::currentDataTag()) + QLatin1String(" main.cpp\n");
    data.parseFilesFromStatus(output);
    QCOMPARE(data.files.at(0).first, first);
    if (second == UnknownFileState)
        QCOMPARE(data.files.size(), 1);
    else
        QCOMPARE(data.files.at(1).first, second);
}

void GitPlugin::testDiffFileResolving_data()
{
    QTest::addColumn<QByteArray>("header");
    QTest::addColumn<QByteArray>("fileName");

    QTest::newRow("New") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "new file mode 100644\n"
            "index 0000000..40997ff\n"
            "--- /dev/null\n"
            "+++ b/src/plugins/git/giteditor.cpp\n"
            "@@ -0,0 +1,281 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
    QTest::newRow("Deleted") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "deleted file mode 100644\n"
            "index 40997ff..0000000\n"
            "--- a/src/plugins/git/giteditor.cpp\n"
            "+++ /dev/null\n"
            "@@ -1,281 +0,0 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
    QTest::newRow("Normal") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "index 69e0b52..8fc974d 100644\n"
            "--- a/src/plugins/git/giteditor.cpp\n"
            "+++ b/src/plugins/git/giteditor.cpp\n"
            "@@ -49,6 +49,8 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
}

void GitPlugin::testDiffFileResolving()
{
    GitEditor editor(editorParameters + 3, 0);
    editor.testDiffFileResolving();
}

void GitPlugin::testLogResolving()
{
    QByteArray data(
                "commit 50a6b54c03219ad74b9f3f839e0321be18daeaf6 (HEAD, origin/master)\n"
                "Merge: 3587b51 bc93ceb\n"
                "Author: Junio C Hamano <gitster@pobox.com>\n"
                "Date:   Fri Jan 25 12:53:31 2013 -0800\n"
                "\n"
                "   Merge branch 'for-junio' of git://bogomips.org/git-svn\n"
                "    \n"
                "    * 'for-junio' of git://bogomips.org/git-svn:\n"
                "      git-svn: Simplify calculation of GIT_DIR\n"
                "      git-svn: cleanup sprintf usage for uppercasing hex\n"
                "\n"
                "commit 3587b513bafd7a83d8c816ac1deed72b5e3a27e9\n"
                "Author: Junio C Hamano <gitster@pobox.com>\n"
                "Date:   Fri Jan 25 12:52:55 2013 -0800\n"
                "\n"
                "    Update draft release notes to 1.8.2\n"
                "    \n"
                "    Signed-off-by: Junio C Hamano <gitster@pobox.com>\n"
                );
    GitEditor editor(editorParameters + 1, 0);
    editor.testLogResolving(data,
                            "50a6b54c - Merge branch 'for-junio' of git://bogomips.org/git-svn",
                            "3587b513 - Update draft release notes to 1.8.2");
}
#endif
