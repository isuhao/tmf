/*
 *   DF
 *   Copyright (C) 2018
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DF_PORT_H_
#define DF_PORT_H_

#include "attribute.h"
#include "buffer.h"
#include "port_caps.h"

#include <typeinfo>
#include <thread>
#include <vector>
#include <map>
#include <string>

namespace df {
  
  /*!
   * \class Port
   * Abstraction of a port in a actor.
   * A port can be either input port of output port.
   */
  
  class Port {
    
  private:
    std::string name; /**< The name of the port */
    int linked; /**< The number of port connected to this port */
    
  protected:
    
    int rate; /**< The port rate */
    Buffer<Attribute> * attrbuf;
    int attrindex;
    PortCaps portCaps;
    
  public:
    
    /*!
     * Port constructor
     *
     * \param name The name of the actor.
     */
    Port(std::string name);
    
    /*!
     * Get the name of the port
     *
     * \return the name of the port.
     */
    std::string getName();
    
    void setRate(int r);
    int getRate();

    const PortCaps & getPortCaps() const;
    /*!
     * Get the number of the ports connected to this port
     *
     * \return the number of the port.
     */
    int getLinked();
    
     /*!
     * Determine if the port is connected
     *
     * \return true if the port is connected, false otherwise
     */
    bool isConnected();
    
    /*!
     * Increase the number of the ports linked to the port.
     * (The actor uses this function when it connects two actors)
     *
     */
    void increaseLinked();
    
    Attribute * getAttr();
    
    virtual void connectPort(Port* n) {}
    
    virtual void connectPort(Port* n, int p, int c) {}
    
    /*!
     * Port descructor
     *
     */
    virtual ~Port() {}
  };
  
}
#endif /* DF_PORT_H_ */