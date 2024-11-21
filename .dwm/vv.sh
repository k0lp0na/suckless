#!/bin/bash

function get_brightness {
  xbacklight -get | sed 's/[.].*//g'
}

function send_notification {
    DIR=`dirname "$0"`
    bright=`get_brightness`
    # Make the bar with the special character ─ (it's not dash -)
    # https://en.wikipedia.org/wiki/Box-drawing_character
#bar=$(seq -s "─" $(($bright/5)) | sed 's/[0-9]//g')
    if [ "$bright" = "0" ]; then
      icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/contrast.svg"
$DIR/notify-send.sh "$bright""      " -i "$icon_name" -t 2000 -h int:value:"$bright" -h string:synchronous:"─" --replace=555
      else
	      if [  "$bright" -lt "10" ]; then
	        icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/contrast.svg"
$DIR/notify-send.sh "$bright""     " -i "$icon_name" --replace=555 -t 2000
      else
        if [ "$bright" -lt "30" ]; then
          icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/contrast.svg"
        else
          if [ "$bright" -lt "70" ]; then
            icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/contrast.svg"
          else
            icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/contrast.svg"
        fi
    fi
  fi
fi
bar=$(seq -s "─" $(($bright/5)) | sed 's/[0-9]//g')
# Send the notification
$DIR/notify-send.sh "$bright""     ""$bar" -i "$icon_name" -t 2000 -h int:value:"$bright" -h string:synchronous:"$bar" --replace=555
}

case $1 in
  up)
    xbacklight -inc 5
    send_notification
    ;;
  down)
    xbacklight -dec 5
    send_notification
    ;;
esac
