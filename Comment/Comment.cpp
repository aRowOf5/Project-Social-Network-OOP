#include "Comment.h"

/**
 * @brief Increases the capacity of the array of voted users.
 */
void Comment::resizeVotedUsers() {
    votedUsersCapacity *= 2;
    unsigned int* newArr = new unsigned int[votedUsersCapacity];
    for (size_t i = 0; i < votedUsersNum; i++) {
        newArr[i] = votedUsers[i];
    }
    delete[] votedUsers;
    votedUsers = newArr;
}

/**
 * @brief Sorts the array of voted users using insertion method.
 */
void Comment::sortVotedUsers() {
    int key;
    int j;
    for (int i = 1; i < votedUsersNum; i++) {
        key = votedUsers[i];
        j = i - 1;
        while (j >= 0 && votedUsers[j] > key) {
            votedUsers[j + 1] = votedUsers[j];
            j--;
        }
        votedUsers[j + 1] = key;
    }
}

/**
 * @brief Constructor with parameters.
 * @param comment Comment text.
 * @param authorId Comment author ID.
 * @param commentId Unique comment identifier.
 */
Comment::Comment(const std::string& comment, unsigned int authorId, unsigned int commentId) : votedUsersCapacity(2) {
    setCommentText(comment);
    setAuthorId(authorId);
    id = commentId;
    commentRating = 0;

    votedUsers = new unsigned int[votedUsersCapacity];
    votedUsersNum = 0;

    replyNum = 0;
}

/**
 * @brief Default constructor.
 */
Comment::Comment() : commentText(""), authorId(0), id(0), commentRating(0), votedUsersCapacity(2), votedUsersNum(0), replyNum(0) {
    votedUsers = new unsigned int[votedUsersCapacity];
}

/**
 * @brief Sets the comment text.
 * @param text The new comment text.
 */
void Comment::setCommentText(const std::string& text) {
    commentText = text;
}

/**
 * @brief Sets the ID of the author of the comment.
 * @param authorId Author ID.
 */
void Comment::setAuthorId(unsigned int authorId) {
    this->authorId = authorId;
}

/**
 * @brief Adds a reply to the comment.
 * @param replyText Reply text.
 * @param authorId Reply author ID.
 */
void Comment::addReply(const std::string& replyText, unsigned int authorId) {
    replies.emplace_back(replyText, authorId, replyNum++);
}

/**
 * @brief Returns the comment text.
 * @return Comment text.
 */
std::string Comment::getCommentText() const {
    return commentText;
}

/**
 * @brief Returns the comment author ID.
 * @return Author ID.
 */
unsigned int Comment::getAuthorId() const {
    return authorId;
}

/**
 * @brief Returns the unique comment identifier.
 * @return Unique comment identifier.
 */
unsigned int Comment::getCommentId() const {
    return id;
}

/**
 * @brief Returns the comment rating.
 * @return Comment rating.
 */
int Comment::getCommentRating() const {
    return commentRating;
}

/**
 * @brief Returns the number of users who voted.
 * @return Number of users who voted.
 */
unsigned int Comment::getVotedUsersNum() const {
    return votedUsersNum;
}

/**
 * @brief Returns a pointer to the array of voted users.
 * @return Pointer to the array of voted users.
 */
const unsigned int* Comment::getVotedUsers() const {
    return votedUsers;
}

/**
 * @brief Returns the number of replies.
 * @return Number of replies.
 */
unsigned int Comment::getReplyNum() const {
    return replyNum;
}

/**
 * @brief Saves replies to a file.
 * @param of Output file stream.
 */
void Comment::writeRepliesToFile(std::ofstream& of) const {
    of.write(reinterpret_cast<const char*>(&replies[0]), replies.size() * sizeof(replies));
    /* read from file
        const size_t count = filesize / sizeof(T);
        std::vector<T> vec(count);
        strm.read(reinterpret_cast<char*>(&vec[0]), count*sizeof(T));
    */
}

/**
 * @brief Prints the comment and replies.
 */
void Comment::printCommentAndReplies() const {
    std::cout << "From user " << authorId << ": " << commentText << ", rating: " << commentRating << "{id: " << id << "}\n";
    for (const Comment& reply : replies) {
        std::cout << "   ";
        reply.printCommentAndReplies();
    }
}

/**
 * @brief Saves the comment to a file.
 * @param of Output file stream.
 */
void Comment::writeToFile(std::ofstream& of) {
    unsigned int size = commentText.size();
    of.write(reinterpret_cast<const char*>(&size), sizeof(size));
    of.write((const char*)&commentText[0], size);

    of.write(reinterpret_cast<const char*>(&authorId), sizeof(authorId));
    of.write(reinterpret_cast<const char*>(&id), sizeof(id));
    of.write(reinterpret_cast<const char*>(&commentRating), sizeof(commentRating));

    // information about users who have already voted on the comment
    of.write(reinterpret_cast<const char*>(&votedUsersNum), sizeof(votedUsersNum));
    of.write(reinterpret_cast<const char*>(votedUsers), sizeof(unsigned int) * votedUsersNum);

    of.write(reinterpret_cast<const char*>(&replyNum), sizeof(replyNum));
    writeRepliesToFile(of);
}

/**
 * @brief Reads the comment from a file.
 * @param iff Input file stream.
 */
void Comment::readFromFile(std::ifstream& iff) {
    unsigned int size = 0;
    iff.read(reinterpret_cast<char*>(&size), sizeof(size));
    commentText.resize(size);
    iff.read((char*)&commentText[0], size);

    iff.read(reinterpret_cast<char*>(&authorId), sizeof(authorId));
    iff.read(reinterpret_cast<char*>(&id), sizeof(id));
    iff.read(reinterpret_cast<char*>(&commentRating), sizeof(commentRating));

    iff.read(reinterpret_cast<char*>(&votedUsersNum), sizeof(votedUsersNum));
    while (votedUsersCapacity <= votedUsersNum) {
        resizeVotedUsers();
    }
    iff.read(reinterpret_cast<char*>(votedUsers), sizeof(unsigned int) * votedUsersNum);

    iff.read(reinterpret_cast<char*>(&replyNum), sizeof(replyNum));
    replies.resize(replyNum);
    iff.read(reinterpret_cast<char*>(&replies[0]), sizeof(replies) * replyNum);
}

/**
 * @brief Increases the rating of the comment from the current user.
 * @param currUserId Current user ID.
 */
void Comment::commentRatingIncrement(unsigned int currUserId) {
    commentRating++;

    votedUsers[votedUsersNum] = currUserId;
    votedUsersNum++;
    sortVotedUsers();
    if (votedUsersNum >= votedUsersCapacity) {
        resizeVotedUsers();
    }
}

/**
 * @brief Lowers the rating of the comment from the current user.
 * @param currUserId Current user ID.
 */
void Comment::commentRatingDecrement(unsigned int currUserId) {
    commentRating--;

    votedUsers[votedUsersNum] = currUserId;
    votedUsersNum++;
    sortVotedUsers();
    if (votedUsersNum >= votedUsersCapacity) {
        resizeVotedUsers();
    }
}

/**
 * @brief Checks if the user has already voted.
 * @param userId User ID.
 * @return Returns true if the user has already voted, otherwise false.
 */
bool Comment::DidUserAlreadyVote(unsigned int userId) {
    for (size_t i = 0; i < votedUsersNum; i++) {
        if (votedUsers[i] == userId) {
            return true;
        }
    }
    return false;
}
