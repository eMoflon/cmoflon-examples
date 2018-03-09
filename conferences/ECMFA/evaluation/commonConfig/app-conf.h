#ifndef __APP_CONF_H_
#define __APP_CONF_H_

#include "app-conf-constants.h"

#define COMPONENT_APPLICATION                  COMPONENT_APPLICATION_DATACOLLECTION
#define COMPONENT_NEIGHBORDISCOVERY            COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST
#define COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT_DISTANCE
#define COMPONENT_NETWORK                      COMPONENT_NETWORK_MAKEFILE
#define COMPONENT_POWERCONTROL                 COMPONENT_POWERCONTROL_BINARYSEARCH
#define COMPONENT_RADIO                        COMPONENT_RADIO_AUTODETECT

/*
 * The topology control algorithm can be set from outside by passing the appropriate integer value 
 * (as defined in app-conf-constants.h) to make via the environment variable TOPOLOGYCONTROL_PREDEFINED_ALGORITHM.
 * Example: make app.sky TARGET=sky TOPOLOGYCONTROL_PREDEFINED_ALGORITHM=1 (for COMPONENT_TOPOLOGYCONTROL_NULL)
 */
#ifndef COMPONENT_TOPOLOGYCONTROL
#define COMPONENT_TOPOLOGYCONTROL              COMPONENT_TOPOLOGYCONTROL_LMST
#endif

#define TESTBED_SIMULATOR 1
#define TESTBED_PILOTY 2
#define TESTBED_FLOCKLAB 3

#define TESTBED TESTBED_FLOCKLAB

#define TOPOLOGYCONTROL_LINKS_HAVE_STATES true

#if TESTBED == TESTBED_SIMULATOR
	#undef COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT
	#define COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT_RSSI
	#define COMPONENT_NETWORK_RIME_BASESTATION "1.0"
	#define COMPONENT_NETWORK_IPV6_BASESTATION "aaaa::212:7401:1:101"

	#define COMPONENT_APPLICATION_MESHMESSAGES_NODESLIST_RIME "1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0"

	#define UTILITIES_CONTIKIRANDOM_SEED UTILITIES_CONTIKIRANDOM_SEED_STATIC

	#define COMPONENT_APPLICATION_DATACOLLECTION_MESSAGESIZE 50
	#define COMPONENT_APPLICATION_DATACOLLECTION_INTERVALSEND_MIN (30-5)
	#define COMPONENT_APPLICATION_DATACOLLECTION_INTERVALSEND_MAX (30+5)
	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_INTERVALBROADCAST_MIN (10-5)
	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_INTERVALBROADCAST_MAX (10+5)
	#define COMPONENT_TOPOLOGYCONTROL_AKTC_K 1.2
	#define COMPONENT_TOPOLOGYCONTROL_AKTC_UPDATEINTERVAL 330
	#define COMPONENT_TOPOLOGYCONTROL_LKTC_STRETCHFACTOR 1.5
	#define COMPONENT_TOPOLOGYCONTROL_LKTC_UPDATEINTERVAL 330


	//#define WITH_TINYOS_AUTO_IDS 1
	#define COMPONENT_NEIGHBORDISCOVERY_NEIGHBORS_MEMORY 80 // funzt, aber geht kleiner?
	#define PACKETBUF_CONF_SIZE 100 // funzt, aber geht kleiner
#elif TESTBED == TESTBED_PILOTY
	// piloty ist instabil, nicht nutzen :(
#elif TESTBED == TESTBED_FLOCKLAB
	#define WITH_TINYOS_AUTO_IDS 1
	#define COMPONENT_NETWORK_RIME_BASESTATION "1.0"
	#define COMPONENT_NETWORK_IPV6_BASESTATION "aaaa::212:7400:115e:c8fe"
	#define COMPONENT_NEIGHBORDISCOVERY_EDGEWEIGHT_DISTANCE_POSITIONS "1.0=22|25,2.0=18|105,3.0=90|239,4.0=69|65,6.0=95|344,7.0=679|121,8.0=80|130,10.0=360|200,11.0=561|120,13.0=613|293,14.0=628|173,15.0=128|121,16.0=85|404,17.0=575|333,18.0=233|399,19.0=505|345,20.0=475|324,22.0=159|345,23.0=410|340,24.0=321|393,25.0=571|234,26.0=464|217,27.0=270|397,28.0=159|304,31.0=221|218,32.0=194|191,33.0=71|192,200.0=242|532,201.0=157|775,202.0=220|640,204.0=144|543"
	#define UTILITIES_CONTIKIRANDOM_SEED UTILITIES_CONTIKIRANDOM_SEED_RANDOM

	#define COMPONENT_APPLICATION_DATACOLLECTION_MESSAGESIZE 50
	#define COMPONENT_APPLICATION_DATACOLLECTION_INTERVALSEND_MIN (30-5)
	#define COMPONENT_APPLICATION_DATACOLLECTION_INTERVALSEND_MAX (30+5)

	#define COMPONENT_APPLICATION_MESHMESSAGES_MESSAGESIZE 50
	#define COMPONENT_APPLICATION_MESHMESSAGES_INTERVALSEND_MIN (30-5)
	#define COMPONENT_APPLICATION_MESHMESSAGES_INTERVALSEND_MAX (30+5)
	#define COMPONENT_APPLICATION_MESHMESSAGES_NODESLIST_RIME "1.0,2.0,3.0,4.0,6.0,7.0,8.0,10.0,11.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0,31.0,32.0,33.0"

	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_MAXBROADCASTS 5
	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_INTERVALBROADCAST_MIN (120-10)
	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_INTERVALBROADCAST_MAX (120+10)
	#define COMPONENT_NEIGHBORDISCOVERY_TWOHOPBROADCAST_DECAYINTERVAL 3600
	#define COMPONENT_TOPOLOGYCONTROL_AKTC_K 1.2
	#define COMPONENT_TOPOLOGYCONTROL_AKTC_UPDATEINTERVAL 660
	#define COMPONENT_TOPOLOGYCONTROL_LKTC_STRETCHFACTOR 1.5
	#define COMPONENT_TOPOLOGYCONTROL_LKTC_UPDATEINTERVAL 660
	#define COMPONENT_TOPOLOGYCONTROL_LMST_UPDATEINTERVAL 660
	#define COMPONENT_TOPOLOGYCONTROL_LSTARKTCALGORITHM_UPDATEINTERVAL 660
	#define COMPONENT_TOPOLOGYCONTROL_KTCALGORITHM_UPDATEINTERVAL 660
	#define COMPONENT_TOPOLOGYCONTROL_LMSTALGORITHM_UPDATEINTERVAL 660

	#define COMPONENT_NEIGHBORDISCOVERY_NEIGHBORS_MEMORY 120 // funzt, aber geht kleiner?
	#define PACKETBUF_CONF_SIZE 150 // funzt, aber geht kleiner?
	#define APP_PRINT_EVALUATION 1
#endif

#endif /* __APP_CONF_H_ */