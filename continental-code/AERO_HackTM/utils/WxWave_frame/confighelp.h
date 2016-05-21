#ifndef confighelp_h_included
#define confighelp_h_included

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


/////////////////
/* colour type */
/////////////////

typedef struct colour_t_tag
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;

  colour_t_tag()
  {
    red   = 255;
    green = 255;
    blue  = 255;
    alpha = 255;
  };
} colour_t;


////////////////
/* list types */
////////////////

typedef std::list<char>   list_char_t;
typedef std::list<short>  list_short_t;
typedef std::list<int>    list_int_t;
typedef std::list<float>  list_float_t;
typedef std::list<double> list_double_t;
typedef std::list<std::string> list_string_t;


////////////////
/* size types */
////////////////

typedef struct size_char_t_tag
{
  char width;
  char height;

  size_char_t_tag()
  {
    width  = 0;
    height = 0;
  };
} size_char_t;

typedef struct size_short_t_tag
{
  short width;
  short height;

  size_short_t_tag()
  {
    width  = 0;
    height = 0;
  }
} size_short_t;

typedef struct size_int_t_tag
{
  int width;
  int height;

  size_int_t_tag()
  {
    width  = 0;
    height = 0;
  };
} size_int_t;

typedef struct size_float_t_tag
{
  float width;
  float height;

  size_float_t_tag()
  {
    width  = 0.0;
    height = 0.0;
  }
} size_float_t;

typedef struct size_double_t_tag
{
  double width;
  double height;

  size_double_t_tag()
  {
    width  = 0.0;
    height = 0.0;
  };
} size_double_t;


/////////////////
/* point types */
/////////////////

typedef struct point_char_t_tag
{
  char x;
  char y;

  point_char_t_tag()
  {
    x = 0;
    y = 0;
  };
} point_char_t;

typedef struct point_short_t_tag
{
  short x;
  short y;

  point_short_t_tag()
  {
    x = 0;
    y = 0;
  };
} point_short_t;

typedef struct point_int_t_tag
{
  int x;
  int y;

  point_int_t_tag()
  {
    x = 0;
    y = 0;
  };
} point_int_t;

typedef struct point_float_t_tag
{
  float x;
  float y;

  point_float_t_tag()
  {
    x = 0.0;
    y = 0.0;
  };
} point_float_t;

typedef struct point_double_t_tag
{
  double x;
  double y;

  point_double_t_tag()
  {
    x = 0.0;
    y = 0.0;
  };
} point_double_t;


////////////////
/* rect types */
////////////////

typedef struct rect_char_t_tag
{
  char x;
  char y;
  char width;
  char height;

  rect_char_t_tag()
  {
    x = 0;
    y = 0;
    width  = 0;
    height = 0;
  };
} rect_char_t;

typedef struct rect_short_t_tag
{
  short x;
  short y;
  short width;
  short height;

  rect_short_t_tag()
  {
    x = 0;
    y = 0;
    width  = 0;
    height = 0;
  };
} rect_short_t;

typedef struct rect_int_t_tag
{
  int x;
  int y;
  int width;
  int height;

  rect_int_t_tag()
  {
    x = 0;
    y = 0;
    width  = 0;
    height = 0;
  };
} rect_int_t;

typedef struct rect_float_t_tag
{
  float x;
  float y;
  float width;
  float height;

  rect_float_t_tag()
  {
    x = 0.0;
    y = 0.0;
    width  = 0.0;
    height = 0.0;
  };
} rect_float_t;

typedef struct rect_double_t_tag
{
  double x;
  double y;
  double width;
  double height;

  rect_double_t_tag()
  {
    x = 0.0;
    y = 0.0;
    width  = 0.0;
    height = 0.0;
  };
} rect_double_t;


///////////////
/* map types */
///////////////

typedef std::map<std::string, char>   map_string_char_t;
typedef std::map<std::string, short>  map_string_short_t;
typedef std::map<std::string, int>    map_string_int_t;
typedef std::map<std::string, float>  map_string_float_t;
typedef std::map<std::string, double> map_string_double_t;
typedef std::map<std::string, std::string> map_string_string_t;


//////////////////////////////////////////////////////////
//           config helper class
//////////////////////////////////////////////////////////
/**
* @class   CDllConfig
* 
* Config base class
*
* This class implements a simplified access to the dll rtx "Parameters" section.
*/
class CDllConfig
{
  typedef std::map<std::string, std::string> CfgMapT;

public:
  CDllConfig(const CfgMapT& cfg, std::string path = "", std::string prefix = "xml:/") :
      cfg_(cfg),
        cur_path_(path),
        cur_pref_(prefix)
      {
      };
      virtual ~CDllConfig(){};

      ///////////////////////////////////////////////
      // config interface functions
      ///////////////////////////////////////////////
      /**
      * Set the current configuratuion path.
      *
      * Set the internal configuration path for relative key value access.
      *
      * @param   path   The configuration path.
      *
      * @return         0.
      */
      int SetPath(const std::string& path)
      {
        cur_path_ = path;
        return(0);
      }

