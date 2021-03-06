/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham@gatech.edu>
 */

#ifndef NETANIM_H
#define NETANIM_H

#include <main/common.h>
#include <map>

#include <QTabWidget>

namespace netanim {

class NetAnim : public QObject
{
Q_OBJECT
public:
    NetAnim();
private:
    typedef std::map <int, Mode *> TabIndexModeMap_t;
    QTabWidget * m_tabWidget;
    TabIndexModeMap_t m_TabMode;

private slots:
    void currentTabChangedSlot(int currentIndex);

};
}

#endif // NETANIM_H
