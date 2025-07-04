#include "Topic.h"

/**
 * @brief Initialization of the static variable topicID.
 */
unsigned int Topic::topicID = 0;

/**
 * @brief Copies data from another topic.
 *
 * @param other The topic from which data will be copied.
 */
void Topic::copyFrom(const Topic& other) {
    setTopicTitle(other.title);
    setTopicDescription(other.topicDescription);
    setCreatorId(other.creatorId);
    id = other.id;

    discussionCapacity = other.discussionCapacity;
    discussionNum = other.discussionNum;
    discussions = new Discussion[discussionCapacity];
    for (size_t i = 0; i < discussionNum && i < discussionCapacity; i++) {
        discussions[i] = other.discussions[i];
    }
    discussionID = other.discussionID;
}

/**
 * @brief Increases the capacity of the discussion array.
 */
void Topic::resizeDiscussions() {
    discussionCapacity *= 2;
    Discussion* newArr = new Discussion[discussionCapacity];
    for (size_t i = 0; i < discussionNum; i++) {
        newArr[i] = discussions[i];
    }
    delete[] discussions;
    discussions = newArr;
}

/**
 * @brief Constructor for initializing a topic with a given title, description, and creator ID.
 *
 * @param title Topic title.
 * @param description Topic description.
 * @param creatorId Topic creator ID.
 */
Topic::Topic(const std::string& title, const std::string& description, unsigned int creatorId) : discussionCapacity(2) {
    setTopicTitle(title);
    setTopicDescription(description);
    setCreatorId(creatorId);
    id = topicID++;

    discussions = new Discussion[discussionCapacity];
    discussionNum = 0;
    discussionID = 0;
}

/**
 * @brief Default constructor for the Topic class.
 */
Topic::Topic() : title(""), topicDescription(""), creatorId(0), id(0), discussionCapacity(2), discussionNum(0), discussionID(0) {
    discussions = new Discussion[discussionCapacity];
}

/**
 * @brief Copy constructor for the Topic class.
 *
 * @param other The topic from which data will be copied.
 */
Topic::Topic(const Topic& other) {
    copyFrom(other);
}

/**
 * @brief Assignment operator for the Topic class.
 *
 * @param other The topic from which data will be assigned.
 * @return Reference to the assigned discussion.
 */
Topic& Topic::operator=(const Topic& other) {
    if (this != &other) {
        delete[] discussions;
        copyFrom(other);
    }
    return *this;
}

/**
 * @brief Destructor for the Topic class.
 */
Topic::~Topic() {
    delete[] discussions;
}

/**
 * @brief Sets a new topic title.
 *
 * @param newTitle The new topic title.
 */
void Topic::setTopicTitle(const std::string& newTitle) {
    title.resize(newTitle.size());
    title = newTitle;
}

/**
 * @brief Sets a new topic description.
 *
 * @param newDescription The new topic description.
 */
void Topic::setTopicDescription(const std::string& newDescription) {
    topicDescription.resize(newDescription.size());
    topicDescription = newDescription;
}

/**
 * @brief Sets the ID of the topic creator.
 *
 * @param id Topic creator ID.
 */
void Topic::setCreatorId(unsigned int id) {
    creatorId = id;
}

/**
 * @brief Increases the number of discussions in the topic by one.
 */
void Topic::discussionNumIncrement() {
    discussionNum++;
    if (discussionNum >= discussionCapacity) {
        resizeDiscussions();
    }
}

/**
 * @brief Decreases the number of discussions in the topic by one.
 */
void Topic::discussionNumDecrement() {
    discussionNum--;
}

/**
 * @brief Returns the topic title.
 *
 * @return Topic title.
 */
std::string Topic::getTopicTitle() const {
    return title;
}

/**
 * @brief Returns the topic description.
 *
 * @return Topic description.
 */
std::string Topic::getTopicDescription() const {
    return topicDescription;
}

/**
 * @brief Returns the ID of the topic creator.
 *
 * @return Topic creator ID.
 */
unsigned int Topic::getTopicCreatorId() const {
    return creatorId;
}

/**
 * @brief Returns the unique ID of the topic.
 *
 * @return Unique topic identifier.
 */
unsigned int Topic::getTopicId() const {
    return id;
}

/**
 * @brief Returns the number of discussions in the topic.
 *
 * @return Number of discussions in the topic.
 */
unsigned int Topic::getDiscussionNum() const {
    return discussionNum;
}

/**
 * @brief Returns the unique identifier for discussions in the topic.
 *
 * @return Unique identifier for discussions.
 */
unsigned int Topic::getDiscussionID() const {
    return discussionID;
}

/**
 * @brief Returns a pointer to the array of discussions in the topic.
 *
 * @return Pointer to the array of discussions in the topic.
 */
Discussion* Topic::getTopicDiscussions() const {
    return discussions;
}

/**
 * @brief Saves the topic data to a file.
 *
 * @param of Output file stream.
 */
void Topic::writeToFile(std::ofstream& of) {
    unsigned int size = title.size();
    of.write(reinterpret_cast<const char*>(&size), sizeof(size));
    of.write((const char*)&title[0], size);

    size = topicDescription.size();
    of.write(reinterpret_cast<const char*>(&size), sizeof(size));
    of.write((const char*)&topicDescription[0], size);

    of.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
    of.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // Saves discussion data
    of.write(reinterpret_cast<const char*>(&discussionNum), sizeof(discussionNum));
    of.write(reinterpret_cast<const char*>(&discussionID), sizeof(discussionID));

    // Saves information about discussions...
}

/**
 * @brief Reads topic data from a file.
 *
 * @param iff Input file stream.
 */
void Topic::readFromFile(std::ifstream& iff) {
    unsigned int size = 0;
    iff.read(reinterpret_cast<char*>(&size), sizeof(size));
    title.resize(size);
    iff.read(&title[0], size);

    iff.read(reinterpret_cast<char*>(&size), sizeof(size));
    topicDescription.resize(size);
    iff.read((char*)&topicDescription[0], size);

    iff.read(reinterpret_cast<char*>(&creatorId), sizeof(creatorId));
    iff.read(reinterpret_cast<char*>(&id), sizeof(id));

    iff.read(reinterpret_cast<char*>(&discussionNum), sizeof(discussionNum));
    iff.read(reinterpret_cast<char*>(&discussionID), sizeof(discussionID));

    topicID = id + 1;

    while (discussionCapacity <= discussionNum) {
        resizeDiscussions();
    }
    // Read information about discussions...
}
