#include <iostream>
#include "System.h"

//Within this project, a console application should be implemented,
//which resembles a social network. In the social network, users can ask
//questions of different nature, which are grouped by topics.
//All data about the network should be stored in files (save, save as commands)
//and loaded when the program is started (open command). If there are no valid files,
//it starts with empty data. You have the freedom to determine the format of the files yourself,
//but you must describe this format, as well as ensure the correctness of the input.

int main() {
	System socialNetwork;
	std::string command;

	std::cout << ">Welcome! Enter command: ";
	do {
		std::cin >> command;
		if (command == "save") {
			socialNetwork.save();
		}
		else if (command == "save_as") {
			std::string fileName;
			std::cout << ">>Enter file name: ";
			std::cin.clear();
			std::cin.ignore();
			std::getline(std::cin, fileName, '\n');
			socialNetwork.saveAs(fileName);
		}
		else if (command == "load") {
			std::string fileName;
			std::cout << ">>Enter file name: ";
			std::cin.clear();
			std::cin.ignore();
			std::getline(std::cin, fileName, '\n');
			socialNetwork.load(fileName);
		}
		else if (command == "signup") {
			socialNetwork.signup();
		}
		else if (command == "login") {
			std::string nickname, password;
			std::cout << ">>Enter nickname: ";
			std::cin >> nickname;
			std::cout << ">>Enter password: ";
			std::cin >> password;
			socialNetwork.login(nickname, password);
		}
		else if (command == "edit") {
			socialNetwork.editUser();
		}
		else if (command == "create") {
			std::string title, description;
			std::cout << ">>Enter the title of the topic: ";
			std::cin.clear();
			std::cin.ignore();
			std::getline(std::cin, title, '\n');
			std::cout << ">>Enter the description of the topic: ";
			std::cin.clear();
			std::getline(std::cin, description, '\n');
			socialNetwork.createTopic(title, description);
		}
		else if (command == "search") {
			std::string topicSubStr;
			std::cout << ">>Enter key word/phrase: ";
			std::cin.clear();
			std::cin.ignore();
			std::getline(std::cin, topicSubStr);
			socialNetwork.searchTopic(topicSubStr);
		}
		else if (command == "open") {
			std::string buff;
			std::cout << ">>Open by id or by full title? (Id/title)" << std::endl;
			std::cin >> buff;
			if (buff == "id" || buff == "Id" || buff == "ID") {
				unsigned int topicId;
				std::cout << ">>Enter Id: ";
				std::cin >> topicId;
				socialNetwork.openTopic(topicId);
			}
			else {
				std::string topicTitle;
				std::cout << ">>Enter full title: ";
				std::cin.clear();
				std::cin.ignore();
				std::getline(std::cin, topicTitle);
				socialNetwork.openTopic(topicTitle);
			}
		}
		else if (command == "list") {
			socialNetwork.listDiscussions();
		}
		else if (command == "post") {
			std::string title, contents;
			std::cout << ">>Enter discussion's title: ";
			std::cin.clear();
			std::cin.ignore();
			std::getline(std::cin, title);
			std::cout << ">>Enter discussion's contents: ";
			std::cin.clear();
			std::getline(std::cin, contents);
			socialNetwork.postDiscussion(title, contents);
		}
		else if (command == "post_open") {
			unsigned int discussionId;
			std::cout << ">>Enter discussion id: ";
			std::cin >> discussionId;
			socialNetwork.openDiscussion(discussionId);
		}
		else if (command == "post_quit") {
			socialNetwork.quitDiscussion();
		}
		else if (command == "quit") {
			socialNetwork.quitTopic();
		}
		else if (command == "remove_post") {
			unsigned int postId;
			std::cout << ">>Enter the post's id: ";
			std::cin >> postId;
			socialNetwork.removeDiscussion(postId);
		}
		else if (command == "remove_topic") {
			unsigned int topicId;
			std::cout << ">>Enter the topic's id: ";
			std::cin >> topicId;
			socialNetwork.removeTopic(topicId);
		}
		else if (command == "add_comment") {
			socialNetwork.addComment();
		}
		else if (command == "add_reply") {
			unsigned int commentId;
			std::cout << ">>Enter comment's id: ";
			std::cin >> commentId;
			socialNetwork.addReply(commentId);
		}
		else if (command == "comment_vote") {
			unsigned int commentId;
			std::cout << ">>Enter comment's id: ";
			std::cin >> commentId;
			socialNetwork.commentVote(commentId);
		}
		else if (command == "remove_comment") {
			unsigned int commentId;
			std::cout << ">>Enter comment's id: ";
			std::cin >> commentId;
			socialNetwork.removeComment(commentId);
		}
		else if (command == "list_comments") {
			socialNetwork.listComments();
		}
		else if (command == "logout") {
			socialNetwork.logout();
		}
		else if (command == "help") {
			std::cout << ">>All commands: save, save_as, load, signup, login, logout, edit, create, search, open, quit,\n" <<
				"list, post, post_open, post_quit, add_comment, add_reply, comment_vote, list_comments, remove_topic,\n" <<
				"remove_post, remove_comment, help, exit." << std::endl;
		}
		else if (command == "exit") {
			char answer;
			std::cout << ">>Do you want to save the changes? (Y/N)\n";
			std::cin >> answer;
			if (answer == 'Y' || answer == 'y') {
				socialNetwork.save();
			}
			else {
				std::cout << ">>The changes were not saved!" << std::endl;
			}
		}
		else {
			std::cout << ">>No such command exist! Use command \'help\' to see all commands.";
		}
		socialNetwork.calculateUserPoints();
		std::cout << "\n>";
	} while (command != "exit");
	//thank you, come again
}
