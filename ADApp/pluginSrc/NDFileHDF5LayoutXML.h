/*
 * layoutxml.h
 *
 *  Created on: 26 Jan 2012
 *      Author: up45
 */

#ifndef LAYOUTXML_H_
#define LAYOUTXML_H_

#include <libxml/xmlreader.h>
#include <string>
#include <map>
#ifdef LOG4CXX
#include <log4cxx/logger.h>
#else

// std::cout logging if log4cxx is not defined
// define HDF5_LOGGING 1 to print log messages
//#define HDF5_LOGGING 1

namespace log4cxx
{

  class Logger
  {
    public:
      static Logger* getLogger(const std::string& name){ return new Logger(); }
  };
  typedef Logger* LoggerPtr;

} // namespace log4cxx

#ifdef HDF5_LOGGING
  #define LOG4CXX_ERROR(LOG, msg) std::cout << msg << std::endl
  #define LOG4CXX_INFO(LOG, msg) std::cout << msg << std::endl
  #define LOG4CXX_DEBUG(LOG, msg) std::cout << msg << std::endl
  #define LOG4CXX_WARN(LOG, msg) std::cout << msg << std::endl
#else
  #define LOG4CXX_ERROR(LOG, msg)
  #define LOG4CXX_INFO(LOG, msg)
  #define LOG4CXX_DEBUG(LOG, msg)
  #define LOG4CXX_WARN(LOG, msg)
#endif
#endif

namespace hdf5 {

// forward declarations
class HdfGroup;
class HdfRoot;
class HdfDataSource;
class HdfAttribute;
class HdfElement;

int main_xml(const char *fname);


class LayoutXML {
public:

  static const std::string ATTR_ELEMENT_NAME;
  static const std::string ATTR_GROUP;
  static const std::string ATTR_DATASET;
  static const std::string ATTR_ATTRIBUTE;
  static const std::string ATTR_GLOBAL;

  static const std::string ATTR_SOURCE;
  static const std::string ATTR_SRC_DETECTOR;
  static const std::string ATTR_SRC_DET_DEFAULT;
  static const std::string ATTR_SRC_NDATTR;
  static const std::string ATTR_SRC_CONST;
  static const std::string ATTR_SRC_CONST_VALUE;
  static const std::string ATTR_SRC_CONST_TYPE;
  static const std::string ATTR_GRP_NDATTR_DEFAULT;
  static const std::string ATTR_SRC_WHEN;
  static const std::string ATTR_GLOBAL_NAME;
  static const std::string ATTR_GLOBAL_VALUE;


  static const std::string DEFAULT_LAYOUT;

    LayoutXML();
    ~LayoutXML();

//    int load_xml(std::string& filename){ return this->load_xml(filename.c_str()); };
    int load_xml();
    int load_xml(const std::string& filename);
    int unload_xml();

    HdfRoot* get_hdftree();
    std::string get_global(const std::string& name);

private:
    int process_node();

    int process_dset_xml_attribute(HdfDataSource& out);
    int process_attribute_xml_attribute(HdfAttribute& out);

    int new_group();
    int new_dataset();
    int new_attribute();
    int new_global();

    log4cxx::LoggerPtr log;
    HdfRoot* ptr_tree;
    HdfElement *ptr_curr_element;
    xmlTextReaderPtr xmlreader;
    std::map<std::string, std::string> globals;

};

} // hdf5

#endif /* LAYOUTXML_H_ */
