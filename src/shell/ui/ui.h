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

#ifndef DF_UI_H
#define DF_UI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include "parser/parser.h"
#include "core/df.h"

using namespace std;

/*!
 * \class UI
 * The user interface class for RDF.
 *
 */
class UI {

protected:
	Parser * parser; /**< Parser. */

	map<string, function<int()>> cmd; /**< A map from command name to command funtion. */
	map<string, string> comment; /**< A map from command name to command description. */

	/*!
	 * Display a graph to the user
	 *
	 * \param g
	 * 	Reference to the graph to display
	 *
	 * \return
	 *
	 */ 
	int display_graph(Graph * g);

	/*!
	 * Display the RDF graph to the user
	 *
	 * \return
	 *
	 */ 
	int display_df_graph();

	/*!
	 * Display the help menu to the user
	 *
	 * \return
	 *
	 */ 
	int display_help();

	/*!
	 * Run the data graph
	 *
	 * \return
	 *
	 */ 
	int run_graph();

	/*!
	 * Process a command given by the user
	 *
	 *  \param command
	 * 	A string containing the command
	 *
	 * \return
	 *
	 */ 
	int process_command(string command);

public:

	/*!
	 * UI constructor
	 *
	 *  \param argc
	 * 	The number of arguments
	 *
	 *  \param argv
	 *  	The list of strings containing the arguments
	 *
	 */ 
	UI(int argc, char * argv[], Parser * parser);
	
	/*!
	 * Main loop of the UI
	 *
	 * \return
	 *
	 */ 
	int loop();
};

#endif