/*
 *   libdataflow
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

using namespace df;

Edge::Edge() {
	name = "";
	visited = false;
	src_actor = nullptr;
	snk_actor = nullptr;
	src_port = "";
	snk_port = "";
	src_rate = 1;
	snk_rate = 1;
}

Edge::Edge(std::string edgename) : Edge() {
	name = edgename;
}

std::string Edge::getName() {
	return name;
}

void Edge::setSource(Actor * src) {
	src_actor = src;
}
void Edge::setSink(Actor * snk) {
	snk_actor = snk;
}
void Edge::setVisited(bool v) {
	visited = v;
}
bool Edge::getVisited() {
	return visited;
}
Actor * Edge::getSource() {
	return src_actor;
}
Actor * Edge::getSink() {
	return snk_actor;
}
void Edge::setSourceRate(int r) {
	src_rate = r;
}
void Edge::setSinkRate(int r) {
	snk_rate = r;
}

void Edge::setSourcePort(std::string p) {
	src_port = p;
}
void Edge::setSinkPort(std::string p) {
	snk_port = p;
}

std::string Edge::getSourcePort() {
	return src_port;
}
std::string Edge::getSinkPort() {
	return snk_port;
}

int Edge::getSourceRate() {
	return src_rate;
}
int Edge::getSinkRate() {
	return snk_rate;
}
