#include "System.h"

/**
 * @brief Doubles the capacity of the user array and clones existing users to a new array.
 */
void System::resizeUsers() {
	capacityOfUsers *= 2;
	User** newArr = new User * [capacityOfUsers];
	for (size_t i = 0; i < numOfUsers; i++) {
		newArr[i] = users[i]->clone();
		delete users[i];
	}
	delete[] users;
	users = newArr;
}

/**
 * @brief Doubles the capacity of the topic array and copies existing topics to a new array.
 */
void System::resizeTopics() {
	capacityOfTopics *= 2;
	Topic* newArr = new Topic[capacityOfTopics];
	for (size_t i = 0; i < numOfTopics; i++) {
		newArr[i] = topics[i];
	}
	delete[] topics;
	topics = newArr;
}

/**
 * @brief Frees memory for all users and topics on the system.
 */
void System::free() {
	for (size_t i = 0; i < numOfUsers; i++) {
		delete users[i];
		users[i] = nullptr;
	}
	delete[] users;
	users = nullptr;

	delete[] topics;
	topics = nullptr;
}

/**
 * @brief Default constructor that initializes the system with initial values.
 */
System::System() : capacityOfUsers(2), numOfUsers(0), capacityOfTopics(2), numOfTopics(0), currUserId(-1),
currUserPermission(Permission::NaN), currTopicId(-1), currDiscussionId(-1) {
	users = new User * [capacityOfUsers] {nullptr};
	topics = new Topic[capacityOfTopics];
}

/**
 * @brief Destructor that releases all system resources.
 */
System::~System() {
	free();
}

/**
 * @brief Registers a new user in the system.
 */
void System::signup() {
	std::string firstName, lastName, nickname, password;

	std::cout << ">Enter First Name: ";
	std::cin >> firstName;

	std::cout << "\n>Enter Last Name: ";
	std::cin >> lastName;

	std::cout << "\n>Enter Nickname: ";
	std::cin >> nickname;
	bool flag = false;
	do {
		for (size_t i = 0; i < numOfUsers; i++) {
			if (users[i]->getNickname() == nickname) {
				flag = true;
				std::cout << "\n>A user with this nickname already exists!";
				break;
			}
		}
		if (flag) {
			std::cout << ">Enter a new nickname: ";
			std::cin >> nickname;
		}
	} while (flag);

	std::cout << "\n>Enter password: ";
	std::cin >> password;

	if (numOfUsers == 0) {
		Moderator firstNewUser(firstName, lastName, nickname, password);
		users[numOfUsers] = firstNewUser.clone();
		numOfUsers++;
	}
	else {
		User newUser(firstName, lastName, nickname, password);
		users[numOfUsers] = newUser.clone();
		numOfUsers++;
	}

	if (numOfUsers >= capacityOfUsers) {
		resizeUsers();
	}
}

/**
 * @brief Login with username and password.
 * @param nickname Username.
 * @param password Password.
 */
void System::login(const std::string& nickname, const std::string& password) {
	bool nicknameFlag = 0, passwordFlag = 0;
	for (size_t i = 0; i < numOfUsers; i++) {
		nicknameFlag = passwordFlag = false;
		if (users[i]->getNickname() == nickname) {
			nicknameFlag = true;
			if (users[i]->getPassword() == password) {
				passwordFlag = true;
				currUserId = i;
				currUserPermission = users[i]->getPermissionRole();
			}
			break;
		}
	}

	if (!nicknameFlag) {
		std::cout << ">User with this nickname does not exist!";
		return;
	}
	if (!passwordFlag) {
		std::cout << ">User's password is incorrect!";
		return;
	}

	std::cout << ">Welcome, " << users[currUserId]->getFirstName();
}

/**
 * @brief Edits information about the current user or another user if the current user has sufficient rights.
 */
