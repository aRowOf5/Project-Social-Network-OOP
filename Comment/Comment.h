#pragma once
#include <vector>
#include "User.h"

/**
 * @class Comment
 * @brief Class that represents a comment with replies and rating.
 */
class Comment {
private:
    std::string commentText;  /**< Comment text. */
    unsigned int authorId;  /**< Comment author ID. */
    unsigned int id;  /**< Unique comment identifier. */
    int commentRating;  /**< Comment rating. */

    unsigned int* votedUsers;  /**< Array of users who voted on the comment. */
    unsigned int votedUsersCapacity;  /**< Capacity of the array of voting users. */
    unsigned int votedUsersNum;  /**< Number of users who voted. */

    std::vector<Comment> replies;  /**< Vector of replies to the comment. */
    unsigned int replyNum;  /**< Number of replies. */

    /**
     * @brief Increases the capacity of the array of voting users.
     */
    void resizeVotedUsers();

    /**
     * @brief Sorts the array of voted users.
     */
    void sortVotedUsers();

public:
    /**
     * @brief Constructor with parameters.
     * @param comment Comment text.
     * @param authorId Comment author ID.
     * @param commentId Unique comment identifier.
     */
    Comment(const std::string& comment, const unsigned int authorId, const unsigned int commentId);

    /**
     * @brief Default constructor.
     */
    Comment();

    /**
     * @brief Sets the comment text.
     * @param text The new comment text.
     */
    void setCommentText(const std::string& text);

    /**
     * @brief Sets the ID of the author of the comment.
     * @param authorId Author ID.
     */
    void setAuthorId(unsigned int authorId);

    /**
     * @brief Adds a reply to the comment.
     * @param replyText Reply text.
     * @param authorId Reply author ID.
     */
    void addReply(const std::string& replyText, unsigned int authorId);

    /**
     * @brief Returns the comment text.
     * @return The text of the comment.
     */
    std::string getCommentText() const;

    /**
     * @brief Returns the comment author ID.
     * @return Author ID.
     */
    unsigned int getAuthorId() const;

    /**
     * @brief Returns the unique comment identifier.
     * @return The unique comment identifier.
     */
    unsigned int getCommentId() const;

    /**
     * @brief Returns the comment rating.
     * @return Comment rating.
     */
    int getCommentRating() const;

    /**
     * @brief Returns the number of users who voted.
     * @return Number of users who voted.
     */
    unsigned int getVotedUsersNum() const;

    /**
     * @brief Returns a pointer to array of voted users.
     * @return Pointer of the array of voted users.
     */
    const unsigned int* getVotedUsers() const;

    /**
     * @brief Returns the number of replies.
     * @return Number of replies.
     */
    unsigned int getReplyNum() const;

    /**
     * @brief Saves replies to a file.
     * @param of Output file stream.
     */
    void writeRepliesToFile(std::ofstream& of) const;

    /**
     * @brief Prints the comment and replies.
     */
    void printCommentAndReplies() const;

    /**
     * @brief Saves the comment to a file.
     * @param of Output file stream.
     */
    void writeToFile(std::ofstream& of);

    /**
     * @brief Reads the comment from a file.
     * @param iff Input file stream.
     */
    void readFromFile(std::ifstream& iff);

    /**
     * @brief Increases the rating of the comment from the current user.
     * @param currUserId Current user ID.
     */
    void commentRatingIncrement(unsigned int currUserId);

    /**
     * @brief Lowers the rating of the comment from the current user.
     * @param currUserId Current user ID.
     */
    void commentRatingDecrement(unsigned int currUserId);

    /**
     * @brief Checks if the user has already voted.
     * @param userId User ID.
     * @return Returns true if the user has already voted, otherwise false.
     */
    bool DidUserAlreadyVote(unsigned int userId);
};
