/***************************************************************************
* Copyright (c) 2013 Abdurrahman AVCI <abdurrahmanavci@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************/

#ifndef SDDM_SCREENMODEL_H
#define SDDM_SCREENMODEL_H

#include <QAbstractListModel>

#ifdef USE_QT5
#include <QHash>
#endif

#include <QRect>

class QScreen;

namespace SDDM {
    class ScreenModelPrivate;

    class ScreenModel : public QAbstractListModel {
        Q_OBJECT
        Q_DISABLE_COPY(ScreenModel)
        Q_PROPERTY(int primary READ primary NOTIFY primaryChanged)
    public:
        enum ScreenRoles {
            NameRole = Qt::UserRole + 1,
            GeometryRole
        };

        ScreenModel(QObject *parent = 0);
        ~ScreenModel();

#ifdef USE_QT5
        QHash<int, QByteArray> roleNames() const override;
#endif
        int primary() const;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    public slots:
        const QRect geometry(int index = -1) const;

    private slots:
#ifdef USE_QT5
        void onScreenAdded(QScreen *scrn);
#endif
        void onScreenChanged();

    signals:
        void primaryChanged();

    private:
        void initScreens(bool first);

        ScreenModelPrivate *d { nullptr };
    };
}

#endif // SDDM_SCREENMODEL_H
