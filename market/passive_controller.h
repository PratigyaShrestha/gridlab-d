/** $Id: passive_controller.h 1182 2009-09-09 22:08:36Z mhauer $
	Copyright (C) 2009 Battelle Memorial Institute
	@file passive_controller.h
	@addtogroup passive_controller
	@ingroup market

 **/

#ifndef _passive_controller_H
#define _passive_controller_H

#include <stdarg.h>
#include "auction.h"
#include "gridlabd.h"

class passive_controller {
public:
	passive_controller(MODULE *);
	int create();
	int init(OBJECT *parent);
	int isa(char *classname);
	TIMESTAMP presync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP sync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP postsync(TIMESTAMP t0, TIMESTAMP t1);
public:
	static CLASS *oclass;
public:
	// control mode
	typedef enum {
		CM_NONE=0,
		CM_RAMP=1,
		CM_DUTYCYCLE=4,
		CM_PROBOFF=5,	// probabilistic shut-off
	} CONTROLMODE;
	CONTROLMODE control_mode;
	// distribution type, for probabilistic control
	typedef enum {
		PDT_NORMAL,
		PDT_EXPONENTIAL,
		PDT_UNIFORM
	} DISTRIBUTIONTYPE;
	DISTRIBUTIONTYPE distribution_type;
	double comfort_level;
	// sensitivity
	double sensitivity;					///<
	int64 period;
	// observation tuple
	double observation;					///<
	double obs_mean;					///<
	double obs_stdev;					///<
	// expected value
	double expectation;					///<
	void *expectation_addr;				///<
	PROPERTY *expectation_property;			///<
	char32 expectation_propname;		///<
	OBJECT *expectation_object;			///<
	// input from series controllers
	int32 input_state;					///< storage for any binary control input
	double input_setpoint;				///< storage for any finite control input
	bool input_chained;					///< flag to determine if there are any attached controllers
	// binary on/off output
	int output_state;					///< binary output value
	void *output_state_addr;			///< binary output value addr
	PROPERTY *output_state_prop;		///< binary output property
	char32 output_state_propname;		///< binary output property name
	double output_setpoint;				///< setpoint output value
	void *output_setpoint_addr;			///< setpoint value addr
	PROPERTY *output_setpoint_property;	///< setpoint property
	char32 output_setpoint_propname;	///< setpoint property name
	OBJECT *observation_object;					///< observed object
	void *observation_addr;				///< observation value addr
	PROPERTY *observation_prop;			///< observation property
	char32 observation_propname;		///< observation prop name
	void *observation_mean_addr;		///< observation mean value addr
	PROPERTY *observation_mean_prop;
	char32 observation_mean_propname;	///< observation mean property name
	void *observation_stdev_addr;		///< observation standard deviation value addr
	PROPERTY *stdev_observation_property;
	char32 observation_stdev_propname;	///< observation standard devation property name
	TIMESTAMP last_cycle_time;			///< last operation cycle time
	int32 cycle_length;					///< operation cycle time delays
	/* setpoint calculations */
	/* actuator calculations */
	double ramp_high, ramp_low;
	double range_high, range_low;
	double prob_off;
	double base_setpoint;
private:
	int calc_ramp(TIMESTAMP t0, TIMESTAMP t1);
	int calc_dutycycle(TIMESTAMP t0, TIMESTAMP t1);
	int calc_proboff(TIMESTAMP t0, TIMESTAMP t1);
	int orig_setpoint;
	int64 last_cycle;
};

#endif // _passive_controller_H