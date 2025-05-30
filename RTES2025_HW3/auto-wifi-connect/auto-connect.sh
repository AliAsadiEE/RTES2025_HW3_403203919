#!/bin/bash

LOG_FILE="/root/auto-connect.log"
SSID="Ali"
PASSWORD="aIi1379!#(aSadI"

echo "----------------------------------------" >> $LOG_FILE
echo "----- $(date) -----" >> $LOG_FILE

# بررسی اینکه NetworkManager در حال اجرا هست یا نه
if ! pgrep -x "NetworkManager" > /dev/null; then
    echo "Error: NetworkManager is not running." >> $LOG_FILE
    echo "----------------------------------------" >> $LOG_FILE
    exit 1
fi

# فعال‌سازی کارت وای‌فای و آماده‌سازی برای اسکن
nmcli radio wifi on
ip link set wlan0 up
sleep 2

# اسکن شبکه‌های وای‌فای اطراف
echo "Scanning available Wi-Fi networks..." >> $LOG_FILE
nmcli device wifi rescan
sleep 2
nmcli device wifi list >> $LOG_FILE

# بررسی اتصال فعلی
CONNECTED_SSID=$(nmcli -t -f active,ssid dev wifi | grep '^yes' | cut -d':' -f2)

if [ "$CONNECTED_SSID" = "$SSID" ]; then
    echo "Already connected to $SSID" >> $LOG_FILE
else
    echo "Not connected to $SSID. Trying to connect..." >> $LOG_FILE
    nmcli device wifi connect "$SSID" password "$PASSWORD" >> $LOG_FILE 2>&1

    # بررسی نتیجه اتصال
    NEW_CONNECTED_SSID=$(nmcli -t -f active,ssid dev wifi | grep '^yes' | cut -d':' -f2)
    if [ "$NEW_CONNECTED_SSID" = "$SSID" ]; then
        echo "Successfully connected to $SSID" >> $LOG_FILE
    else
        echo "Failed to connect to $SSID" >> $LOG_FILE
    fi
fi

echo "----------------------------------------" >> $LOG_FILE
