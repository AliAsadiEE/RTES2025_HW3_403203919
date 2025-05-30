#!/bin/bash

# مسیر FIFO
FIFO_PATH="/tmp/myfifo"

# اگر FIFO وجود نداشت، بساز
if [[ ! -p $FIFO_PATH ]]; then
    mkfifo $FIFO_PATH
fi

echo "Reader started. Waiting for messages..."

# خواندن از FIFO و نمایش روی ترمینال
while true; do
    if read line < $FIFO_PATH; then
        echo "Received: $line"
    fi
done
