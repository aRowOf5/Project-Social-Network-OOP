# Project-Social-Network-OOP
## Description
This is a console-based social network application where users can ask and answer questions grouped by topics. The application supports user accounts, topic creation, question posting, commenting, and voting. All data is persisted in files and can be loaded when the application starts.

## Features

- ### User Management
  - User Registration (signup): Create a new account with first name, last name, username, and password
  - Login (login): Authenticate with username and password
  - Profile Editing (edit): Modify personal information (names and password)
  - Moderator Privileges: First registered user becomes a moderator who can edit other accounts and change roles
- ### Topic Operations
  - Topic Creation (create): Create new topics with title and description
  - Topic Search (search): Find topics by partial title match
  - Topic Opening (open): View topic details and its questions
  - Topic Listing (list): Display all questions in an open topic
- ### Question Operations
  - Posting Questions (post): Add new questions to open topics
  - Viewing Questions (post_open): Display question details and comments
  - Commenting: Add comments and replies to questions
  - Voting: Upvote/downvote comments (each user can vote once per comment)
  - Moderation: Moderators can remove questions or entire topics

## Data Persistence
All network data is stored in files:
  - Automatic saving on application exit (exit command)
  - Manual saving (save and save as commands)
  - Automatic loading at startup if valid files exist
## Usage Examples
- ### User Registration
text
> signup
Username: john_doe
Password: ********
First Name: John
Last Name: Doe
 
- ### Topic Operations
text
> search programming
>> Advanced Programming {id: 1}
>> Programming Basics {id: 2}

> open 1
Welcome to "Advanced Programming"

> list
What are design patterns? {id: 101}
How to implement polymorphism? {id: 102}

- ### Question Interaction
text
> post_open 101
Title: What are design patterns?
Content: Can someone explain design patterns in simple terms?
Comments: 3

> comment
This is a fundamental concept in OOP...
Comment posted successfully!

> upvote 45
Vote recorded!

## Technical Details
- User Attributes:
  - First name, last name
  - Unique username
  - Password
  - Unique numeric ID
  - Points (reputation)
- Topic Attributes:
  - Title
  - Creator ID
  - Description
  - Unique topic ID
- Question Attributes:
  - Title
  - Content
  - Author ID
  - Unique question ID
- Comment Attributes:
  - Author
  - Content
  - Score (sum of votes)
  - Unique comment ID within question
  - 
## Requirements
- C++ compiler supporting standard libraries
- File system access for data persistence

## Notes
- The first registered user automatically becomes a moderator
- Users can only edit their own accounts (except moderators)
- All data changes are persisted to files
- File format is custom and should be documented by implementers
