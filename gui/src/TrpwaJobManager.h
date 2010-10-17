/*
 * TrpwaJobManager.h
 *
 *  Created on: Oct 12, 2010
 *      Author: Promme
 *
 *      class to manages jobs on a cluster farm
 *
 *      (12.10.10)
 *      - Declaration of singleton class
 */

#include <set>
#include <string>

using namespace std;

#ifndef TRPWAJOBMANAGER_H_
#define TRPWAJOBMANAGER_H_

// these are the available farm types
// that might differ in job handling
static const string arrfarmtypes [] = {
		"local ",
		"cern ",
		"gridka ",
		"mainz ",
		"munich "
}; // warning, do only add at the end and do not change the order

static const set<string> farmtypes(arrfarmtypes, arrfarmtypes+5);

class TrpwaJobManager{
public:
	// return the instance to this object
	static TrpwaJobManager* Instance();

	// return the available farm type
	// (local is always available)
	string GetFarmType(){return _available_farmtype;};

	// send a job to the farm with the command specified
	// in the command string
	// job is an optional job name that will be used for the submitted script
	// the script will be erased after execution
	// duration is the optional job queue length
	// please use always filenames with full path!
	bool SendJob(string command, string jobname = "job", int duration = 60);

private:
	string _available_farmtype;
	string _temp_space; // path to store scripts to (default is $(pwd)/rootpwa_gui_scripts)
	static TrpwaJobManager* _pinstance;

	// farm type is checked on creation
	TrpwaJobManager();
	virtual ~TrpwaJobManager();

	// searches for signatures showing the
	// type of farm
	void CheckFarmType();
};

#endif /* TRPWAJOBMANAGER_H_ */