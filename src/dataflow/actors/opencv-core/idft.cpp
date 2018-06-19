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

#include "idft.h"

using namespace df;
using namespace std;

ActorRegister<Idft> Idft::reg("Idft");

Idft::Idft(const string& name) : Actor(name) {
  input = createInputPort<cv::Mat>("input");
  output = createOutputPort<cv::Mat>("output");
}

void Idft::init() {

}

void Idft::run() {

  cv::Mat * in = consume(input);	
  cv::Mat * out = produce(output);
  in->convertTo(*out, CV_32F);
  cv::idft(*out, *out);
  log("sending frame "+to_string(stepno));
  release(input);
  release(output);

}

Idft::~Idft() {
  destroyPort(input);
  destroyPort(output);
}