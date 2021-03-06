/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003  
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/* Desc: Gazebo configuration on this computer 
 * Author: Jordi Polo
 * Date: 3 May 2008
 * SVN: $Id: GazeboConfig.hh 7773 2009-06-03 13:51:30Z natepak $
 *
 * Modified by: Eurico Pedrosa <efp@ua.p>
 * Date: 10 Fev 2010
 *
 * Modification Notes
 *
 *  The modifications presented by me, have the purpose of
 *  removing the 'rendering' and 'gui' modules from the code base.
 *  The reasons behind this decision are simple, allow gazebo to run
 *  on computers with less gpu capabilities and lessen the the coupling
 *  between simulation and visualization.
 *
 */

#ifndef GAZEBOCONFIG_HH
#define GAZEBOCONFIG_HH

#include <string>
#include <list>

namespace gazebo
{

/// \addtogroup gazebo_server
/// \brief Local configuration on this computer about how gazebo server should work 
/// \{

  class GazeboConfig
  {
    /// \brief Constructor
    public: GazeboConfig();

    /// \brief destructor
    public: ~GazeboConfig();

    /// \brief True if the string is null
    public: void Load();

    /// \brief Get paths to Gazebo install 
    public: std::list<std::string>& GetGazeboPaths();
 
    /// Paths gazebo install
    private: std::list<std::string> gazeboPaths;

  };


/// \}
}

#endif