void System::editUser() {
	std::string buff;
	do {
		std::cout << ">What do you want to edit: ";
		std::cin >> buff;
		if (buff == "firstName") {
			std::cout << ">Enter new first name: ";
			std::cin >> buff;
			users[currUserId]->setFirstName(buff);
			continue;
		}
		else if (buff == "lastName") {
			std::cout << ">Enter new last name: ";
			std::cin >> buff;
			users[currUserId]->setLastName(buff);
			continue;
		}
		else if (buff == "password") {
			std::cout << ">Enter new password: ";
			std::cin >> buff;
			users[currUserId]->setPassword(buff);
			continue;
		}
		else if (buff == "id") {
			if (currUserPermission == Permission::MOD) {
				std::cout << ">Access granted!\n";
				unsigned int id;
				std::cout << ">Enter the id of user: ";
				std::cin >> id;
				if (id >= numOfUsers) {
					std::cout << ">No such user exists!\n";
					continue;
				}
				std::cout << ">Enter new role of selected user: ";
				std::cin >> buff;
				if (buff == "user" || buff == "User" || buff == "USER") {
					users[id]->setPermissionRole(Permission::USER);
					continue;
				}
				else if (buff == "mod" || buff == "Mod" || buff == "MOD" || buff == "moderator" || buff == "Moderator" || buff == "MODERATOR") {
					users[id]->setPermissionRole(Permission::MOD);
					continue;
				}
				else {
					std::cout << ">No such role exists!\n";
				}
			}
			else {
				std::cout << ">Access denied!\n";
			}
		}
		else {
			std::cout << ">No such editable parameter exists! Editable parameters are: firstName, lastName, password and id.\n";
		}
	} while (buff != "goBack");
}

/**
 * @brief Logout.
 */
void System::logout() {
	std::cout << "	Goodbye, " << users[currUserId]->getFirstName() << std::endl;
	currUserId = -1;
	currUserPermission = Permission::NaN;
	currTopicId = -1;
	currDiscussionId = -1;
}

/**
 * @brief Loads social network data from a file.
 * @param fileName File name.
 */
void System::load(const std::string& fileName) {
	std::ifstream readFile(fileName, std::ios::binary);
	if (!readFile.is_open()) {
		std::cout << ">File does not exist!" << std::endl;
		readFile.close();
		return;
	}

	// if the file exists...
	free();

	readFile.read(reinterpret_cast<char*>(&numOfUsers), sizeof(numOfUsers));
	readFile.read(reinterpret_cast<char*>(&capacityOfUsers), sizeof(capacityOfUsers));

	users = new User * [capacityOfUsers] {nullptr};

	Permission userPerm = Permission::NaN;
	for (size_t i = 0; i < numOfUsers; i++) {
		readFile.read(reinterpret_cast<char*>(&userPerm), sizeof(Permission));
		if (userPerm == Permission::USER) {
			User* userToRead = new User();
			userToRead->readFromFile(readFile);

			users[i] = userToRead->clone();
			delete userToRead;
			continue;
		}
		if (userPerm == Permission::MOD) {
			Moderator* modToRead = new Moderator();
			modToRead->readFromFile(readFile);

			users[i] = modToRead->clone();
			delete modToRead;
		}
	}

	readFile.read(reinterpret_cast<char*>(&numOfTopics), sizeof(numOfTopics));
	readFile.read(reinterpret_cast<char*>(&capacityOfTopics), sizeof(capacityOfTopics));

	topics = new Topic[capacityOfTopics];

	for (size_t i = 0; i < numOfTopics; i++) {
		topics[i].readFromFile(readFile);

		for (size_t j = 0; j < topics[i].getDiscussionNum(); j++) {
			topics[i].getTopicDiscussions()[j].readFromFile(readFile);

			for (size_t k = 0; k < topics[i].getTopicDiscussions()[j].getCommentNum(); k++) {
				topics[i].getTopicDiscussions()[j].getDiscussionComments()[k].readFromFile(readFile);
			}
		}
	}

	std::cout << ">Load successful!" << std::endl;
	currFileOpened = fileName;
	readFile.close();
}

/**
 * @brief Saves the current state of the social network to a file.
 *
 * If the file does not exist, it asks the user whether to create it.
 * If a file is not created, the current progress is not saved.
 */
