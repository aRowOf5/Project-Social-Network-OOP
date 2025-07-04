#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

/**
 * @enum Permission
 * @brief Defines different levels of user permissions.
 */
enum class Permission {
    NaN = -1, /**< Invalid or unused permission. */
    USER,     /**< Regular user. */
    MOD       /**< Moderator. */
};

/**
 * @class User
 * @brief Represents a user with various attributes such as name, nickname, password, points, and role.
 */
class User {
protected:
    std::string firstName; /**< User first name. */
    std::string lastName;  /**< User last name. */
    std::string nickname;  /**< User nickname. */
    std::string password;  /**< User password. */
    unsigned int id;       /**< User ID. */
    int points;            /**< The points associated with the user. */
    Permission role;       /**< The role (permission) of the user. */

    static unsigned int ID; /**< Static variable to generate unique IDs for users. */

public:
    /**
     * @brief Constructor for a new User object with the given details.
     *
     * @param firstName User first name.
     * @param lastName User last name.
     * @param nickname User nickname.
     * @param password User password.
     */
    User(const std::string& firstName, const std::string& lastName, const std::string& nickname, const std::string& password);

    /**
     * @brief Default constructor for the User class.
     */
    User() = default;

    /**
     * @brief Default destructor for the User class.
     */
    virtual ~User() = default;

    /**
     * @brief Sets the user first name.
     *
     * @param firstName The new first name.
     */
    void setFirstName(const std::string& firstName);

    /**
     * @brief Sets the user last name.
     *
     * @param lastName The new last name.
     */
    void setLastName(const std::string& lastName);

    /**
     * @brief Sets the user nickname.
     *
     * @param nickname The new nickname.
     */
    void setNickname(const std::string& nickname);

    /**
     * @brief Sets the user password.
     *
     * @param password The new password.
     */
    void setPassword(const std::string& password);

    /**
     * @brief Sets the user permission role.
     *
     * @param newRole The new permission role.
     */
    void setPermissionRole(Permission newRole);

    /**
     * @brief Changes the user's points.
     *
     * @param changeOfPoints The amount to change the points.
     */
    void changePoints(const int changeOfPoints);

    /**
     * @brief Returns the user first name.
     *
     * @return First name.
     */
    const std::string getFirstName() const;

    /**
     * @brief Returns the user last name.
     *
     * @return Last name.
     */
    const std::string getLastName() const;

    /**
     * @brief Returns the user nickname.
     *
     * @return Nickname.
     */
    const std::string getNickname() const;

    /**
     * @brief Returns the user password.
     *
     * @return Password.
     */
    const std::string getPassword() const;

    /**
     * @brief Returns the user permission role.
     *
     * @return Permission role.
     */
    const Permission getPermissionRole() const;

    /**
     * @brief Returns the user's points.
     *
     * @return Points.
     */
    const unsigned int getPoints() const;

    /**
     * @brief Returns the unique user ID.
     *
     * @return Unique ID.
     */
    const unsigned int getId() const;

    /**
     * @brief Creates a clone of the user.
     *
     * @return Pointer to the cloned User object.
     */
    virtual User* clone() const;

    /**
     * @brief Saves user data to a file.
     *
     * @param of Output file stream.
     */
    virtual void writeToFile(std::ofstream& of) const;

    /**
     * @brief Reads user data from a file.
     *
     * @param iff Input file stream.
     */
    virtual void readFromFile(std::ifstream& iff);
};
