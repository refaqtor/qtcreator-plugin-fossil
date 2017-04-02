** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
#include "diffeditorwidget.h"
#include "diffshoweditor.h"
#include "diffshoweditorfactory.h"
DiffEditorPlugin::DiffEditorPlugin()
}
DiffEditorPlugin::~DiffEditorPlugin()
    Core::ActionContainer *toolsContainer =
        Core::ActionManager::actionContainer(Core::Constants::M_TOOLS);
    Core::Context globalcontext(Core::Constants::C_GLOBAL);

    Core::Command *diffCommand = Core::ActionManager::registerAction(diffAction,
                             "DiffEditor.Diff", globalcontext);
    connect(diffAction, SIGNAL(triggered()), this, SLOT(diff()));
    addAutoReleasedObject(new DiffShowEditorFactory(this));
{
}
    QString fileName1 = QFileDialog::getOpenFileName(0,
    QString fileName2 = QFileDialog::getOpenFileName(0,
    const Core::Id editorId = Constants::DIFF_EDITOR_ID;
    //: Editor title
    DiffEditor *editor = qobject_cast<DiffEditor *>
            (Core::EditorManager::openEditorWithContents(editorId, &title));
    if (!editor)
        return;
    Core::EditorManager::activateEditor(editor);
    DiffEditorWidget *editorWidget = editor->editorWidget();
    const QString text1 = getFileContents(fileName1, editorWidget->codec());
    const QString text2 = getFileContents(fileName2, editorWidget->codec());
    DiffEditorWidget::DiffFilesContents dfc;
    dfc.leftFileInfo = fileName1;
    dfc.leftText = text1;
    dfc.rightFileInfo = fileName2;
    dfc.rightText = text2;
    QList<DiffEditorWidget::DiffFilesContents> list;
    list.append(dfc);
    editor->setDiff(list);
QString DiffEditorPlugin::getFileContents(const QString &fileName, QTextCodec *codec) const
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        return codec->toUnicode(file.readAll());
    return QString();
} // namespace Internal
} // namespace DiffEditor
#ifdef WITH_TESTS
void DiffEditor::Internal::DiffEditorPlugin::testAssemblyRows()
    DiffEditorWidget widget;
    widget.testAssemblyRows();
Q_EXPORT_PLUGIN(DiffEditor::Internal::DiffEditorPlugin)