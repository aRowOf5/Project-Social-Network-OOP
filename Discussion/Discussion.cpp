#include "Discussion.h"

/**
 * @brief Copies data from another discussion.
 *
 * @param other The discussion from which data will be copied.
 */
void Discussion::copyFrom(const Discussion& other) {
    setDiscussionTitle(other.title);
    setDiscussionContents(other.contents);
    setDiscussionCreatorId(other.creatorId);
    id = other.id;

    commentCapacity = other.commentCapacity;
    commentNum = other.commentNum;
    comments = new Comment[commentCapacity];
    for (size_t i = 0; i < commentNum && i < commentCapacity; i++) {
        comments[i] = other.comments[i];
    }
    commentID = other.commentID;
}

/**
 * @brief Resizes the comments array to accommodate more comments.
 */
void Discussion::resizeComments() {
    commentCapacity *= 2;
    Comment* newArr = new Comment[commentCapacity];
    for (size_t i = 0; i < commentNum; i++) {
        newArr[i] = comments[i];
    }
    delete[] comments;
    comments = newArr;
}

/**
 * @brief Constructs a new Discussion object with the given details.
 *
 * @param title The title of the discussion.
 * @param contents The content of the discussion.
 * @param creatorId Discussion creator ID.
 * @param discussionId Unique discussion ID.
 */
Discussion::Discussion(const std::string& title, const std::string& contents, unsigned int creatorId, unsigned int discussionId) : commentCapacity(2) {
    setDiscussionTitle(title);
    setDiscussionContents(contents);
    setDiscussionCreatorId(creatorId);
    id = discussionId;

    comments = new Comment[commentCapacity];
    commentNum = 0;
    commentID = 0;
}

/**
 * @brief Default constructor for the Discussion class.
 */
Discussion::Discussion() : Discussion("", "", 0, 0) {  }

/**
 * @brief Copy constructor for the Discussion class.
 *
 * @param other The discussion to be copied.
 */
Discussion::Discussion(const Discussion& other) {
    copyFrom(other);
}

/**
 * @brief Assignment operator for the Discussion class.
 *
 * @param other The discussion that will be assigned.
 * @return Reference to the assigned discussion.
 */
Discussion& Discussion::operator=(const Discussion& other) {
    if (this != &other) {
        delete[] comments;
        copyFrom(other);
    }
    return *this;
}

/**
 * @brief Destructor for the Discussion class.
 */
Discussion::~Discussion() {
    delete[] comments;
}

/**
 * @brief Sets the title of the discussion.
 *
 * @param title The new title.
 */
void Discussion::setDiscussionTitle(const std::string& title) {
    this->title = title;
}

/**
 * @brief Sets the content of the discussion.
 *
 * @param contents The new content.
 */
void Discussion::setDiscussionContents(const std::string& contents) {
    this->contents = contents;
}

/**
 * @brief Sets the ID of the discussion creator.
 *
 * @param creatorId The new creator ID.
 */
void Discussion::setDiscussionCreatorId(unsigned int creatorId) {
    this->creatorId = creatorId;
}

/**
 * @brief Returns the title of the discussion.
 *
 * @return The title of the discussion.
 */
std::string Discussion::getDiscussionTitle() const {
    return title;
}

/**
 * @brief Returns the content of the discussion.
 *
 * @return The content of the discussion.
 */
std::string Discussion::getDiscussionContents() const {
    return contents;
}

/**
 * @brief Returns the ID of the discussion creator.
 *
 * @return Discussion creator ID.
 */
unsigned int Discussion::getDiscussionCreatorId() const {
    return creatorId;
}

/**
 * @brief Returns the unique discussion ID.
 *
 * @return The unique discussion ID.
 */
unsigned int Discussion::getDiscussionId() const {
    return id;
}

/**
 * @brief Returns the number of comments in the discussion.
 *
 * @return The number of comments in the discussion.
 */
unsigned int Discussion::getCommentNum() const {
    return commentNum;
}

/**
 * @brief Returns the unique ID for the comments in the discussion.
 *
 * @return The unique ID for comments in the discussion.
 */
unsigned int Discussion::getCommentID() const {
    return commentID;
}

/**
 * @brief Returns the array of comments in the discussion.
 *
 * @return Pointer to the comments array.
 */
Comment* Discussion::getDiscussionComments() const {
    return comments;
}

