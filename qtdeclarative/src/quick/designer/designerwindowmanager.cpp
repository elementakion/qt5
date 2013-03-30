/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
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
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "designerwindowmanager_p.h"

#include <QtGui/QOpenGLContext>

#include <QtQuick/QQuickWindow>


QT_BEGIN_NAMESPACE

DesignerWindowManager::DesignerWindowManager()
    : m_sgContext(QSGContext::createDefaultContext())
{
}

void DesignerWindowManager::show(QQuickWindow *window)
{
    makeOpenGLContext(window);
}

void DesignerWindowManager::hide(QQuickWindow *)
{
}

void DesignerWindowManager::windowDestroyed(QQuickWindow *)
{
}

void DesignerWindowManager::makeOpenGLContext(QQuickWindow *window)
{
    if (!m_openGlContext) {
        m_openGlContext.reset(new QOpenGLContext());
        m_openGlContext->setFormat(window->requestedFormat());
        m_openGlContext->create();
        if (!m_openGlContext->makeCurrent(window))
            qWarning("QQuickWindow: makeCurrent() failed...");
        m_sgContext->initialize(m_openGlContext.data());
    } else {
        m_openGlContext->makeCurrent(window);
    }
}

void DesignerWindowManager::exposureChanged(QQuickWindow *)
{
}

QImage DesignerWindowManager::grab(QQuickWindow *)
{
    return QImage();
}

void DesignerWindowManager::resize(QQuickWindow *, const QSize &)
{
}

void DesignerWindowManager::maybeUpdate(QQuickWindow *)
{
}

QSGContext *DesignerWindowManager::sceneGraphContext() const
{
    return m_sgContext.data();
}

void DesignerWindowManager::createOpenGLContext(QQuickWindow *window)
{
    window->create();
    window->update();
}

void DesignerWindowManager::update(QQuickWindow *window)
{
    makeOpenGLContext(window);
}

QT_END_NAMESPACE


