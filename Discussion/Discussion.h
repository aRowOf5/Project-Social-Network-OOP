#pragma once
#include "Comment.h"
#include <string>

/**
 * @class Discussion
 * @brief Represents a discussion consisting of a title, content, comments, and creator.
 */
class Discussion {
private:
    std::string title; /**< Discussion title. */
    std::string contents; /**< Discussion content. */
    unsigned int creatorId; /**< Discussion creator ID. */
    unsigned int id; /**< Unique discussion ID. */

    Comment* comments; /**< An array of comments to the discussion. */
    unsigned int commentCapacity; /**< Comment array capacity. */
    unsigned int commentNum; /**< Number of comments in the discussion. */
    unsigned int commentID; /**< Unique ID for comments within the discussion. */

    /**
     * @brief Copies data from another discussion.
     *
     * @param other The discussion from which data will be copied.
     */
    void copyFrom(const Discussion& other);

    /**
     * @brief Resizes the comments array to accommodate more comments.
     */
    void resizeComments();

public:
    /**
     * @brief Constructs a new Discussion object with the given details.
     *
     * @param title The title of the discussion.
     * @param contents The content of the discussion.
     * @param creatorId Discussion creator ID.
     * @param discussionId Unique discussion ID.
     */
    Discussion(const std::string& title, const std::string& contents, unsigned int creatorId, unsigned int discussionId);

    /**
     * @brief Default constructor for the Discussion class.
     */
    Discussion();

    /**
     * @brief Copy constructor for the Discussion class.
     *
     * @param other The discussion to be copied.
     */
    Discussion(const Discussion& other);

    /**
     * @brief Assignment operator for the Discussion class.
     *
     * @param other The discussion that will be assigned.
     * @return Reference to the assigned discussion.
     */
    Discussion& operator=(const Discussion& other);

    /**
     * @brief Destructor for the Discussion class.
     */
    ~Discussion();

    /**
     * @brief Sets the title of the discussion.
     *
     * @param title The new title.
     */
    void setDiscussionTitle(const std::string& title);

    /**
     * @brief Sets the content of the discussion.
     *
     * @param contents The new content.
     */
    void setDiscussionContents(const std::string& contents);

    /**
     * @brief Sets the ID of the discussion creator.
     *
     * @param creatorId The new creator ID.
     */
    void setDiscussionCreatorId(unsigned int creatorId);

    /**
     * @brief Returns the title of the discussion.
     *
     * @return The title of the discussion.
     */
    std::string getDiscussionTitle() const;

    /**
     * @brief Returns the content of the discussion.
     *
     * @return The content of the discussion.
     */
    std::string getDiscussionContents() const;

    /**
     * @brief Returns the ID of the discussion creator.
     *
     * @return Discussion creator ID.
     */
    unsigned int getDiscussionCreatorId() const;

    /**
     * @brief Returns the unique discussion ID.
     *
     * @return The unique discussion ID.
     */
    unsigned int getDiscussionId() const;

    /**
     * @brief Returns the number of comments in the discussion.
     *
     * @return The number of comments in the discussion.
     */
    unsigned int getCommentNum() const;

    /**
     * @brief Returns the unique ID for the comments in the discussion.
     *
     * @return The unique ID for comments in the discussion.
     */
    unsigned int getCommentID() const;

    /**
     * @brief Returns the array of comments in the discussion.
     *
     * @return Pointer to the comments array.
     */
    Comment* getDiscussionComments() const;

    //topics[id].discussions[id].<command>

    /**
     * @brief Adds a new comment to the discussion.
     *
     * @param authorId The ID of the author of the comment.
     */
    void addComment(unsigned int authorId);

    /**
     * @brief Adds a reply to an existing comment.
     *
     * @param authorId Reply author ID.
     * @param commentId The ID of the comment to which the reply is being added to.
     */
    void commentReply(unsigned int authorId, unsigned int commentId);

    /**
     * @brief Vote for a comment.
     *
     * @param curUserId Current user ID.
     * @param commentId Comment ID being voted on.
     */
    void commentVote(unsigned int curUserId, unsigned int commentId);

    /**
     * @brief Removes comment from discussion.
     *
     * @param curUserId Current user ID.
     * @param commentId The ID of the comment to be removed.
     * @param curUserPermission Current user permission.
     */
    void removeComment(unsigned int curUserId, unsigned int commentId, Permission curUserPermission);

    /**
     * @brief Lists all comments in the discussion.
     */
    void listComments() const;

    /**
     * @brief Saves discussion data to a file.
     *
     * @param of The output file stream.
     */
    void writeToFile(std::ofstream& of);

    /**
     * @brief Reads discussion data from a file.
     *
     * @param iff The input file stream.
     */
    void readFromFile(std::ifstream& iff);
};
