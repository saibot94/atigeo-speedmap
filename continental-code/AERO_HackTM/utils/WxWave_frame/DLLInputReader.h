#ifndef _DLLINPUTREADER_H_
#define _DLLINPUTREADER_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


class DLLInputReader
{
public:

    /// Construnctor of the class
    ///
    /// <param name='parametersString'> input string containing user defined parameters to a DLL </param> 
    /// <param name='separatorParameters'> string with characters to be user to split the parameters from each other </param> 
    /// <param name='separatorValues'> string with characters to be user to split the values from parameter's name </param> 
    ///
    /// e.g. ParameterName1=Value1;ParameterName2=Value2;ParameterName3=Value3;  separatorParameters=";" and separatorValues="=";
    ///
    DLLInputReader(string parametersString, string separatorParameters, string separatorValues);

    /// Default contructor
    ///
    DLLInputReader(void);

    /// Default destructor
    ///
    ~DLLInputReader(void);

    /// Finds and returns a string value to a parameter by name
    ///
    /// <param name='parameterName'> parameters'name that should be found </param> 
    /// <returns> the parameter's value if parameter found, else it returns the standart value </returns>
    ///
    string getParamterValueString(string parameterName, string);

    /// Finds and returns a int value to a parameter by name
    ///
    /// <param name='parameterName'> parameters'name that should be found </param> 
    /// <returns> the parameter's value if parameter found, else it returns the standart value </returns>
    ///
    int getParamterValueInt(string parameterName, int);

    /// Finds and returns a float value to a parameter by name
    ///
    /// <param name='parameterName'> parameters'name that should be found </param> 
    /// <returns> the parameter's value if parameter found, else it returns the standart value </returns>
    ///
    float getParamterValueFloat(string parameterName, float);

    /// Finds and returns a double value to a parameter by name
    ///
    /// <param name='parameterName'> parameters'name that should be found </param> 
    /// <returns> the parameter's value if parameter found, else it returns the standart value </returns>
    ///
    double getParamterValueDouble(string parameterName, double);

    /// Finds and returns a long value to a parameter by name
    /// !!! The function can not read characters as long values e.g. "0xff" -> the standart value will be returned
    ///
    /// <param name='parameterName'> parameters'name that should be found </param>
    /// <returns> the parameter's value if parameter found, else it returns the standart value </returns>
    ///
    long getParamterValueLong(string parameterName, long);

private:
    map<string, string> p_parameters;
    string p_separatorParameters;
    string p_separatorValues;

protected:

    /// Reads the input string and saves the parameters and values as pairs
    ///
    /// <param name='parametersString'> input string containing user defined parameters to a DLL </param>
    ///
    void readParametersString(string parametersString);

    /// Splits a given string into a vector of words by a given string of separator characters
    ///
    /// <param name='text'> string to be splited </param>
    /// <param name='separators'> characters to be used as split point </param>
    /// <param name='text'> vector to return the splited string </param>
    ///
    void split(string& text, string& separators, vector<string>& words);
};

#endif /* _DLLINPUTREADER_H_ */
