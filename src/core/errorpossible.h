//
// Created by Ion Agorria on 22/04/18
//
#ifndef OPENE2140_ERRORPOSSIBLE_H
#define OPENE2140_ERRORPOSSIBLE_H

#include <string>

/**
 * Classes that can produce an error
 */
class IErrorPossible {
protected:
    /**
     * Last occurred error
     */
    std::string error;
public:
    /**
     * IPalette destructor
     */
    virtual ~IErrorPossible() = default;

    /**
     * @return the last occurred error and clears it
     */
    std::string getError();
};

#endif //OPENE2140_ERRORPOSSIBLE_H
