/*
 *   TMF
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

#ifndef DF_PARSER_EDGE_H
#define DF_PARSER_EDGE_H

#include <string>
#include <vector>
#include <map>
#include "actor.h"

using namespace std;

/*!
 * Edge class
 *  A edge has reference to its source and sink ports.
 *
 */
class Edge {
private:
	string name; /**< Edge name */
	bool visited; /**< Boolean to check the edge is visited in dfs algorithm. */
	Actor * src_actor;
	Actor * snk_actor;

	string src_port; /**< Source port of the edge */
	string snk_port; /**< Sink port of the edge */

	int src_rate;
	int snk_rate;

public:
	/*!
	 * Edge constructor
	 *
	 */
	Edge();
	
	/*!
	 * Edge constructor with name
	 *
	 * \param edgename
	 * 	Name of the edge
	 *
	 */
	Edge(string edgename);
	
	/*!
	 * Get name of the edge
	 *
	 * \return
	 * 	Name of the edge
	 *
	 */
	string get_name();
	
	
	/*!
	 * Set the visited boolean.
	 *
	 * \param v
	 * 	The boolean value to assign to the visited.
	 *
	 */
	void set_visited(bool v);
	
	/*!
	 * Get the visited boolean.
	 *
	 * \return
	 * 	The value of the visited.
	 *
	 */
	bool get_visited();
	
	/*!
	 * Get source actor of the edge.
	 *
	 * \return
	 * 	Source actor of the edge.
	 *
	 */
	Actor * get_source_actor();
	
	/*!
	 * Get sink actor of the edge.
	 *
	 * \return
	 * 	Sink actor of the edge.
	 *
	 */
	Actor * get_sink_actor();
	
	void set_source_actor(Actor * src);
	void set_sink_actor(Actor * snk);
	
	/*!
	 * Set the source port of the edge
	 *
	 * \param src
	 * 	The source port name.
	 *
	 */
	void set_source_port(std::string src);
	
	/*!
	 * Set the sink port of the edge
	 *
	 * \param snk
	 * 	The sink port name.
	 *
	 */
	void set_sink_port(std::string snk);
	
	std::string get_source_port();
	std::string get_sink_port();

	/*!
	 * Set source rate of the edge.
	 *
	 * \param rate
	 * 	The source rate to set.
	 *
	 */
	void set_source_rate(int rate);
	
	/*!
	 * Set sink rate of the edge.
	 *
	 * \param rate
	 * 	The sink rate to set.
	 *
	 */
	void set_sink_rate(int rate);
	
	/*!
	 * Get source rate of the edge.
	 *
	 * \return
	 * 	The source rate of the edge.
	 *
	 */
	int get_source_rate();

	/*!
	 * Get sink rate of the edge.
	 *
	 * \return
	 * 	The sink rate of the edge.
	 *
	 */
	int get_sink_rate();
};

#endif
