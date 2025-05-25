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

using namespace std;

int main(void)
{
	string url = "GET /get?id=1 HTTP/1.1 Host: orangeexhibit-sonataspain-8000.codio.io X-Codio-Host: orangeexhibit-sonataspain.codio.io Connection: upgrade X-Forwarded-For: 204.144.15.30 X-Forwarded Proto: https X-Forwarded-Port: 443 X-Amzn-Trace-Id: Root=1-65453470-795ebbcd44f8e3384dbeac2a sec-ch-ua: \"Chromium\";v=\"118\", \"Google Chrome\";v=\"118\", \"Not=A?Brand\";v=\"99\" sec-ch-ua-mobile: ?0 sec-ch-ua-platform: \"Windows\" upgrade-insecure-requests: 1 user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.0.0 Safari/537.36 accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7 sec-fetch-site: none sec-fetch-mode: navigate sec-fetch-user: ?1 sec-fetch-dest: document accept-encoding: gzip, deflate, br accept-language: en-US,en;q=0.9,sv;q=0.8 cookie: dynamic_preview_session=7f849631-4a9b-46c4-a03b-10a1fa05e700; AWSALB=yvCCaqVkRNUYK1K88Z/KuGss/qal8xxVpJBZ0I8SIuW+e1UTuxbs/yVQTeSpHz2aZPrybwpZEcWRKUxk0HEalz0Uu43E6oaoYNgj/nOMacSV0jglLRio0P1WaY4f; AWSALBCORS=yvCCaqVkRNUYK1K88Z/KuGss/qal8xxVpJBZ0I8SIuW+e1UTuxbs/yVQTeSpHz2aZPrybwpZEcWRKUxk0HEalz0Uu43E6oaoYNgj/nOMacSV0jglLRio0P1WaY4";
		//do this with the get string as well
		/*string url = "GET /list HTTP/1.1
Host: orangeexhibit-sonataspain-8000.codio.io
X-Codio-Host: orangeexhibit-sonataspain.codio.io
Connection: upgrade
X-Forwarded-For: 204.144.15.30
X-Forwarded-Proto: https
X-Forwarded-Port: 443
X-Amzn-Trace-Id: Root=1-65452a70-0f0a1aa272308bc31d1749b5
sec-ch-ua: \"Chromium\";v=\"118\", \"Google Chrome\";v=\"118\", \"Not=A?Brand\";v=\"99\"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: \"Windows\"
upgrade-insecure-requests: 1
user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/118.0.0.0 Safari/537.36
accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*;q=0.8,application/signed-exchange;v=b3;q=0.7
sec-fetch-site: none
sec-fetch-mode: navigate
sec-fetch-user: ?1
sec-fetch-dest: document
accept-encoding: gzip, deflate, br
accept-language: en-US,en;q=0.9,sv;q=0.8
cookie: dynamic_preview_session=7f849631-4a9b-46c4-a03b-10a1fa05e700; AWSALB=KNEQdJ7MhYUTPuQJvzoHqo1NLvY/QLMJaz7m0TmbmPq/g8qvFSdZKoQAMFSt/c+P8ehQEtLpFgZCwpEtsnhPIR6osE1AuC2JSR4X5EmhUqWPmgCT5KRekvCbV8uC; AWSALBCORS=KNEQdJ7MhYUTPuQJvzoHqo1NLvY/QLMJaz7m0TmbmPq/g8qvFSdZKoQAMFSt/c+P8ehQEtLpFgZCwpEtsnhPIR6osE1AuC2JSR4X5EmhUqWPmgCT5KRekvCbV8uC*/
    
    // regular expression to match everything after the last / i think(from chatgpt)

    regex reg("GET (/[^?]*)\\? HTTP");
    smatch match;
		string theMatch;
    if (regex_search(url, match, reg)) {
        if (match.size() > 1) {
            theMatch = match.str(1);
        }
    }

		cout << theMatch << endl;

}