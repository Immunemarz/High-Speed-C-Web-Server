# Login request with userid 'bob' and password 'csrocks55'
curl --output - 'http://127.0.0.1:8000/login?userid=bob&password=csrocks55'

# Login request with userid 'bob' and password 'csrock66'
curl --output - 'http://127.0.0.1:8000/login?userid=bob&password=csrock66'

# List request
curl --output - 'http://127.0.0.1:8000/list'

# Get request with id 1
curl --output - 'http://127.0.0.1:8000/get?id=1'

# Get request with id 4242
curl --output - 'http://127.0.0.1:8000/get?id=4242'

# Posting request with author 'bob', subject 'Computer Networks Rocks', and a message
curl --output - 'http://127.0.0.1:8000/posting?author=bob&subject=Computer%20Networks%20Rocks&message=It%20is%20so%20so%20cool.%20%20All%20the%20glue%20that%20holds%20technology%20together.%20%20Computer%20Networks%20you%20are%20my%20friend.'
