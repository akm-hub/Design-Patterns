/**
  * @purpose Demonstrate  traditional singleton design pattern using pointers
  *
  * @author  Ashish
  * @license MIT license
  * @version 1.0, Doxygen compatible comments
  */
#include<iostream>
#include<string>
using namespace std;

/** \brief A simple Logger class, to read and write to log files
  */
class Logger{
 private:
    static Logger *log_instance;  /// have a static pointer to the Class
    string log_data_;

 public:
/** \brief  a static function that allocates object to the static pointer
  *          lazy init
  * \param  void
  * \return Logger* - alloted Logger class instance
  */
    static Logger* get_instance(void) {
        if (log_instance == NULL)
            log_instance = new Logger;
        return log_instance;
    }

/** \brief  a member function that writes data onto a string variable
  *          Instead of a string in this example, it could be a file, network, etc.
  * \param  given_string - the data to be logged
  * \return void
  */
    void write_to_log(const string& given_string) {
        log_data_ += given_string;
    }

/** \brief  a member function that reads data from log storage
  *          Instead of a string in this example, it could be a file, network, etc.
  * \param  void
  * \return string - the logged data
  */    
    string read_from_log() {
        return log_data_;
    }

 protected:
    Logger() {
    }
};

Logger* Logger::log_instance = NULL;  /// init the static member

int main() {
    Logger *log = Logger::get_instance();
    log->write_to_log("hello");

    Logger *log2 = Logger::get_instance();
    log2->write_to_log(", world!");

    cout << log->read_from_log() << endl;
    return 0;
}
