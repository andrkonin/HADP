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

	int slResult;			/* keeps return values */

	char scLogTxt[64];		/* array for log */
	char scSerial[64];

	/* connect to sensor */


	/* open connection */

        printf ("--> Connecting SENSOR %s", stCurrentSensor->scSensorIP);
        console->sprintf("--> Connecting SENSOR %s\n", stCurrentSensor->scSensorIP);
        slResult = pmdOpen (&stCurrentSensor->HndSensor, "/home/student/o3.L32.pcp", stCurrentSensor->scSensorIP , "/home/student/o3.L32.pcp", "");
	if (slResult != PMD_OK)
	{
		sprintf (scLogTxt, "--> Could not connect to sensor Error: %i\n", slResult);

                //printf(scLogTxt);
                console->append(scLogTxt);
                stCurrentSensor->usSensorOnline = 0;
		return FALSE;
	}

	slResult = pmdUpdate(stCurrentSensor->HndSensor);
	if (slResult != PMD_OK)
	{
		sprintf (scLogTxt, "--> Could not update to sensor Error: %i\n", slResult);
                //printf(scLogTxt);
                console->append(scLogTxt);
		return FALSE;
	}

	/* GetSerialNumber */
	slResult = pmdSourceCommand (stCurrentSensor->HndSensor, scSerial, sizeof(scSerial), "GetSerialNumber");
	if (slResult != PMD_OK)
	{
		sprintf (scLogTxt, "--> Could not send pmdSourceCommand GetSerialNumber ERROR:%i\n", slResult);
                //printf(scLogTxt);
                console->append(scLogTxt);
	}
	else
	{
		strcpy(stCurrentSensor->scSensorSerial, scSerial);
		sprintf (scLogTxt, "--> Sensor MAC: %s\n", stCurrentSensor->scSensorSerial);
                //printf(scLogTxt);
                console->append(scLogTxt);
        }

	stCurrentSensor->usSensorOnline = 1;
	sprintf (scLogTxt, "--> Connected to sensor %s\n", stCurrentSensor->scSensorIP);
        //printf(scLogTxt);
        console->append(scLogTxt);
	return TRUE;
}

