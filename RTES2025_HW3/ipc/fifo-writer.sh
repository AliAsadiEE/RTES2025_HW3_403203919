#!/bin/bash

# مسیر FIFO
FIFO_PATH="/tmp/myfifo"

# اگر FIFO وجود نداشت، بساز
if [[ ! -p $FIFO_PATH ]]; then
    mkfifo $FIFO_PATH
fi

echo "Writer started. Type messages below:"

# خواندن از ترمینال و نوشتن در FIFO
while true; do
    read input
    echo "$input" > $FIFO_PATH
done
