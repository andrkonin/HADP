
/**************************************************************//**

\file TOF_Sensor.c

This module implements functions to communicate with the sensor.

\version  2009/03/11 initial version

******************************************************************/

#include <stdio.h>
#include <string.h>
#include <QString>

#include <TOF_Sensor.h>


int slSensorsConnected = 0;

/** @defgroup Sensor TOF Framework sensor handling
  Functions to handle sensor connections and data capture .
   @{
 */

/**************************************************************************//**

Connect sensor with settings from stCurrentSensor. Read serial number from sensor.

\param stSensorConfig configuration settings

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_Connect(struct stSensorConfig *stCurrentSensor, QString *console)
{

    return 0;
}

/**************************************************************************//**

Capture data from sensor.

\param stSensorConfig sensor configuration
\param pCvMatFrame	  to save data

\return TRUE on success FALSE on failure
******************************************************************************/
/*int SENSOR_Capture(struct stSensorConfig *stCurrentSensor, CvMat *pCvMatFrame, QString *console)
{
   return 0;
}*/

/**************************************************************************//**

Get exposure time from sensor with index 'slExpIndex'.

\param stCurrentSensor 		sensor configuration
\param slExpIndex 			index of exposure time 0 to 2

\return exposure time or -1 on errors
******************************************************************************/
unsigned int SENSOR_GetExpTime(struct stSensorConfig *stCurrentSensor, int slExpIndex)
{

    return 0;
}

/**************************************************************************//**

Set exposure time from sensor 'slSensorNumber' with index 'slExpIndex'.

\param stCurrentSensor 		sensor configuration
\param slExpIndex 			index of exposure time 0 to 2
\param ulExpTime			exposure time to set

\return TRUE on success
******************************************************************************/
int SENSOR_SetExpTime(struct stSensorConfig *stCurrentSensor, int slExpIndex, int ulExpTime)
{
   return 0;
}
/**************************************************************************//**

Close connection to the used sensor.

\param stCurrentSensor  sensor configuration

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_Close(struct stSensorConfig *stCurrentSensor,QString *console)
{
return 0;
}


/**************************************************************************//**

Export raw data to CSV.

\param stCurrentSensor 	sensor configuration
\param pflData			data pointer

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_exportCSV(struct stSensorConfig *stCurrentSensor, float **pflData)
{
   return 0;
}


/**************************************************************************//**

Import CSV.

\param stCurrentSensor	sensor configuration
\param pflData			data pointer

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_importCSV(struct stSensorConfig *stCurrentSensor, float **pflData)
{
   return 0;
}

/** @} */ // end of Sensor


