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
 *
 */
/* Desc: A ray
 * Author: Nate Koenig
 * Date: 14 Oct 2009
 * SVN: $Id:$
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

#include "ODEBody.hh"
#include "ODEGeom.hh"
#include "ODEPhysics.hh"
#include "ODERayShape.hh"

using namespace gazebo;

//////////////////////////////////////////////////////////////////////////////
// Constructor
ODERayShape::ODERayShape( Geom *parent )
    : RayShape(parent)
{
  ODEGeom *geom = (ODEGeom*)this->parent;

  // Create default ray with unit length
  geom->SetGeom( dCreateRay( geom->GetSpaceId(), 1.0 ),  false );
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
ODERayShape::~ODERayShape()
{
}

////////////////////////////////////////////////////////////////////////////////
// Update the ray geom
void ODERayShape::Update()
{
  ODEGeom *geom = (ODEGeom*)this->parent;

  Vector3 dir;

  this->globalStartPos = this->parent->GetBody()->GetAbsPose().CoordPositionAdd(
      this->relativeStartPos);
  this->globalEndPos = this->parent->GetBody()->GetAbsPose().CoordPositionAdd(
      this->relativeEndPos);

  dir = this->globalEndPos - this->globalStartPos;
  dir.Normalize();

  if (this->contactLen != 0)
  {
    dGeomRaySet(geom->GetGeomId(), this->globalStartPos.x,
        this->globalStartPos.y, this->globalStartPos.z,
        dir.x, dir.y, dir.z);

    dGeomRaySetLength( geom->GetGeomId(),
        this->globalStartPos.Distance(this->globalEndPos) );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Set the starting point and direction
void ODERayShape::SetPoints(const Vector3 &posStart, const Vector3 &posEnd)
{
  Vector3 dir;
  ODEGeom *geom = (ODEGeom*)this->parent;

  RayShape::SetPoints(posStart, posEnd);

  dir = this->globalEndPos - this->globalStartPos;
  dir.Normalize();

  dGeomRaySet(geom->GetGeomId(), this->globalStartPos.x,
              this->globalStartPos.y, this->globalStartPos.z,
              dir.x, dir.y, dir.z);

  dGeomRaySetLength( geom->GetGeomId(),
                     this->globalStartPos.Distance(this->globalEndPos) );
}