void System::save() const {
	std::ifstream tryToOpen(currFileOpened, std::ios::binary);
	if (!tryToOpen.is_open()) {
		char answer;
		std::string fileName;
		std::cout << ">No previous save was found! Do you wish to create a file? (Y/N)" << std::endl;
		std::cin >> answer;
		if (answer != 'Y' && answer != 'y') {
			std::cout << ">Current progress was not saved!" << std::endl;
			tryToOpen.close();
			return;
		}
		std::cout << ">Enter file name: ";
		std::cin >> fileName;
		saveAs(fileName);
		return;
	}
	tryToOpen.close();

	// if the file exists...
	std::ofstream writeFile(currFileOpened, std::ios::binary);

	writeFile.write(reinterpret_cast<const char*>(&numOfUsers), sizeof(numOfUsers));
	writeFile.write(reinterpret_cast<const char*>(&capacityOfUsers), sizeof(capacityOfUsers));
	// there is a resize() function, but why use it when you can directly set the capacity

	for (size_t i = 0; i < numOfUsers; i++) {
		//writeFile.write(reinterpret_cast<const char*>(users[i]->getPermissionRole()), sizeof(Permission));
		users[i]->writeToFile(writeFile);
	}

	// begins saving data from topics
	writeFile.write(reinterpret_cast<const char*>(&numOfTopics), sizeof(numOfTopics));
	writeFile.write(reinterpret_cast<const char*>(&capacityOfTopics), sizeof(capacityOfTopics));

	for (size_t i = 0; i < numOfTopics; i++) {
		topics[i].writeToFile(writeFile);

		for (size_t j = 0; j < topics[i].getDiscussionNum(); j++) {
			topics[i].getTopicDiscussions()[j].writeToFile(writeFile);

			for (size_t k = 0; k < topics[i].getTopicDiscussions()[j].getCommentNum(); k++) {
				topics[i].getTopicDiscussions()[j].getDiscussionComments()[k].writeToFile(writeFile);
			}
		}
	}

	std::cout << ">Current progress was saved!" << std::endl;
	writeFile.close();
}

/**
 * @brief Saves the current state of the social network to a specified file.
 * @param fileName File name.
 */
void System::saveAs(const std::string& fileName) const {
	std::ofstream writeFile(fileName, std::ios::binary);

	// newly created file...
	writeFile.write(reinterpret_cast<const char*>(&numOfUsers), sizeof(numOfUsers));
	writeFile.write(reinterpret_cast<const char*>(&capacityOfUsers), sizeof(capacityOfUsers));
	// there is a resize() function, but why use it when you can directly set the capacity

	for (size_t i = 0; i < numOfUsers; i++) {

		//writeFile.write(reinterpret_cast<const char*>(users[i]->getPermissionRole()), sizeof(Permission));
		users[i]->writeToFile(writeFile);
	}

	// begins saving data from topics
	writeFile.write(reinterpret_cast<const char*>(&numOfTopics), sizeof(numOfTopics));
	writeFile.write(reinterpret_cast<const char*>(&capacityOfTopics), sizeof(capacityOfTopics));

	for (size_t i = 0; i < numOfTopics; i++) {
		topics[i].writeToFile(writeFile);

		for (size_t j = 0; j < topics[i].getDiscussionNum(); j++) {
			topics[i].getTopicDiscussions()[j].writeToFile(writeFile);

			for (size_t k = 0; k < topics[i].getTopicDiscussions()[j].getCommentNum(); k++) {
				topics[i].getTopicDiscussions()[j].getDiscussionComments()[k].writeToFile(writeFile);
			}
		}
	}

	std::cout << ">Current progress was saved!" << std::endl;
	writeFile.close();
}

/**
 * @brief Creates a new topic.
 * @param topicTitle Topic title.
 * @param description Topic description.
 */
void System::createTopic(const std::string& topicTitle, const std::string& description) {
	Topic newTopic(topicTitle, description, currUserId);
	topics[numOfTopics] = newTopic;
	numOfTopics++;

	if (numOfTopics >= capacityOfTopics) {
		resizeTopics();
	}
}

/**
 * @brief Searches for a topic by part of the title and displays it if found.
 * @param partOfTitle Part of the topic title.
 */
void System::searchTopic(const std::string& partOfTitle) {
	unsigned int found = 0;
	for (size_t i = 0; i < numOfTopics; i++) {
		found = topics[i].getTopicTitle().find(partOfTitle);
		if (found != std::string::npos) {
			std::cout << "	>>" << topics[i].getTopicTitle() << " {id: " << topics[i].getTopicId() << "}\n";
			return;
		}
	}
	std::cout << ">No topic found!" << std::endl;
}

/**
 * @brief Opens topic by title.
 * @param topicTitle Topic title.
 */
void System::openTopic(const std::string& topicTitle) {
	if (currTopicId > -1) {
		std::cout << ">A topic is already opened!" << std::endl;
		return;
	}

	for (size_t i = 0; i < numOfTopics; i++) {
		if (topics[i].getTopicTitle() == topicTitle) {
			currTopicId = topics[i].getTopicId();
			break;
		}
	}

	if (currTopicId > -1) {
		std::cout << "	Welcome to \"" + topics[currTopicId].getTopicTitle() + "\"." << std::endl;
		return;
	}
	std::cout << ">Topic with such name does not exist!" << std::endl;
}