/**************************************************************************//**

Capture data from sensor.

\param stSensorConfig sensor configuration
\param pCvMatFrame	  to save data

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_Capture(struct stSensorConfig *stCurrentSensor, CvMat *pCvMatFrame, QString *console)
{
	int i,j;				/* counter values */

	int slResult;			/* keeps return values */
	int slFrameSize;		/* size of a frame */
	int slFrameNumbers;		/* number of frames */
	int slCamCount = 0;		/* counter for sensors */

	float **flDistances;	/* pointer for frame array */
	float *flMeanDistance;	/* pointer to array with single frame */

	char scLogTxt[64];		/* array for log */

	/* get amount of frames to capture and their size */
        slFrameNumbers = 10;
	slFrameSize = stCurrentSensor->usResX*stCurrentSensor->usResY;
        //printf("--> Framesize %i X %i\n", slFrameSize, slFrameNumbers);
        console->sprintf("--> Framesize %i X %i\n", slFrameSize, slFrameNumbers);
	/* allocate memory for every frame row */
	flDistances = (float **)malloc(slFrameNumbers * sizeof(float *));
	if(flDistances == NULL)
	{
		sprintf(scLogTxt, "--> No virtual memory\n");
                //printf(scLogTxt);
                console->append(scLogTxt);
                return FALSE;
	}

	/* allocate memory for every frame colum */
	for(; slCamCount < slFrameNumbers; slCamCount++)
	{
		flDistances[slCamCount] = (float *)malloc(slFrameSize * sizeof(float));
        if(flDistances[slCamCount] == NULL)
        {
        	sprintf(scLogTxt, "--> No memory for row  %d\n", slCamCount);
            //printf(scLogTxt);
            console->append(scLogTxt);
            return FALSE;
        }
	}

		/* start capturing amount of frames 'slFrameNumbers' */
		slCamCount = 0;
		for(; slCamCount<slFrameNumbers; slCamCount++)
		{
			slResult = pmdUpdate(stCurrentSensor->HndSensor);
			if (slResult != PMD_OK)
			{
			    sprintf(scLogTxt, "--> Could not update sensor ERROR: %i\n", slResult);
                            //printf(scLogTxt);
                            console->append(scLogTxt);
                            return FALSE;
			}

			slResult = pmdGetDistances(stCurrentSensor->HndSensor, flDistances[slCamCount], (slFrameSize *sizeof(float)));
			memset(&flDistances[slCamCount][48*stCurrentSensor->usResY], 0, 2*stCurrentSensor->usResY*sizeof(float));

			if (slResult != PMD_OK)
			{
			    sprintf(scLogTxt, "--> Could not retrieve distance %i ERROR: %i\n",slCamCount, slResult);
                            //printf(scLogTxt);
                            console->append(scLogTxt);
			}
		}

		SENSOR_exportCSV (stCurrentSensor, flDistances);



	flMeanDistance = (float *)malloc(slFrameSize * sizeof(float));
	memset(flMeanDistance, 0.0 , sizeof(slFrameSize * sizeof(float)));

	float *pflFrame = (float *) pCvMatFrame->data.fl;

	int slFrameNumber;
	int slElementSource      = 0;
	int slElementDestination = 0;

	for (i=0; i<stCurrentSensor->usResY; i++)
	{
		for(j=0; j<(stCurrentSensor->usResX-2); j++)
		{
			// old size : 64x50 pixel
			slElementSource  = i + (j*stCurrentSensor->usResY);


			slElementDestination = slElementSource;

			flMeanDistance[slElementSource] = 0;
			for (slFrameNumber=0; slFrameNumber<slFrameNumbers; slFrameNumber++)
			{
				flMeanDistance[slElementSource] += flDistances[slFrameNumber][slElementSource];
			}

			if (flMeanDistance[slElementSource] != 0)
				pflFrame[slElementDestination] = 1000.0 * (flMeanDistance[slElementSource] / slFrameNumbers);
			else
				pflFrame[slElementDestination] = 0;
		}
	}


	/* free empty colums first (distance) */
	for(slCamCount=0; slCamCount < 10; slCamCount++)
	{
		free(flDistances[slCamCount]);
	}

	/* free empty rows (distance) */
	free(flDistances);
	free(flMeanDistance);

	return TRUE;
}

/**************************************************************************//**

Get exposure time from sensor with index 'slExpIndex'.

\param stCurrentSensor 		sensor configuration
\param slExpIndex 			index of exposure time 0 to 2

\return exposure time or -1 on errors
******************************************************************************/
unsigned int SENSOR_GetExpTime(struct stSensorConfig *stCurrentSensor, int slExpIndex)
{
	char scLogTxt[64];		/* array for log */
	int slResult;			/* keeps return values */
	unsigned int ulExpTime;	/* keeps exposure time value */

	slResult = pmdUpdate(stCurrentSensor->HndSensor);
	if (slResult != PMD_OK)
	{
	    sprintf(scLogTxt, "--> Could not update sensor ERROR: %i\n", slResult);
            //printf(scLogTxt);
	    return -1;
	}

	slResult = pmdGetIntegrationTime (stCurrentSensor->HndSensor, &ulExpTime, slExpIndex);
	if (slResult != PMD_OK)
	{
	    sprintf(scLogTxt, "--> Could not get exposure time ERROR: %i\n", slResult);
            //printf(scLogTxt);
	    return -1;
	}
	return ulExpTime;
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
	char scLogTxt[64];		/* array for log */
	int slResult;			/* keeps return values */

	slResult = pmdUpdate(stCurrentSensor->HndSensor);
	if (slResult != PMD_OK)
	{
	    sprintf(scLogTxt, "--> Could not update sensor ERROR: %i\n", slResult);
            //printf(scLogTxt);
	    return FALSE;
	}

	slResult = pmdSetIntegrationTime (stCurrentSensor->HndSensor, slExpIndex, ulExpTime);
	if (slResult != PMD_OK)
	{
	    sprintf(scLogTxt, "--> Could not set exposure time ERROR: %i\n", slResult);
            //printf(scLogTxt);
	    return FALSE;
	}
	sprintf(scLogTxt, "--> Set exposure time %i for sensor to %i\n", slExpIndex, ulExpTime);
        //printf(scLogTxt);
	return TRUE;
}
/**************************************************************************//**

Close connection to the used sensor.

\param stCurrentSensor  sensor configuration

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_Close(struct stSensorConfig *stCurrentSensor,QString *console)
{

	int slResult;

	char scLogTxt[64];

	/* close sensor_0 */
	if(stCurrentSensor->usSensorOnline == 1)
	{
		/* SetTrigger SOFT */
		slResult = pmdSourceCommand (stCurrentSensor->HndSensor, 0, 0, "SetTrigger OFF");
		if (slResult != PMD_OK)
		{
			sprintf (scLogTxt, "--> pmdSourceCommand SetTrigger ERROR:%i\n ", slResult);
                        //printf(scLogTxt);
                        console->append(scLogTxt);
		}

                //printf ("--> Closing SENSOR %s\n", stCurrentSensor->scSensorIP);
                console->sprintf("--> Closing SENSOR %s\n", stCurrentSensor->scSensorIP);
                slResult = pmdClose (stCurrentSensor->HndSensor);
		if (slResult != PMD_OK)
		{
			sprintf (scLogTxt, "--> Could not close sensor ERROR: %i\n", slResult);
                        //printf(scLogTxt);
                        console->append(scLogTxt);
                        return FALSE;
		}
		sprintf (scLogTxt, "--> Closed sensor %s\n", stCurrentSensor->scSensorIP);
                //printf(scLogTxt);
                console->append(scLogTxt);
                //printf("done\n");
                console->append("done\n");
	}

	return TRUE;
}


