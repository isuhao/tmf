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

#include "edge.h"

Edge::Edge() {
	name = "";
	visited = false;
	source = nullptr;
	sink = nullptr;
}

Edge::Edge(string edgename) : Edge() {
	name = edgename;
}

string Edge::get_name() {
	return name;
}

void Edge::connect_source(Port * sourceport) {
	source = sourceport;
}
void Edge::connect_sink(Port * sinkport) {
	sink = sinkport;
}
void Edge::set_visited(bool v) {
	visited = v;
}
bool Edge::get_visited() {
	return visited;
}

Actor * Edge::get_source_actor() {
	return src_actor;
}

Actor * Edge::get_sink_actor() {
	return snk_actor;
}

void Edge::set_source_actor(Actor * src) {
	src_actor = src;
}

void Edge::set_sink_actor(Actor * snk) {
	snk_actor = snk;
}

void Edge::set_source_rate(int r) {
	source->set_rate(r);
}
void Edge::set_sink_rate(int r) {
	sink->set_rate(r);
}
int Edge::get_source_rate() {
	return source->get_rate();
}
int Edge::get_sink_rate() {
	return sink->get_rate();
}