/**
 * @brief Opens a topic by specified ID.
 *
 * @param topicId Identifier of the topic to be opened.
 *
 * If a topic is already opened or if no topic with that ID exists,
 * an appropriate error message is displayed.
 */
void System::openTopic(unsigned int topicId) {
	if (currTopicId > -1) {
		std::cout << ">A topic is already opened!" << std::endl;
		return;
	}

	for (size_t i = 0; i < numOfTopics; i++) {
		if (topics[i].getTopicId() == topicId) {
			currTopicId = topics[i].getTopicId();
			break;
		}
	}

	if (currTopicId > -1) {
		std::cout << "	Welcome to \"" + topics[currTopicId].getTopicTitle() + "\"." << std::endl;
		return;
	}
	std::cout << ">Topic with such id does not exist!" << std::endl;
}

/**
 * @brief Closes the currently opened topic.
 *
 * If there is no opened topic or if a discussion is opened, an error message is displayed.
 */
void System::quitTopic() {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId != -1) {
		currDiscussionId = -1;
	}

	std::cout << "	Closing topic \"" << topics[currTopicId].getTopicTitle() << "\"." << std::endl;
	currTopicId = -1;
}

/**
 * @brief Removes a topic by a given ID.
 *
 * @param topicId Identifier of the topic to be removed.
 *
 * Only moderators can remove topics. Upon successful removal,
 * a recalculation of users' points is called.
 */
void System::removeTopic(unsigned int topicId) {
	if (currUserPermission != Permission::MOD) {
		std::cout << ">Access denied!" << std::endl;
		return;
	}

	for (size_t i = 0; i < numOfTopics; i++) {
		if (topics[i].getTopicId() < topicId) {
			continue;
		}
		topics[i] = topics[i + 1];
	}
	numOfTopics--;

	calculateUserPoints();
}

/**
 * @brief Displays a list of discussions in the currently open topic.
 *
 * If no topic is selected, an error message is displayed.
 */
void System::listDiscussions() const {
	for (size_t i = 0; i < topics[currTopicId].getDiscussionNum(); i++) {
		std::cout << "	" + topics[currTopicId].getTopicDiscussions()->getDiscussionTitle() <<
			" {id: " + topics[currTopicId].getTopicDiscussions()->getDiscussionId() << "}\n";
	}
}

/**
 * @brief Post a new discussion in the currently opened topic.
 *
 * @param discussionTitle Title of the new discussion.
 * @param discussionContents Content of the new discussion.
 *
 * If no topic is selected, an error message is displayed.
 */
void System::postDiscussion(const std::string& discussionTitle, const std::string& discussionContents) {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	Discussion newDiscussion(discussionTitle, discussionContents, currUserId, topics[currTopicId].getDiscussionNum());
	topics[currTopicId].getTopicDiscussions()[topics[currTopicId].getDiscussionNum()] = newDiscussion;
	topics[currTopicId].discussionNumIncrement();
}

/**
 * @brief Opens a discussion by a specified identifier.
 *
 * @param discussionId Identifier of the discussion to be opened.
 *
 * If no topic is selected, an error message is displayed.
 * If another discussion is already opened or if no discussion with
 * such an identifier exists, an appropriate error message is displayed.
 */
void System::openDiscussion(unsigned int discussionId) {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId != -1) {
		std::cout << ">A discussion is already opened!" << std::endl;
		return;
	}

	for (size_t i = 0; i < topics[currTopicId].getDiscussionNum(); i++) {
		if (topics[currTopicId].getTopicDiscussions()[i].getDiscussionId() == discussionId) {
			currDiscussionId = topics[currTopicId].getTopicDiscussions()[i].getDiscussionId();
			break;
		}
	}

	if (currDiscussionId > -1) {
		std::cout << "	Welcome to \"" << topics[currTopicId].getTopicDiscussions()[currDiscussionId].getDiscussionTitle() << "\".\n";
		std::cout << "	The contents of this discussion are as follow: \n	" <<
			topics[currTopicId].getTopicDiscussions()[currDiscussionId].getDiscussionContents() << ".\n";
		std::cout << "	There are currently " + topics[currTopicId].getTopicDiscussions()[currDiscussionId].getCommentNum() <<
			" comments in the discussion." << std::endl;
		return;
	}
	std::cout << ">Discussion with such id does not exist!" << std::endl;
}

