#ifndef _VEHICLECONFIG_H_
#define _VEHICLECONFIG_H_

#include"IniFile.h"
#include<string>


class VehicleConfig
{
public:
	VehicleConfig();
    VehicleConfig(std::string VehicleCfgIniFileName);
	virtual ~VehicleConfig();

	//gives back the path to the vehicle ini file, so that other programs can read it manually
	const std::string & getConfigFile();  

	//reads the vehicle name
	std::string getVehicleName();

	//reads the info string of the config file
	std::string VehicleConfig::getInfoString();

	//reads the sensor pose from the vehicle config file, returns false in case the sensor is unknown
	bool sensorPose(std::string sensorName, float &x_m, float &y_m, float &angle_rad) const;
    bool sensorPose(std::string sensorName, double &x_m, double &y_m, double &angle_rad) const;
	
	//reads a float value from the config file
	bool getValue(const std::string & sensorName, const std::string & key, float &value) const;
	//reads an int value from the config file
    bool getValue(const std::string & sensorName, const std::string & key, int &value) const;

    // returns status if file could be loaded
    bool wasLoaded()
    {
      return m_loaded;
    }

  VehicleConfig & operator=(const VehicleConfig &){}
protected:
	std::string m_filename;
	helpers::IniFile m_file;
private:
    bool m_loaded;

};

#endif //_VEHICLECONFIG_H_
