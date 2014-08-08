/*
 *
 *  Tiny Multimedia Framework
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Filter.h"
#include "Port.h"

Filter::Filter(const string &name) {

	this->name = name;
	linked = 0;
	inputFed = 0;
	bus = 0;

}

void Filter::connectFilter(Filter * f) {

	vector<Port*>::iterator itOut;
	vector<Port*>::iterator itIn;

	bool linked = false;
	for (itOut = this->outputPorts.begin(); itOut != this->outputPorts.end();
			++itOut) {
		for (itIn = f->inputPorts.begin(); itIn != f->inputPorts.end();
				++itIn) {

			string typeOut = ((Port*) (*itOut))->getType();
			string typeIn = ((Port*) (*itIn))->getType();
			if (((Port*) (*itIn))->getLinked() == 0 && (typeOut == typeIn)) {

				((Port*) (*itOut))->addNextPort(((Port*) (*itIn)));
				linked = true;
				break;
			}
		}
		if (linked)
			break;
	}
}

void Filter::setProp(const string & key, const string & val) {
	bus->setProp(key,val);
}

string Filter::getProp(const string & key) {
	return bus->getProp(key);
}

FilterStatus Filter::executeFilter() {
	FilterStatus status = FILTER_SUCCESS;

	if (linked > 0 && inputFed + 1 != linked) {
		inputFed++;
		return FILTER_WAIT_FOR_INPUT;
	}

	inputFed = 0;
	status = process();
	return status;
}

//void Filter::initializeFilter() {
//	init();
//}

Filter::~Filter() {

}
