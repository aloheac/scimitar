//
// Created by loheac on 11/1/19.
//

#ifndef SCIMITAR7_GROUP_H
#define SCIMITAR7_GROUP_H

#include "../parameter/Parameter.h"
#include "../engine/EngineAuxiliary.h"


/**
 * A container class for implementing the logic surrounding groups of parameters. This container is directly
 * connected with the "group" statement provided by the grammar. A set of parameters which are grouped together
 * are evaluated in "lock step" with one another, which contrasts with the behavior of the same set of ungrouped
 * parameters.
 *
 * The Group class provides methods for adding, removing, and accessing parameters as members of the group.
 */
class Group {
public:

    /**
     * Default constructor. Provides an empty group.
     */
    Group();

    /**
     * Constructor which initializes the group with a single element.
     * @param parameter Initializing parameter which will be added to the group.
     */
    Group( Parameter* parameter );

    ~Group();

    /**
     * Add a parameter to the group.
     * @param parameter Parameter to add.
     */
    void add_parameter( Parameter* parameter );

    /**
     * Delete a parameter from the group which matches the provided identifier.
     * @param identifier Identifier of the parameter to remove.
     */
    void delete_parameter( std::string identifier );

    /**
     * Check whether a parameter matching an identifier exists in the group.
     * @param identifier Identifier to check for a match.
     * @return True if a match is found, false otherwise.
     */
    bool has_parameter( std::string identifier );

    /**
     * Obtains the pointer to the parameter matching the provided identifier.
     * @param identifier Identifier of the parameter to obtain.
     * @return Pointer to the matching Parameter object.
     */
    Parameter* get_parameter( std::string identifier );

    /**
     * Validates the current state of the group. If any configuration would not compile, an exception is thrown.
     */
    void validate();

    /**
     * Gets the next set of parameter values provided by the generator. The number of elements in the generator is
     * equal to the parameter length.
     * @return A vector containing one ValuePair object for each parameter in the group.
     */
    std::vector<ValuePair> get_next();

    /**
     * Gets the number of parameters present in this group.
     * @return Number of parameters in this group.
     */
    int length();

    /**
     * Gets the number of values provided by each parameter in this group. This length must be equal across all
     * parameters by definition.
     * @return The length of each parameter.
     */
    int parameter_length();

    /**
     * Merges (by copying) the elements of the passed group with this instance.
     * @param group The group whose elements to copy into this group.
     */
    void merge( Group group );

    /**
     * Splits the parameters into new groups, where each parameter is placed into its own group.
     * @return A vector of the new Group instances.
     */
    std::vector<Group> split();

    /**
     * Generates a pretty-printed representation of this instance.
     * @return A string representation of this instance.
     */
    std::string to_string();

    /**
     * Resets the state of the generator to the first element.
     */
    void reset();

    /**
     * Indicates whether the the generator has been exhausted.
     * @return True if the generator is exhausted, false otherwise.
     */
    bool is_empty();

    /**
     * Marks this parameter as to be hidden when evaluated by the Engine.
     * @param identifier The parameter to be marked as hidden.
     */
    void hide_parameter( std::string identifier );

    /**
     * Returns whether a parameter of a given identifier has been hidden.
     * @param identifier The identifier to check.
     * @return True if the matching identifier has been hidden, false otherwise.
     */
    bool is_hidden( std::string identifier );

private:

    /* The container of Parameter objects this group holds. */
    std::vector<Parameter*> parameters;

    /* The list of hidden identifiers within this group. */
    std::vector<std::string> hidden_identifiers;

    /* Number of parameters contained within this group. */
    int len;

    /* Length of each parameter which is a member of this group. The length of each parameter should be the same. */
    int parameter_len;

    /* Index counter for the generator. */
    int next_index;

};

#endif //SCIMITAR7_GROUP_H
