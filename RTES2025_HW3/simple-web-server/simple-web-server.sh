#!/bin/bash

PORT=80

while true; do
  echo "Waiting for connection on port $PORT..."

  {
    read request_line
    echo "Received request: $request_line"
    response="HTTP/1.1 200 OK\r
Content-Type: text/plain\r
Connection: close\r
\r
Current date and time: $(date)\r
"
    echo -e "$response"
  } | nc -l -p $PORT -q 1
done
