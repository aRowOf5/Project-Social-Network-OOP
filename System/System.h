#pragma once
#include <fstream>
#include "Moderator.h"
#include "Topic.h"

/**
 * @brief The System class represents the entire social network. This class is a singleton and provides various functions for managing users, topics, discussions, and comments.
 */
class System {
private:
	User** users; ///< Array of pointers to users.
	Topic* topics; ///< Array of topics.

	unsigned int capacityOfUsers; ///< User array capacity.
	unsigned int numOfUsers; ///< Number of current users.

	unsigned int capacityOfTopics; ///< Topic array capacity.
	unsigned int numOfTopics; ///< Number of current topics.

	int currUserId; ///< ID of the currently logged in user.
	Permission currUserPermission; ///< Permession role of the currently logged in user.

	std::string currFileOpened; ///< The name of the currently open social network file.

	int currTopicId; ///< Identifier of the currently open topic.
	int currDiscussionId; ///< Identifier of the currently open discussion.

	/**
	 * @brief Increases the capacity of the user array.
	 */
	void resizeUsers();

	/**
	 * @brief Increases the capacity of the topic array.
	 */
	void resizeTopics();

	/**
	 * @brief Frees dynamically allocated memory.
	 */
	void free();

public:
	/**
	 * @brief Default constructor.
	 */
	System();

	/**
	 * @brief Destructor.
	 */
	~System();

	/**
	 * @brief Registers a new user in the system.
	 */
	void signup();

	/**
	 * @brief Login with username and password.
	 * @param nickname Username.
	 * @param password Password.
	 */
	void login(const std::string& nickname, const std::string& password);

	/**
	 * @brief Logout.
	 */
	void logout();

	/**
	 * @brief Edits information about the current user or another user if the current user has sufficient rights.
	 */
	void editUser();

	/**
	 * @brief Loads social network data from a file.
	 * @param fileName File name.
	 */
	void load(const std::string& fileName);

	/**
	 * @brief Saves the current state of the social network to a file.
	 */
	void save() const;

	/**
	 * @brief Saves the current state of the social network to a specified file.
	 * @param fileName File name.
	 */
	void saveAs(const std::string& fileName) const;

	/**
	 * @brief Creates a new topic.
	 * @param topicTitle Topic title.
	 * @param description Topic description.
	 */
	void createTopic(const std::string& topicTitle, const std::string& description);

	/**
	 * @brief Searches for a topic by part of the title and displays it if found.
	 * @param partOfTitle Part of the topic title.
	 */
	void searchTopic(const std::string& partOfTitle);

	/**
	 * @brief Opens topic by title.
	 * @param topicTitle Topic title.
	 */
	void openTopic(const std::string& topicTitle);

	/**
	 * @brief Opens topic by ID.
	 * @param topicId Topic ID.
	 */
	void openTopic(unsigned int topicId);

	/**
	 * @brief Closes the currently open topic.
	 */
	void quitTopic();

	/**
	 * @brief Removes topic by ID.
	 * @param topicId Topic ID.
	 */
	void removeTopic(unsigned int topicId);

	/**
	 * @brief Displays a list of discussions in the currently open topic.
	 */
	void listDiscussions() const;

	/**
	 * @brief Post a new discussion in the currently open topic.
	 * @param discussionTitle Discussion title.
	 * @param discussionContents Discussion content.
	 */
	void postDiscussion(const std::string& discussionTitle, const std::string& discussionContents);

	/**
	 * @brief Opens discussion by ID.
	 * @param discussionId Discussion ID.
	 */
	void openDiscussion(unsigned int discussionId);

	/**
	 * @brief Closes the currently open discussion.
	 */
	void quitDiscussion();

	/**
	 * @brief Removes discussion by ID.
	 * @param discussionId Discussion ID.
	 */
	void removeDiscussion(unsigned int discussionId);

	/**
	 * @brief Displays a list of comments in the currently open discussion.
	 */
	void listComments() const;

	/**
	 * @brief Adds a new comment to the currently open discussion.
	 */
	void addComment();

	/**
	 * @brief Adds a reply to a comment by ID.
	 * @param commentId Comment ID.
	 */
	void addReply(unsigned int commentId);

	/**
	 * @brief Vote for comment by ID.
	 * @param commentId Comment ID.
	 */
	void commentVote(unsigned int commentId);

	/**
	 * @brief Removes comment by ID.
	 * @param commentId Comment ID.
	 */
	void removeComment(unsigned int commentId);

	/**
	 * @brief Calculates users' points.
	 */
	void calculateUserPoints();
};
