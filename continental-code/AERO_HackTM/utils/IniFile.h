#ifndef HELPERS_INIFILE_H
#define HELPERS_INIFILE_H

#include <string>
#include <vector>
#include <list>

namespace helpers {

class IniFilePrivate;

/**
 * Class to read and write INI files.
 * - sections start with [section]
 * - key/value pairs are of the syntax key = value (whitespaces irrelevant)
 * - comments start with ';' and can also appear behind a key/value pair
 *
 * Usage:
 * \code
 * IniFile file;
 * file.loadFile("C:\\full\\path\\file.ini");
 *
 * // read a value, if the entry does not exist, the default value is used
 * int         a = file.read("General", "key1", 42);
 * std::string b = file.read("General", "key2", "default");
 * double      c = file.read("General", "key3", 1.0);
 * bool        d = file.read("General", "key4", false);
 *
 * // set new values
 * file.write("General", "key5", 42);
 * file.write("General", "key6", std::string("default"));
 * file.write("General", "key7", 1.0);
 * file.write("General", "key8", false);
 *
 * // save to another file
 * file.saveFile("C:\\full\\path\\new-file.ini");
 * // now new-file.ini contains the section [General] and the key/value
 * // pairs key1...key8
 * \endcode
 */
class IniFile
{
public:
  IniFile();
  ~IniFile();

  bool loadFile(const std::string& fullPathWithFilename);
  bool saveFile(const std::string& fullPathWithFilename);

  std::string read(const std::string& section, const std::string& key, const std::string& defaultValue) const;
  int read(const std::string& section, const std::string& key, int defaultValue) const;
  double read(const std::string& section, const std::string& key, double defaultValue) const;
  float read(const std::string& section, const std::string& key, float defaultValue) const;
  bool read(const std::string& section, const std::string& key,  bool defaultValue) const;

  void write(const std::string& section, const std::string& key, const std::string& value);
  void write(const std::string& section, const std::string& key, int value);
  void write(const std::string& section, const std::string& key, double value);
  void write(const std::string& section, const std::string& key, float value);
  void write(const std::string& section, const std::string& key,  bool value);

  void sections(std::vector<std::string>& destSections) const;
  bool sectionAvailable(const std::string section) const;
  void keys(const std::string& section, std::vector<std::string>& destKeys) const;
  bool keyAvailable(const std::string section, const std::string key) const;

  void debug();

  IniFile & operator=( const IniFile &){}

protected:
  void readEntry(const std::string& section, const std::string& line);
  bool readSection(std::string& section);

private:
  /* avoid copy construction */
  IniFile(const IniFile& rhs) : d(0)
  {
    rhs;
  }
  friend class IniFilePrivate;
  IniFilePrivate* const d;
};


class ParameterReader;

class ParameterBase
{
public:
  ParameterBase(ParameterReader &r, const char* section, const char* parameterName);
  virtual ~ParameterBase();

// remove Warning L4
#pragma warning(push)
#pragma warning(disable: 4100)
  virtual void setValue(IniFile& inifile) {};
#pragma warning(pop)

  const std::string section;
  const std::string parameterName;
  ParameterBase & operator=( const ParameterBase &){}
protected:
  ParameterReader* reader;
};


class ParameterReader
{
public:
  ParameterReader(const char* iinifile);
  virtual ~ ParameterReader(){};
  void readParams();
  void registerParameter(ParameterBase* p);
  void unRegisterParameter(ParameterBase* p);
  IniFile& getIniFile() {return file;};
  ParameterReader & operator=( const ParameterReader &){}

protected:
  IniFile file;
  std::string inifile;
  std::list<ParameterBase*> parameters;
};

template <typename ParameterType>
class Parameter : ParameterBase
{
  public:
  Parameter(ParameterReader &r, const char* section, const char* parameterName, ParameterType defaultValue)
    : ParameterBase(r, section, parameterName)
      {
        value=defaultValue;
        setValue(r.getIniFile());
      };
  virtual ~Parameter() {};
  operator ParameterType() const{return value;}
  void setValue(IniFile& inifile)
  {
    value=inifile.read(section,parameterName,value);
  };
  protected:
    ParameterType value;
};


}

#endif // HELPERS_INIFILE_H
