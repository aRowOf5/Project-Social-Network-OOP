#pragma once
#include "Discussion.h"

/**
 * @brief Topic class represents a topic with related discussions.
 */
class Topic {
private:
    std::string title; /**< Topic title. */
    std::string topicDescription; /**< Topic description. */
    unsigned int creatorId; /**< Topic creator ID. */
    unsigned int id; /**< Unique topic identifier. */

    Discussion* discussions; /**< Array of discussions related to the topic. */
    unsigned int discussionCapacity; /**< Discussion array capacity. */
    unsigned int discussionNum; /**< Number of discussions in the topic. */
    unsigned int discussionID; /**< Unique identifier for each discussion. */

    static unsigned int topicID; /**< Static variable for a unique identifier for each topic. */

    /**
     * @brief Copies data from another topic.
     *
     * @param other The topic from which data will be copied.
     */
    void copyFrom(const Topic& other);

    /**
     * @brief Increases the capacity of the discussion array.
     */
    void resizeDiscussions();

public:
    /**
     * @brief Constructor for initializing a topic with a given title, description, and creator ID.
     *
     * @param title Topic title.
     * @param description Topic description.
     * @param creatorId Topic creator ID.
     */
    Topic(const std::string& title, const std::string& description, unsigned int creatorId);

    /**
     * @brief Default constructor for the Topic class.
     */
    Topic();

    /**
     * @brief Copy constructor for the Topic class.
     *
     * @param other The topic from which data will be copied.
     */
    Topic(const Topic& other);

    /**
     * @brief Assignment operator for the Topic class.
     *
     * @param other The topic from which data will be assigned.
     * @return Reference to the assigned discussion.
     */
    Topic& operator=(const Topic& other);

    /**
     * @brief Destructor for the Topic class.
     */
    ~Topic();

    /**
     * @brief Sets a new topic title.
     *
     * @param newTitle The new topic title.
     */
    void setTopicTitle(const std::string& newTitle);

    /**
     * @brief Sets a new topic description.
     *
     * @param newDescription The new topic description.
     */
    void setTopicDescription(const std::string& newDescription);

    /**
     * @brief Sets the ID of the topic creator.
     *
     * @param id Topic creator ID.
     */
    void setCreatorId(unsigned int id);

    /**
     * @brief Increases the number of discussions in the topic by one.
     */
    void discussionNumIncrement();

    /**
     * @brief Decreases the number of discussions in the topic by one.
     */
    void discussionNumDecrement();

    /**
     * @brief Returns the topic title.
     *
     * @return Topic title.
     */
    std::string getTopicTitle() const;

    /**
     * @brief Returns the topic description.
     *
     * @return Topic description.
     */
    std::string getTopicDescription() const;

    /**
     * @brief Returns the ID of the topic creator.
     *
     * @return Topic creator ID.
     */
    unsigned int getTopicCreatorId() const;

    /**
     * @brief Returns the unique ID of the topic.
     *
     * @return Unique topic identifier.
     */
    unsigned int getTopicId() const;

    /**
     * @brief Returns the number of discussions in the topic.
     *
     * @return Number of discussions in the topic.
     */
    unsigned int getDiscussionNum() const;

    /**
     * @brief Returns the unique identifier for discussions in the topic.
     *
     * @return Unique identifier for discussions.
     */
    unsigned int getDiscussionID() const;

    /**
     * @brief Returns a pointer to the array of discussions in the topic.
     *
     * @return Pointer to the array of discussions in the topic.
     */
    Discussion* getTopicDiscussions() const;

    /**
     * @brief Saves the topic data to a file.
     *
     * @param of Output file stream.
     */
    void writeToFile(std::ofstream& of);

    /**
     * @brief Reads topic data from a file.
     *
     * @param iff Input file stream.
     */
    void readFromFile(std::ifstream& iff);

    // Discussion commands, just like in Discussion.h
    // Implemented in System.h
};