/**************************************************************************//**

Export raw data to CSV.

\param stCurrentSensor 	sensor configuration
\param pflData			data pointer

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_exportCSV(struct stSensorConfig *stCurrentSensor, float **pflData)
{
	int i,j;
	char scaFilename[128];

	sprintf(scaFilename, "./data/out.csv");

	FILE *fCSV = fopen(scaFilename, "w+");
	if(fCSV==NULL)
	{
		printf("--> SENSOR_exportCSV No file found");
		return FALSE;
	}

	char cCSV[10];
	unsigned short usBytesWritten = 0;

	int slNumberPixel = stCurrentSensor->usResX * stCurrentSensor->usResY;

	for (i=0; i<10; i++)
	{
		for (j=0; j<slNumberPixel; j++)
		{
			if (j<(slNumberPixel-1))
			{
				sprintf(cCSV, "%f;", pflData[i][j]);
			}
			else
			{
				if (i<(10-1))
					sprintf(cCSV, "%f\n", pflData[i][j]);
				else
					sprintf(cCSV, "%f", pflData[i][j]);
			}

			usBytesWritten += fwrite(cCSV, sizeof(char), strlen(cCSV), fCSV);
		}
	}

	fclose(fCSV);

	return TRUE;
}


/**************************************************************************//**

Import CSV.

\param stCurrentSensor	sensor configuration
\param pflData			data pointer

\return TRUE on success FALSE on failure
******************************************************************************/
int SENSOR_importCSV(struct stSensorConfig *stCurrentSensor, float **pflData)
{
	char scaFilename[128];

	int slNumberPixel = stCurrentSensor->usResX * stCurrentSensor->usResY;

	sprintf(scaFilename, "./data/in.csv");

	FILE *fCSV = fopen(scaFilename, "r");
	if(fCSV==NULL)
	{
		printf("--> SENSOR_importCSV No file found");
		return FALSE;
	}

	fseek(fCSV, 0, SEEK_END);
	int slFilesize = ftell(fCSV);
	rewind(fCSV);

	//allocate memory for data
	char *pcaBuffer = (char *)malloc(slFilesize);
	char *pcaElement;
	char caSeperator[]=";\x0a";

	int slRowCount = 0;
	int slColCount = 0;

	while(!feof(fCSV))
	{
		fgets(pcaBuffer, slFilesize, fCSV);

		pcaElement = strtok(pcaBuffer, caSeperator);
		while(pcaElement != NULL)
		{
			pflData[slRowCount][slColCount] = (float)atof(pcaElement);

			slColCount++;
			pcaElement = strtok(NULL, caSeperator);

			if(slColCount >= slNumberPixel)
			{
				slColCount = 0;
				slRowCount++;
			}
		}
	}

	fclose(fCSV);
	free(pcaBuffer);

	return TRUE;
}

/** @} */ // end of Sensor