/**
 * @brief Closes the currently open discussion.
 *
 * If there is no topic selected or if there is no opened discussion, an error message is displayed.
 */
void System::quitDiscussion(){
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}

	std::cout << "	Closing discussion \"" << topics[currTopicId].getTopicDiscussions()[currDiscussionId].getDiscussionTitle() << "\"." << std::endl;
	currDiscussionId = -1;
}

/**
 * @brief Removes discussion by specified ID.
 *
 * @param discussionId ID of the discussion to be removed.
 *
 * Only moderators can remove discussions. Upon successful removal,
 * a recalculation of users' points is called.
 */
void System::removeDiscussion(unsigned int discussionId) {
	//topics[currTopicId].getTopicDiscussions()[currDiscussionId].
	if (currUserPermission != Permission::MOD) {
		std::cout << ">Access denied!" << std::endl;
		return;
	}

	for (size_t i = 0; i < topics[currTopicId].getDiscussionNum(); i++) {
		if (topics[currTopicId].getTopicDiscussions()[i].getDiscussionId() < discussionId) {
			continue;
		}
		topics[currTopicId].getTopicDiscussions()[i] = topics[currTopicId].getTopicDiscussions()[i + 1];
	}
	topics[currTopicId].discussionNumDecrement();

	// change user points/rating...
	calculateUserPoints();
}

/**
 * @brief Displays a list of comments in the currently opened discussion.
 *
 * If no topic or discussion is selected, an error message is displayed.
 */
void System::listComments() const {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}
	topics[currTopicId].getTopicDiscussions()[currDiscussionId].listComments();
}

/**
 * @brief Adds a new comment to the currently opened discussion.
 *
 * If no topic or discussion is selected, an error message is displayed.
 */
void System::addComment() {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}
	topics[currTopicId].getTopicDiscussions()[currDiscussionId].addComment(currUserId);
}

/**
 * @brief Adds a reply to a comment in the currently opened discussion.
 *
 * @param commentId ID of the comment to which the reply is being added.
 *
 * If no topic or discussion is selected, an error message is displayed.
 */
void System::addReply(unsigned int commentId) {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}
	topics[currTopicId].getTopicDiscussions()[currDiscussionId].commentReply(currUserId, commentId);
}

/**
 * @brief Vote for a comment in the currently opened discussion.
 *
 * @param commentId Comment ID being voted on.
 *
 * If no topic or discussion is selected, an error message is displayed.
 */
void System::commentVote(unsigned int commentId) {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}
	topics[currTopicId].getTopicDiscussions()[currDiscussionId].commentVote(currUserId, commentId);
}

/**
 * @brief Removes a comment by a given ID.
 *
 * @param commentId Comment ID to be removed.
 *
 * If no topic or discussion is selected, an error message is displayed.
 */
void System::removeComment(unsigned int commentId) {
	if (currTopicId == -1) {
		std::cout << ">No topic selected!" << std::endl;
		return;
	}
	if (currDiscussionId == -1) {
		std::cout << ">No discussion selected!" << std::endl;
		return;
	}
	topics[currTopicId].getTopicDiscussions()[currDiscussionId].removeComment(currUserId, commentId, currUserPermission);
}

/**
 * @brief Calculates and updates users' points in the system.
 *
 * Points are calculated based on the ratings of the comments they have written.
 * When this method is called, all user points are reset and recalculated.
 */
void System::calculateUserPoints() { // maybe recalculate
	// If I take out the first for-loop and add userId, there will be three for-loops
	for (size_t i = 0; i < numOfUsers; i++) {
		users[i]->changePoints(0); // resets previous score and recalculates points
		for (size_t j = 0; j < numOfTopics; j++) {
			for (size_t k = 0; k < topics[j].getDiscussionNum(); k++) {
				for (size_t l = 0; l < topics[j].getTopicDiscussions()[k].getCommentNum(); l++) {
					if (topics[j].getTopicDiscussions()[k].getDiscussionComments()[l].getAuthorId() == users[i]->getId()) {
						users[i]->changePoints(topics[j].getTopicDiscussions()[k].getDiscussionComments()[l].getCommentRating());
					}
				}
			}
		}
	}
}
