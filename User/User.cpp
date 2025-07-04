#include "User.h"

/**
 * @brief Initialization of the static variable ID.
 */
unsigned int User::ID = 0;

/**
 * @brief Constructor for a new User object with the given details.
 *
 * @param firstName User first name.
 * @param lastName User last name.
 * @param nickname User nickname.
 * @param password User password.
 */
User::User(const std::string& firstName, const std::string& lastName, const std::string& nickname, const std::string& password) {
	setFirstName(firstName);
	setLastName(lastName);
	setNickname(nickname);
	setPassword(password);
	setPermissionRole(Permission::USER);
	points = 0;
	id = ID++;
}

/**
 * @brief Sets the user first name.
 *
 * @param firstName The new first name.
 */
void User::setFirstName(const std::string& firstName) {
	this->firstName = firstName;
}

/**
 * @brief Sets the user last name.
 *
 * @param lastName The new last name.
 */
void User::setLastName(const std::string& lastName) {
	this->lastName = lastName;
}

/**
 * @brief Sets the user nickname.
 *
 * @param nickname The new nickname.
 */
void User::setNickname(const std::string& nickname) {
	this->nickname = nickname;
}

/**
 * @brief Sets the user password.
 *
 * @param password The new password.
 */
void User::setPassword(const std::string& password) {
	this->password = password;
}

/**
 * @brief Sets the user permission role.
 *
 * @param newRole The new permission role.
 */
void User::setPermissionRole(Permission newRole) {
	role = newRole;
}

/**
 * @brief Changes the user's points.
 *
 * @param changeOfPoints The amount to change the points.
 */
void User::changePoints(const int changeOfPoints) {
	points += changeOfPoints;
}

/**
 * @brief Returns the user first name.
 *
 * @return First name.
 */
const std::string User::getFirstName() const {
	return firstName;
}

/**
 * @brief Returns the user last name.
 *
 * @return Last name.
 */
const std::string User::getLastName() const {
	return lastName;
}

/**
 * @brief Returns the user nickname.
 *
 * @return Nickname.
 */
const std::string User::getNickname() const {
	return nickname;
}

/**
 * @brief Returns the user password.
 *
 * @return Password.
 */
const std::string User::getPassword() const {
	return password;
}

/**
 * @brief Returns the user permission role.
 *
 * @return Permission role.
 */
const Permission User::getPermissionRole() const {
	return role;
}

/**
 * @brief Returns the user's points.
 *
 * @return Points.
 */
const unsigned int User::getPoints() const {
	return points;
}

/**
 * @brief Returns the unique user ID.
 *
 * @return Unique ID.
 */
const unsigned int User::getId() const {
	return id;
}

/**
 * @brief Creates a clone of the user.
 *
 * @return Pointer to the cloned User object.
 */
User* User::clone() const {
	return new User(*this);
}

/**
 * @brief Saves user data to a file.
 *
 * @param of Output file stream.
 */
void User::writeToFile(std::ofstream& of) const {
	of.write(reinterpret_cast<const char*>(&role), sizeof(Permission));

	unsigned int size = firstName.size();
	of.write(reinterpret_cast<const char*>(&size), sizeof(size));
	of.write((const char*)&firstName[0], size);

	size = lastName.size();
	of.write(reinterpret_cast<const char*>(&size), sizeof(size));
	of.write((const char*)&lastName[0], size);

	size = nickname.size();
	of.write(reinterpret_cast<const char*>(&size), sizeof(size));
	of.write((const char*)&nickname[0], size);

	size = password.size();
	of.write(reinterpret_cast<const char*>(&size), sizeof(size));
	of.write((const char*)&password[0], size);

	of.write(reinterpret_cast<const char*>(&id), sizeof(id));
	of.write(reinterpret_cast<const char*>(&points), sizeof(points));
	of.write(reinterpret_cast<const char*>(&role), sizeof(Permission));
}

/**
 * @brief Reads user data from a file.
 *
 * @param iff Input file stream.
 */
void User::readFromFile(std::ifstream& iff) {
	unsigned int size = 0;
	iff.read(reinterpret_cast<char*>(&size), sizeof(size));
	firstName.resize(size);
	iff.read((char*)&firstName[0], size);

	iff.read(reinterpret_cast<char*>(&size), sizeof(size));
	lastName.resize(size);
	iff.read((char*)&lastName[0], size);

	iff.read(reinterpret_cast<char*>(&size), sizeof(size));
	nickname.resize(size);
	iff.read((char*)&nickname[0], size);

	iff.read(reinterpret_cast<char*>(&size), sizeof(size));
	password.resize(size);
	iff.read((char*)&password[0], size);

	iff.read(reinterpret_cast<char*>(&id), sizeof(id));
	iff.read(reinterpret_cast<char*>(&points), sizeof(points));
	iff.read(reinterpret_cast<char*>(&role), sizeof(Permission));

	ID = id + 1; // maybe not good
}
