/**************************************************************//**

\file TOF_Sensor.h

Function prototypes and defines for communication with the used sensor.

******************************************************************/
#ifndef TOF_SENSOR_H_
#define TOF_SENSOR_H_

#pragma once

//#include <TOF_Framework.h>

#include <pmdsdk2.h>
#include <pmdsdk2common.h>
#include <pmddatadescription.h>

#include <QString>

#define MAX_APP_CHAR 64
//#define TRUE 1
//#define FALSE 0

/** This struct contains configuration for sensors.
* Stores data for every sensor and a handle.
*/
struct stSensorConfig
{
    unsigned short usSensorID;				/**< ID of connected sensor */
    char scSensorIP[MAX_APP_CHAR];			/**< IP address of sensor */
    char scSensorSerial[MAX_APP_CHAR];		/**< MAC of sensor */
    PMDHandle HndSensor;					/**< sensor handle */
    unsigned short usResX;					/**< resolution x */
    unsigned short usResY;					/**< resolution y */
    unsigned short usApertureH;				/**< aperture size horizontal */
    unsigned short usApertureV;				/**< aperture size vertical */
    unsigned short usSensorOnline;			/**< number of frames to capture */
};

int SENSOR_importCSV(struct stSensorConfig *stCurrentSensor, float **pflData);
int SENSOR_exportCSV(struct stSensorConfig *stCurrentSensor, float **pflData);

int SENSOR_Connect(struct stSensorConfig *stCurrentSensor, QString *console);
int SENSOR_Close(struct stSensorConfig *stCurrentSensor, QString *console);
//int SENSOR_Capture(struct stSensorConfig *stCurrentSensor, CvMat *pCvMatFrame, QString *console);
int SENSOR_SetExpTime(struct stSensorConfig *stCurrentSensor, int slExpIndex, int slExpTime);

unsigned int SENSOR_GetExpTime(struct stSensorConfig *stCurrentSensor, int slExpIndex);


#endif /*MLI_SENSOR_H_*/