/**
 * @brief Adds a new comment to the discussion.
 *
 * @param authorId The ID of the author of the comment.
 */
void Discussion::addComment(unsigned int authorId) {
    std::string buff;
    std::cout << ">Enter a comment: ";
    std::getline(std::cin, buff);

    Comment newComment(buff, authorId, commentID);
    comments[commentNum] = newComment;
    commentNum++;

    if (commentNum >= commentCapacity) {
        resizeComments();
    }
}

/**
 * @brief Adds a reply to an existing comment.
 *
 * @param authorId Reply author ID.
 * @param commentId The ID of the comment to which the reply is being added to.
 */
void Discussion::commentReply(unsigned int authorId, unsigned int commentId) {
    std::string buff;
    std::cout << ">Enter the reply: ";
    std::getline(std::cin, buff);
    comments[commentId].addReply(buff, authorId);
}

/**
 * @brief Vote for a comment.
 *
 * @param curUserId Current user ID.
 * @param commentId Comment ID being voted on.
 */
void Discussion::commentVote(unsigned int curUserId, unsigned int commentId) {
    if (comments[commentId].DidUserAlreadyVote(curUserId)) {
        std::cout << ">You have already voted!\n";
        return;
    }
    char vote;
    std::cout << ">Upvote or downvote a comment(U/D): ";
    std::cin >> vote;

    while (vote != 'U' && vote != 'u' && vote != 'D' && vote != 'd') {
        std::cout << ">No such vote exists! Enter a new vote(U/D): ";
        std::cin >> vote;
    }

    if (vote == 'u') { vote = 'U'; }
    if (vote == 'd') { vote = 'D'; }

    if (vote == 'U') {
        comments[commentId].commentRatingIncrement(curUserId);
        // changing the user rating in main
        return;
    }
    comments[commentId].commentRatingDecrement(curUserId);
    // changing the user rating in main
}

/**
 * @brief Removes comment from discussion.
 *
 * @param curUserId Current user ID.
 * @param commentId The ID of the comment to be removed.
 * @param curUserPermission Current user permission.
 */
void Discussion::removeComment(unsigned int curUserId, unsigned int commentId, Permission curUserPermission) {
    if (comments[commentId].getAuthorId() != curUserId && curUserPermission != Permission::MOD) {
        std::cout << ">Access denied!\n";
        return;
    }

    for (size_t i = 0; i < commentNum; i++) {
        if (comments[i].getCommentId() < commentId) {
            continue;
        }
        comments[i] = comments[i + 1];
    }
    commentNum--;
    // changing the user rating in main
}

/**
 * @brief Lists all comments in the discussion.
 */
void Discussion::listComments() const {
    std::cout << ">Comments: \n\t";
    for (size_t i = 0; i < commentNum; i++) {
        comments[i].printCommentAndReplies();
    }
}

/**
 * @brief Saves discussion data to a file.
 *
 * @param of The output file stream.
 */
void Discussion::writeToFile(std::ofstream& of) {
    unsigned int size = title.size();
    of.write(reinterpret_cast<const char*>(&size), sizeof(size));
    of.write((const char*)&title[0], size);

    size = contents.size();
    of.write(reinterpret_cast<const char*>(&size), sizeof(size));
    of.write((const char*)&contents[0], size);

    of.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
    of.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // starts recording comment data
    of.write(reinterpret_cast<const char*>(&commentNum), sizeof(commentNum));
    of.write(reinterpret_cast<const char*>(&commentID), sizeof(commentID));

    // the comments continue...
}

/**
 * @brief Reads discussion data from a file.
 *
 * @param iff The input file stream.
 */
void Discussion::readFromFile(std::ifstream& iff) {
    unsigned int size = 0;
    iff.read(reinterpret_cast<char*>(&size), sizeof(size));
    title.resize(size);
    iff.read((char*)&title[0], size);

    iff.read(reinterpret_cast<char*>(&size), sizeof(size));
    contents.resize(size);
    iff.read((char*)&contents[0], size);

    iff.read(reinterpret_cast<char*>(&creatorId), sizeof(creatorId));
    iff.read(reinterpret_cast<char*>(&id), sizeof(id));

    iff.read(reinterpret_cast<char*>(&commentNum), sizeof(commentNum));
    iff.read(reinterpret_cast<char*>(&commentID), sizeof(commentID));

    while (commentCapacity <= commentNum) {
        resizeComments();
    }
    // information about comments...
}
