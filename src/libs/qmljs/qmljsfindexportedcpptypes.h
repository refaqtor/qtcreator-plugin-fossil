/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef QMLJS_QMLJSFINDEXPORTEDCPPTYPES_H
#define QMLJS_QMLJSFINDEXPORTEDCPPTYPES_H

#include "qmljs_global.h"
#include <cplusplus/CppDocument.h>
#include <languageutils/fakemetaobject.h>

#include <QCoreApplication>
#include <QHash>

namespace QmlJS {

class QMLJS_EXPORT FindExportedCppTypes
{
    Q_DECLARE_TR_FUNCTIONS(QmlJSTools::FindExportedCppTypes)
public:
    FindExportedCppTypes(const CPlusPlus::Snapshot &snapshot);

    // document must have a valid source and ast for the duration of the call
    void operator()(const CPlusPlus::Document::Ptr &document);

    QList<LanguageUtils::FakeMetaObject::ConstPtr> exportedTypes() const;
    QHash<QString, QString> contextProperties() const;

    static bool maybeExportsTypes(const CPlusPlus::Document::Ptr &document);

private:
    CPlusPlus::Snapshot m_snapshot;
    QList<LanguageUtils::FakeMetaObject::ConstPtr> m_exportedTypes;
    QHash<QString, QString> m_contextProperties;
};

} // namespace QmlJS

#endif // QMLJS_QMLJSFINDEXPORTEDCPPTYPES_H