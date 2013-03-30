/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_CachingIterator_H
#define Patternist_CachingIterator_H

#include <QList>
#include <QVector>

#include <private/qdynamiccontext_p.h>
#include <private/qitem_p.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short An QAbstractXmlForwardIterator that gets its item from a cache unless its empty, in
     * which case it continues to populate the cache as well as deliver on its
     * own from a source QAbstractXmlForwardIterator.
     *
     * @author Frans Englich <frans.frans.englich@nokia.com>
     * @ingroup Patternist_iterators
     */
    class CachingIterator : public Item::Iterator
    {
    public:
        /**
         * We always use the same cache cell so why don't we use it directly,
         * instead of passing the slot and ItemSequenceCacheCell::Vector to
         * this class? Because the GenericDynamicContext might decide to resize
         * the vector and that would invalidate the reference.
         *
         * We intentionally pass in a non-const reference here.
         */
        CachingIterator(ItemSequenceCacheCell::Vector &cacheCells,
                        const VariableSlotID slot,
                        const DynamicContext::Ptr &context);

        virtual Item next();
        virtual Item current() const;
        virtual xsInteger position() const;
        virtual Item::Iterator::Ptr copy() const;

    private:
        Item                        m_current;
        xsInteger                   m_position;

        /**
         * This variable cannot be called m_slot, because
         * /usr/include/sys/sysmacros.h on hpuxi-acc defines it.
         */
        const VariableSlotID        m_varSlot;

        /**
         * We don't use the context. We only keep a reference such that it
         * doesn't get deleted, and m_cacheCells starts to dangle.
         */
        const DynamicContext::Ptr   m_context;

        /**
         * We intentionally store a reference here such that we are able to
         * modify the item.
         */
        ItemSequenceCacheCell::Vector &m_cacheCells;

        /**
         * Whether this CachingIterator is delivering items from
         * m_cacheCell.cacheItems or from m_cacheCell.sourceIterator.
         */
        bool m_usingCache;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
