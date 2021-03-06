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

#include "actor.h"

using namespace df;
using namespace std;

Actor::Actor(const string &name) : status(OK), stepno(0), name(name) {
  realtime = false;
  distributed = false;
  home_path = std::getenv("HOME");
  df_path = home_path + "/Documents/df/";  
  dfout_path = df_path + "outputs/";
}

std::string Actor::getName() {
	return name;
}
void Actor::log(std::string msg) {
  cpuid = sched_getcpu();
  string s = name + ": [" + to_string(stepno) + "] [" + to_string(now()) + "] [" + to_string(cpuid) + "] " + msg + "\n";
  iolock->lock(); 
  std::cout << s;
  iolock->unlock();
}
void Actor::sleep(int s) {
  this_thread::sleep_for(chrono::milliseconds{rand()%s});
}

std::string Actor::getSingleInputPort() {
	if (inputPorts.size() == 1)
		return inputPorts.begin()->second->getName();
	return "";
}

std::string Actor::getSingleOutputPort() {
	if (outputPorts.size() == 1)
		return outputPorts.begin()->second->getName();
	return "";
}

int Actor::connectActor(Actor * snk) {
  return connectActor(snk,1,1);  
}

int Actor::connectActor(std::string outp, std::string host, int portnb) {

  if (outputPorts.find(outp) == outputPorts.end()) {
	  log("port "+outp+" is not found.");
 	  return -1; 
  }  

  if (outputPorts.find(outp) == outputPorts.end())
    return -1;

  return outputPorts[outp]->connectPort(host, portnb);

}

int Actor::connectActor(Actor * snk, int p, int c) {
  
  bool linked = false;
  for (auto fout : outputPorts) {
    for (auto fin : snk->inputPorts) {
      
      string typeOut = fout.second->getPortCap();
      string typeIn = fin.second->getPortCap();
      
      if ( fin.second->getLinked() == 0 && (typeOut == typeIn)) {
	
	fout.second->connectPort(fin.second);
	fout.second->setRate(p);
	fin.second->setRate(c);
	
	linked = true;
	break;
      }
    }
    if (linked)
      break;
  }
  return 0;
}

int Actor::connectActor(Actor * snk, std::string outp, std::string inp, int p, int c) {
	
  IPort * in;
  OPort * out;

  //retrieve index from outp
  int index = -1;

  if (outp == "" && inp == "")
	  return connectActor(snk, p, c);

  if (outputPorts.find(outp) == outputPorts.end()) {
	  log("port "+outp+" is not found.");
 	  return -1; 
  } else
	out = outputPorts[outp];

  if (snk->inputPorts.find(inp) == snk->inputPorts.end()) {
	  log("port "+inp+" of actor "+snk->getName()+" is not found.");
	  return -1;
  } else
	in = snk->inputPorts[inp];
 
  if ( in->getLinked() > 0 ) {
	 log("port "+inp+" is already linked.");
	 return -1;
  }

  string type_out = out->getPortCap();
  string type_in = in->getPortCap();
 
  if (type_out != type_in) {
	log("types of ports "+inp+" and "+outp+" do not match.");
	return -1;
  }	

  int ret = out->connectPort(in, index);
  out->setRate(p);
  in->setRate(c);
  return ret;

}
	
void Actor::startInit() {
  tinit = thread(&Actor::initActor, this);
}

void Actor::startRun(int cpu) {

  trun = thread(&Actor::runActor, this);
 
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu, &cpuset);

  int rc = pthread_setaffinity_np(trun.native_handle(), sizeof(cpu_set_t), &cpuset);
  if (rc != 0)
	  log("error calling pthread_setaffinity_np");

}

void Actor::waitInit() {
  tinit.join();

}

void Actor::waitRun() {
  trun.join();
  if (distributed) {
    for (auto p : inputPorts) {
	    p.second->waitAccept();
    }
  }

}

void Actor::setIOLock(mutex * mux) {
  iolock = mux;
}

void Actor::initActor() {

  if (!propEmpty("realtime"))
	  realtime = getPropBool("realtime");

  if (!propEmpty("distributed"))
	  distributed = getPropBool("distributed");

  if (distributed) {
    for (auto p : inputPorts) {
	    listen(p.second);
	    p.second->startAccept();
    }
  }
   
  init();

}

void Actor::listen(IPort * port) {
      std::string name = port->getName();
      if (propEmpty(name+"_port")) {
	      log(name+"_port is not specified.");
      } 
      else {
	      int portnb = getPropInt(name+"_port");
      	      port->listen(portnb);
      }
}

void Actor::runActor() {

  if (!distributed) {
    for (auto p : inputPorts) {
      if (p.second->getLinked() == 0) {
        log(p.second->getName()+string(" is not connected"));
      	setStatus(ERROR);
      }
    }
    for (auto p : outputPorts) {
      if (p.second->getLinked() == 0) {
        log(p.second->getName()+string(" is not connected"));
        setStatus(ERROR);
      }
    }
  }

  while(getStatus() != EOS) {
    if (distributed) {
	    runDist();
    } else if (!realtime) {
    	    run();
    } else {
	    runRT();
    }
    stepno++;
  }
  
}

void Actor::hstart() { 
	hrtstart = std::chrono::high_resolution_clock::now(); 
}
void Actor::hend(std::string msg) { 
	hrtend = std::chrono::high_resolution_clock::now(); 
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(hrtend - hrtstart); 
	log(msg+" exect = "+std::to_string(time_span.count())); 
    }
void Actor::start() { 
	tstart = clock(); 
}
void Actor::end(std::string msg) { 
	tend = clock();
	log(msg+" exect = "+std::to_string(double(tend - tstart)/CLOCKS_PER_SEC)); 
}

unsigned long Actor::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Actor::~Actor() { 
}
