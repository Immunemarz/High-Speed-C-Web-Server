#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <regex>
#include <serializer.h>
#include <books.h>

using namespace std;

const string user = "bob";
const string pass = "csrocks55";
bool loginBool = false;

	vector<string> split(const string &s, char delimiter) {
			vector<string> tokens;
			string token;
			istringstream tokenStream(s);
			while (getline(tokenStream, token, delimiter)) {
					tokens.push_back(token);
			}
			return tokens;
		}



int main(void)
{
	// Create socket
	int s = socket(PF_INET, SOCK_STREAM, 0);

	if (s <= 0)
	{
		cerr << "server:main(): Socket creation failed." << endl;
		return -1;
	}

	// Do the bind a PORT to the socket
	sockaddr_in address;
	int addressSize = sizeof(sockaddr);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port  = htons(8000); // <---------------- port is 8000

	int status = bind(s, (struct sockaddr*) &address, addressSize);
	// Create a buffer to put messages in
	const int BUFFER_SIZE = 10000;
	char buffer[BUFFER_SIZE];

	do
	{
		// Wait for client to connect using listen
		cout << "server: Waiting for client to connect..." << endl;
		listen(s,3); // up to 3 clients can connect

		// Accept returns a NEW socket for the client we will talk to
		int cs = accept(s, (struct sockaddr*) &address, (socklen_t *) &addressSize);
		cout << "server: Server and client established communication." << endl;

		// receive message from client!
		cout << "server: Waiting for client message." << endl;
		int size = recv(cs, buffer, BUFFER_SIZE, 0);
		for (int i=0; i<size; i++)
		{
		
			cout << buffer[i];
			cout.flush();
		}
		if(loginBool == false)
		{
		string url = buffer;

		regex regexPattern("GET (.*)HTTP"); // this just gets everything in the buffer from the get to the http
    smatch match;
		string theMatch;
    if (regex_search(url, match, regexPattern)) {
        if (match.size() > 1) {
            theMatch = match.str(1);
        }
    }

		cout << "the regex match is: \n" << theMatch <<endl;
		
		theMatch.erase(remove(theMatch.begin(), theMatch.end(), ' '), theMatch.end()); //i used the internet here. Realized after maybe an hour of trying to finally realize my string has whitespace. This will remove that whitespace and now it works.
		string firstThree = theMatch.substr(0, 3);
		firstThree.erase(remove(firstThree.begin(), firstThree.end(), ' '), firstThree.end());

		if(firstThree != "/lo")
		{
				cout << "the login information was wrong!!" << endl;
				string fourOhOneResponse = "HTTP/1.1 401 Unauthorized\n"+string("")+
											"Content-Length: 0\n"+string("")+
											"\n";
				strcpy(buffer,fourOhOneResponse.c_str());	
				loginBool = false;	
		}


		else
		{


		
		regex pattern("userid=([a-zA-Z0-9]+)&password=([a-zA-Z0-9]+)");

    smatch matches;
    if (regex_search(url, matches, pattern)) {
        if (matches.size() == 3) {
            string userid = matches[1].str();
            string password = matches[2].str();

            cout << "UserID: " << userid << endl;
            cout << "Password: " << password << endl;

						if(userid == user && password == pass)
						{
									string response = "HTTP/1.1 200 OK\n" + string("") +
                      "Content-Type: text/html\n" + string("") +
                      "Content-Length: 59\n" + string("") +
                      "\n" + string("") +
    /* 7 */           "<html>\n" + string("") +
    /* 7 */           "<body>\n" + string("") +
    /*30 */           "   <h1>Login Successful!</h1>\n" + string("") +
    /* 8 */           "</body>\n" + string("") +
    /* 7 */           "</html>";

									strcpy(buffer,response.c_str());

									loginBool = true;
						}
						else
						{	
									cout << "the login information was wrong!!" << endl;
									string fourOhOneResponse = "HTTP/1.1 401 Unauthorized\n"+string("")+
                               "Content-Length: 0\n"+string("")+
                               "\n";
								  strcpy(buffer,fourOhOneResponse.c_str());	
									loginBool = false;						
						}


        }
		}

		}
		}
		else{


		//cout << "out of while loop!!!:" << buffer << "end buffer" << endl;
	
		string url = buffer;

		
    // regular expression to match everything after the last / i think(from chatgpt)
    regex regexPattern("GET (.*)HTTP"); // this just gets everything in the buffer from the get to the http
    smatch match;
		string theMatch;
    if (regex_search(url, match, regexPattern)) {
        if (match.size() > 1) {
            theMatch = match.str(1);
        }
    }

		cout << "the regex match is: \n" << theMatch <<endl;
		
		theMatch.erase(remove(theMatch.begin(), theMatch.end(), ' '), theMatch.end()); //i used the internet here. Realized after maybe an hour of trying to finally realize my string has whitespace. This will remove that whitespace and now it works.
		string firstThree = theMatch.substr(0, 3);
		firstThree.erase(remove(firstThree.begin(), firstThree.end(), ' '), firstThree.end());
		cout << "new theMatch == " << firstThree << endl;




		if(firstThree == "/li" || theMatch == "/list")
		{
			if(loginBool == false)
			{
				string fourOhOneResponse = "HTTP/1.1 401 Unauthorized\n"+string("")+
                              		 "Content-Length: 0\n"+string("")+
                               		 "\n";
				strcpy(buffer,fourOhOneResponse.c_str());	
			}
			else
			{
			ifstream file("books.txt");
			string line;
			vector<Book> books;

			while (getline(file, line)) {
					vector<string> tokens = split(line, ',');
					Book book;
					book.id = stoi(tokens[0]);//got stoi from internet converts string to int
					book.author = tokens[1]; 
					book.genre = tokens[2];  
					book.message = tokens[3];  
					books.push_back(book);
			}
			string response = "";
			string allBooksTogether ="";
			for(int i = 0; i < books.size(); ++i){

				allBooksTogether = allBooksTogether + "<br>" + "{" + "<br>" + "ID: " + to_string(books[i].id)+ "," + "<br>" + "Author: " + books[i].author + "<br>" + "Genre: " + books[i].genre + "<br>" + "Message: " + books[i].message  + "<br>" + "}," + "<br>";
				




				
			}
				response = "HTTP/1.1 200 OK\n" 
                  "Content-Type: text/html\n" 
                  "Content-Length: " + to_string(allBooksTogether.length() + 30) + "\n\n" 
                  "\n" 
                  "<html>\n" 
                  "<body>\n" 
                  "   <h1>" + allBooksTogether + "</h1>\n" 
                  "</body>\n" 
                  "</html>";
			strcpy(buffer,response.c_str());


			}
	}	
		

				//TODO finish this
				


		//	strcpy(buffer,response.c_str());
			
		


		if(firstThree == "/ge")
		{
			cout << "it is inside of GET!!" << endl;

			regex regexPattern("\\?(.*?) HTTP"); // this just gets everything in the buffer from the get to the http
    	smatch getMatch;
			string stringGetMatch;
    	if (regex_search(url, getMatch, regexPattern)) {
        if (getMatch.size() > 1) {
            stringGetMatch = getMatch.str(1);
        }

    	}

			string stringValue = stringGetMatch.substr(3);
			int idValue = stoi(stringValue);
			cout << idValue << " idvalue <- " << endl;
			
			ifstream file("books.txt");
			string line;
			vector<Book> books;
			int countOfLines = 0;
			while (getline(file, line)) {
					countOfLines++;
					vector<string> tokens = split(line, ',');
					Book book;
					book.id = stoi(tokens[0]);//got stoi from internet converts string to int
					book.author = tokens[1]; 
					book.genre = tokens[2];  
					book.message = tokens[3];  
					books.push_back(book);

					if(idValue == book.id)
					{
						string response = "";
						string allBooksTogether ="";
		
						allBooksTogether = allBooksTogether + "<br>" + "{" + "<br>" + "ID: " + to_string(book.id)+ "," + "<br>" + "Author: " + book.author + "<br>" + "Genre: " + book.genre + "<br>" + "Message: " + book.message  + "<br>" + "},";
						response = "HTTP/1.1 200 OK\n" 
                  "Content-Type: text/html\n" 
                  "Content-Length: " + to_string(allBooksTogether.length() + 30) + "\n\n" 
                  "\n" 
                  "<html>\n" 
                  "<body>\n" 
                  "   <h1>" + allBooksTogether + "</h1>\n" 
                  "</body>\n" 
                  "</html>";
						strcpy(buffer,response.c_str());
					}
					if(idValue > countOfLines || idValue < 0)
					{
						string fourOhOneResponse = "HTTP/1.1 404 Not Found\n"+string("")+
																			"Content-Length: 0\n"+string("")+
																			"\n";
						strcpy(buffer,fourOhOneResponse.c_str());						
					}



			}
			


		}//end if /ge

		if(firstThree == "/po")
		{

			regex regexPattern("author=([^&]+)&subject=([^&]+)&message=([^&]+) HTTP"); // this just gets everything in the buffer from the get to the http
    	smatch getMatch;
			string stringGetMatch;
    	if(regex_search(url, getMatch, regexPattern)) {
				string author = getMatch[1];
				string subject = getMatch[2];
				string genre = "NONE";
				string message = getMatch[3];
				//url is: posting?author=bob&subject=Computer%20Networks%20Rocks&message=It%20is%20so%20so%20cool.%20%20All%20the%20glue%20that%20holds%20technology%20together.%20%20Computer%20Networks%20you%20are%20my%20friend
				regex regexFor20("%20");
				smatch match20;
				string newSubject;
				string newMessage;
				newSubject = regex_replace(subject,regexFor20," ");
				newMessage = regex_replace(message,regexFor20," ");
				
				subject = newSubject;
				message = newMessage;


				cout << "author: " << author << " subject: " << subject << " genre: " << genre << " message: " << message << endl;  

				ifstream file("books.txt");
				string line;
				vector<Book> books;
				int countOfLinesToId = 0;
				while (getline(file, line)) {
					countOfLinesToId++;
				}





				string response = "";
				string allBooksTogether ="";

				allBooksTogether = allBooksTogether + "<br>" + "{" + "<br>" + "ID: " + to_string(countOfLinesToId + 1) + "," + "<br>" + "Author: " + author + "<br>" + "Subject: " + subject + "<br>" + "Genre: " + genre + "<br>" + "Message: " + message  + "<br>" + "},";
				response = "HTTP/1.1 200 OK\n" 
							"Content-Type: text/html\n" 
							"Content-Length: " + to_string(allBooksTogether.length() + 30) + "\n\n" 
							"\n" 
							"<html>\n" 
							"<body>\n" 
							"   <h1>" + allBooksTogether + "</h1>\n" 
							"</body>\n" 
							"</html>";

					strcpy(buffer,response.c_str());



					ofstream bookFile("books.txt",ios::app); //got ios::app from internet... appends data to existing file
					//5,"J.K. Rowling","Fantasy","The Harry Potter series follows a young wizard's journey through the magical world of Hogwarts."
					//id , author, genre, message
					if(bookFile.is_open())
					{
						bookFile << "\n" << countOfLinesToId + 1 << ",\"" << author << "\",\"" << genre << "\",\"" << message << "\"";
						bookFile.close();
					}

				}
		}

			if(firstThree == "/lo")
			{
				cout << "inside /lo" << endl;
				regex pattern("userid=([a-zA-Z0-9]+)&password=([a-zA-Z0-9]+)");
				
				smatch matches;
				if (regex_search(url, matches, pattern)) {
					if (matches.size() == 3) {
							string userid = matches[1].str();
							string password = matches[2].str();

							cout << "UserID: " << userid << endl;
							cout << "Password: " << password << endl;

							if(userid == user && password == pass)
							{
										string response = "HTTP/1.1 200 OK\n" + string("") +
												"Content-Type: text/html\n" + string("") +
												"Content-Length: 59\n" + string("") +
												"\n" + string("") +
			/* 7 */           "<html>\n" + string("") +
			/* 7 */           "<body>\n" + string("") +
			/*30 */           "   <h1>Login Successful!</h1>\n" + string("") +
			/* 8 */           "</body>\n" + string("") +
			/* 7 */           "</html>";

										strcpy(buffer,response.c_str());

										loginBool = true;
							}
							else
							{	
										cout << "the login information was wrong!!" << endl;
										string fourOhOneResponse = "HTTP/1.1 401 Unauthorized\n"+string("")+
																"Content-Length: 0\n"+string("")+
																"\n";
										strcpy(buffer,fourOhOneResponse.c_str());	
										loginBool = false;						
							}


					}
				}
			}







		

		}//end if(loginbool ==true)

		/* Payload size (stuff that isn't header information -> 59 bytes */
		
		send(cs,buffer,strlen(buffer)+1,0);
		close(cs);
	} while (true);
	close(s);

	return 1;
}