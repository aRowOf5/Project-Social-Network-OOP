#pragma once
#include "User.h"

/**
 * @brief The Moderator class inherits the User class and adds specific functionality for moderators.
 */
class Moderator : public User {
public:
    /**
     * @brief Constructor that creates a new Moderator object with the specified parameters.
     *
     * @param firstName Moderator's first name.
     * @param lastName Moderator's last name.
     * @param nickname Moderator's nickname.
     * @param password Moderator's password.
     */
    Moderator(const std::string& firstName, const std::string& lastName, const std::string& nickname, const std::string& password);

    /**
     * @brief Default constructor.
     */
    Moderator();

    /**
     * @brief Clones the Moderator object.
     *
     * @return Pointer to the new User object (in this case Moderator).
     */
    virtual User* clone() const override;

    /**
     * @brief Saves moderator data to a file.
     *
     * @param of The output file stream.
     */
    virtual void writeToFile(std::ofstream& of) const override;

    /**
     * @brief Reads moderator data from a file.
     *
     * @param iff The input file stream.
     */
    virtual void readFromFile(std::ifstream& iff) override;
};