      /**
      * Get the current configuratuion path.
      *
      * Retrieves the internal configuration path.
      *
      * @return         The configuration path.
      */
      std::string GetPath()
      {
        return(cur_path_);
      }

      /**
      * Get the value for a absolute path.
      *
      * Retrieve a configuration value using full path as parameter.
      *
      * @param   path    The full configuration path.
      * @param   defval  The default value in case of path does not exists.
      *
      * @return         The value or empty string if not found.
      */
      std::string GetFull(const std::string& path, const std::string defval = "")
      {
        if(path.empty()) return(defval);
        CfgMapT::iterator iter = cfg_.find(cur_pref_ + path);
        if(iter == cfg_.end()) return(defval);
        return(iter->second);
      }

      /**
      * Get the value for a relative path.
      *
      * Retrieve a configuration value using a path relative to current path.
      *
      * @param   path    The relative configuration path.
      * @param   defval  The default value in case of path does not exists.
      *
      * @return         The value or default string if not found.
      */
      std::string Get(const std::string& path, const std::string defval = "")
      {
        if(path.empty())      return(defval);
        if(cur_path_.empty()) return(GetFull(path, defval));
        if(path[0] == '/')    return(GetFull(cur_path_       + path, defval));
        else                  return(GetFull(cur_path_ + '/' + path, defval));
      }

      class BadConversion : public std::runtime_error {
      public:
        BadConversion(const std::string& s)
          : std::runtime_error(s)
        {}
      };

      static list_string_t Tokenize(const std::string& str,const std::string& delimiters)
      {
        list_string_t tokens;
        std::string::size_type delimPos = 0, tokenPos = 0, pos = 0;

        if(str.length()<1)  return tokens;
        for(;;)
        {
          delimPos = str.find_first_of(delimiters, pos);
          tokenPos = str.find_first_not_of(delimiters, pos);

          if(std::string::npos != delimPos)
          {
            if(std::string::npos != tokenPos)
            {
              if(tokenPos<delimPos)
              {
                tokens.push_back(str.substr(pos,delimPos-pos));
              }else
              {
                tokens.push_back("");
              }
            }
            else
            {
              tokens.push_back("");
            }
            pos = delimPos+1;
          } 
          else 
          {
            if(std::string::npos != tokenPos)
            {
              tokens.push_back(str.substr(pos));
            } 
            else 
            {
              tokens.push_back("");
            }
            break;
          }
        }
        return tokens;
      }

      static bool AsBool(std::string s)
      {
        if(s.empty()) return(false);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return(s=="true");
      }

      /*static char AsChar(std::string s)
      {
      if(s.empty()) return(false);
      std::istringstream i(s);
      char x;
      if (!(i >> x))
      throw BadConversion("CDllConfig::AsChar(\"" + s + "\")");
      return x;
      }*/

      static char AsChar(std::string s)
      {
        int i; 
        char x;
        i = AsInt(s);
        if ((i>255)||(i<0))
          throw BadConversion("CDllConfig::AsChar(\"" + s + "\")");
        else
          x = char(i);
        return x;
      }

      static short AsShort(std::string s)
      {
        if(s.empty()) return(false);
        std::istringstream i(s);
        short x;
        if (!(i >> x))
          throw BadConversion("CDllConfig::AsShort(\"" + s + "\")");
        return x;
      }

      static int AsInt(std::string s)
      {
        if(s.empty()) return(false);
        std::istringstream i(s);
        int x;
        if (!(i >> x))
          throw BadConversion("CDllConfig::AsInt(\"" + s + "\")");
        return x;
      }

      static float AsFloat(std::string s)
      {
        if(s.empty()) return(false);
        std::istringstream i(s);
        float x;
        if (!(i >> x))
          throw BadConversion("CDllConfig::AsFloat(\"" + s + "\")");
        return x;
      }

      static double AsDouble(std::string s)
      {
        if(s.empty()) return(false);
        std::istringstream i(s);
        double x;
        if (!(i >> x))
          throw BadConversion("CDllConfig::AsDouble(\"" + s + "\")");
        return x;
      }

      ////////////////////////
      //       COLOUR       //
      ////////////////////////

      static colour_t AsColour(std::string s)
      {
        colour_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.red = (unsigned char)AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.green = (unsigned char)AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.blue = (unsigned char)AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.alpha = (unsigned char)AsChar(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      ////////////////////////
      //        LIST        //
      ////////////////////////

      static list_char_t AsListChar(std::string s)
      {
        list_char_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          char value = AsChar(*list_value_iter);
          output_values.push_back(value);
        }

        return output_values;
      }

      static list_short_t AsListShort(std::string s)
      {
        list_short_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          short value = AsShort(*list_value_iter);
          output_values.push_back(value);
        }

        return output_values;
      }

      static list_int_t AsListInt(std::string s)
      {
        list_int_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          int value = AsInt(*list_value_iter);
          output_values.push_back(value);
        }

