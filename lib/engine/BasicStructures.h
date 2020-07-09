//
// Created by loheac on 12/21/19.
//

#ifndef SCIMITAR7_BASICSTRUCTURES_H
#define SCIMITAR7_BASICSTRUCTURES_H

#include <string>
#include <vector>

class EngineException : public std::exception {
public:

    EngineException( std::string msg );

    virtual const char* what() const throw();

private:

    std::string msg;

};


struct OptionPair {

    OptionPair();

    OptionPair( std::string option, std::string value );

    std::string option;

    std::string value;

};


class OptionSet {

public:

    OptionSet();

    void add_option( OptionPair option );

    bool has_option( std::string option );

    std::string get_option( std::string option );

    OptionPair at( unsigned long i );

    unsigned long size();

private:

    std::vector<OptionPair> options;

};

#endif //SCIMITAR7_BASICSTRUCTURES_H
