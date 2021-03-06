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
/*
 * Desc: Factory Position2d controller.
 * Author: Nathan Koenig
 * Date: 01 Feb 2007
 * SVN info: $Id: Factory.cc 7748 2009-05-30 09:46:23Z robotos $
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

#include "Global.hh"
#include "XMLConfig.hh"
#include "Model.hh"
#include "World.hh"
#include "gazebo.h"
#include "GazeboError.hh"
#include "gazebo.h"
#include "Factory.hh"

using namespace gazebo;

////////////////////////////////////////////////////////////////////////////////
// Constructor
Factory::Factory()
{
  // Prefix and suffix for xml files
  this->xmlPrefix = "<?xml version='1.0'?> <gazebo:world xmlns:xi='http://www.w3.org/2001/XInclude' xmlns:gazebo='http://playerstage.sourceforge.net/gazebo/xmlschema/#gz' xmlns:model='http://playerstage.sourceforge.net/gazebo/xmlschema/#model' xmlns:sensor='http://playerstage.sourceforge.net/gazebo/xmlschema/#sensor' xmlns:body='http://playerstage.sourceforge.net/gazebo/xmlschema/#body' xmlns:geom='http://playerstage.sourceforge.net/gazebo/xmlschema/#geom' xmlns:joint='http://playerstage.sourceforge.net/gazebo/xmlschema/#joint' xmlns:interface='http://playerstage.sourceforge.net/gazebo/xmlschema/#interface' xmlns:rendering='http://playerstage.sourceforge.net/gazebo/xmlschema/#rendering' xmlns:renderable='http://playerstage.sourceforge.net/gazebo/xmlschema/#renderable' xmlns:controller='http://playerstage.sourceforge.net/gazebo/xmlschema/#controller' xmlns:physics='http://playerstage.sourceforge.net/gazebo/xmlschema/#physics' >";


  this->xmlSuffix = "</gazebo:world>";

  this->factoryIface = (FactoryIface*)IfaceFactory::NewIface("factory");

  // Create the iface
  try
  {
    this->factoryIface->Create(World::Instance()->GetGzServer(), "default");
  }
  catch (std::string e)
  {
    gzthrow(e);
  }

}

////////////////////////////////////////////////////////////////////////////////
// Destructor
Factory::~Factory()
{
  if (this->factoryIface)
  {
    this->factoryIface->Close();
    this->factoryIface->Destroy();
    delete this->factoryIface;
    this->factoryIface = NULL;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Initialize the controller
void Factory::Init()
{
  // initialize newModel to blank
  strcpy((char*)this->factoryIface->data->newModel,"");
}

////////////////////////////////////////////////////////////////////////////////
// Update the controller
void Factory::Update()
{
  // If there is a string, then add the contents to the world
  this->factoryIface->Lock(1);

  if (strcmp((const char*)this->factoryIface->data->newModel,"")!=0)
  {
    //std::cout << " factory update: " << this->factoryIface->data->newModel << std::endl;
    std::string xmlString;
    std::string xmlMiddle = (const char*)(this->factoryIface->data->newModel);
    
    // Strip leading <?xml...?> tag, if present, to allow the client to
    // pass the contents of a valid .model file
    std::string xmlVersion = "<?xml version=\"1.0\"?>";
    int i = xmlMiddle.find(xmlVersion);
    if(i >= 0)
      xmlMiddle.replace(i, xmlVersion.length(), "");

    xmlString = this->xmlPrefix + xmlMiddle + this->xmlSuffix;

    // Add the new models into the World
    World::Instance()->InsertEntity( xmlString);

    strcpy((char*)this->factoryIface->data->newModel,"");
  }

  // Attempt to delete a model by name, if the string is present
  if (strcmp((const char*)this->factoryIface->data->deleteModel,"")!=0)
  {
    World::Instance()->DeleteEntity((const char*)this->factoryIface->data->deleteModel);

    strcpy((char*)this->factoryIface->data->deleteModel,"");
  }
  this->factoryIface->Unlock();

}