        return output_values;
      }

      static list_float_t AsListFloat(std::string s)
      {
        list_float_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          float value = AsFloat(*list_value_iter);
          output_values.push_back(value);
        }

        return output_values;
      }

      static list_double_t AsListDouble(std::string s)
      {
        list_double_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          double value = AsDouble(*list_value_iter);
          output_values.push_back(value);
        }

        return output_values;
      }

      static list_string_t AsListString(std::string s)
      {
        list_string_t output_values;
        if(s.empty()) return(output_values);
        output_values = Tokenize(s, ";");

        return output_values;
      }

      ////////////////////////
      //        SIZE        //
      ////////////////////////

      static size_char_t AsSizeChar(std::string s)
      {
        size_char_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.width = AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsChar(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static size_short_t AsSizeShort(std::string s)
      {
        size_short_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.width = AsShort(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsShort(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static size_int_t AsSizeInt(std::string s)
      {
        size_int_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.width = AsInt(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsInt(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static size_float_t AsSizeFloat(std::string s)
      {
        size_float_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.width = AsFloat(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsFloat(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static size_double_t AsSizeDouble(std::string s)
      {
        size_double_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.width = AsDouble(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsDouble(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      ////////////////////////
      //        POINT       //
      ////////////////////////

      static point_char_t AsPointChar(std::string s)
      {
        point_char_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.x = AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsChar(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static point_short_t AsPointShort(std::string s)
      {
        point_short_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.x = AsShort(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsShort(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static point_int_t AsPointInt(std::string s)
      {
        point_int_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.x = AsInt(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsInt(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static point_float_t AsPointFloat(std::string s)
      {
        point_float_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.x = AsFloat(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsFloat(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static point_double_t AsPointDouble(std::string s)
      {
        point_double_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 2) return output_values;

        output_values.x = AsDouble(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsDouble(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      ////////////////////////
      //        RECT        //
      ////////////////////////

      static rect_char_t AsRectChar(std::string s)
      {
        rect_char_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.x = AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.width = AsChar(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsChar(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static rect_short_t AsRectShort(std::string s)
      {
        rect_short_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.x = AsShort(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsShort(*(token_values.begin()));
        token_values.pop_front();
        output_values.width = AsShort(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsShort(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static rect_int_t AsRectInt(std::string s)
      {
        rect_int_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.x = AsInt(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsInt(*(token_values.begin()));
        token_values.pop_front();
        output_values.width = AsInt(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsInt(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static rect_float_t AsRectFloat(std::string s)
      {
        rect_float_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.x = AsFloat(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsFloat(*(token_values.begin()));
        token_values.pop_front();
        output_values.width = AsFloat(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsFloat(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      static rect_double_t AsRectDouble(std::string s)
      {
        rect_double_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");
        if(token_values.size() < 4) return output_values;

        output_values.x = AsDouble(*(token_values.begin()));
        token_values.pop_front();
        output_values.y = AsDouble(*(token_values.begin()));
        token_values.pop_front();
        output_values.width = AsDouble(*(token_values.begin()));
        token_values.pop_front();
        output_values.height = AsDouble(*(token_values.begin()));
        token_values.pop_front();

        return output_values;
      }

      ////////////////////////
      //        MAP         //
      ////////////////////////

      static map_string_char_t AsMapStringChar(std::string s)
      {
        map_string_char_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          char value = AsChar(*(token_pair_values.begin()));
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }

      static map_string_short_t AsMapStringShort(std::string s)
      {
        map_string_short_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          short value = AsShort(*(token_pair_values.begin()));
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }

      static map_string_int_t AsMapStringInt(std::string s)
      {
        map_string_int_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          int value = AsInt(*(token_pair_values.begin()));
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }

      static map_string_float_t AsMapStringFloat(std::string s)
      {
        map_string_float_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          float value = AsFloat(*(token_pair_values.begin()));
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }

      static map_string_double_t AsMapStringDouble(std::string s)
      {
        map_string_double_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          double value = AsDouble(*(token_pair_values.begin()));
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }

      static map_string_string_t AsMapStringString(std::string s)
      {
        map_string_string_t output_values;
        if(s.empty()) return(output_values);
        list_string_t token_values = Tokenize(s, ";");

        for(list_string_t::iterator list_value_iter = token_values.begin();
          list_value_iter != token_values.end();
          list_value_iter++)
        {
          list_string_t token_pair_values = Tokenize(*list_value_iter, ":");
          if(token_pair_values.size() != 2)
            continue;

          std::string key = *(token_pair_values.begin());
          token_pair_values.pop_front();
          std::string value = *(token_pair_values.begin());
          token_pair_values.pop_front();

          if(key != "")
            output_values.insert(std::make_pair(key, value));
        }

        return output_values;
      }


private:
  CfgMapT     cfg_;
  std::string cur_path_;
  std::string cur_pref_;
};

#endif /* confighelp_h_included */
