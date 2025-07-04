#include "Moderator.h"

/**
 * @brief Constructor that creates a new Moderator object with the specified parameters.
 *
 * @param firstName Moderator's first name.
 * @param lastName Moderator's last name.
 * @param nickname Moderator's nickname.
 * @param password Moderator's password.
 */
Moderator::Moderator(const std::string& firstName, const std::string& lastName, const std::string& nickname, const std::string& password) :
    User(firstName, lastName, nickname, password){
    setPermissionRole(Permission::MOD);
}

/**
 * @brief Default constructor.
 */
Moderator::Moderator() : User() {
	setPermissionRole(Permission::MOD);
}

/**
 * @brief Clones the Moderator object.
 *
 * @return Pointer to the new User object (in this case Moderator).
 */
User* Moderator::clone() const {
    return new Moderator(*this);
}

/**
 * @brief Saves moderator data to a file.
 *
 * @param of The output file stream.
 */
void Moderator::writeToFile(std::ofstream& of) const {
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
 * @brief Reads moderator data from a file.
 *
 * @param iff The input file stream.
 */
void Moderator::readFromFile(std::ifstream& iff) {
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
}
