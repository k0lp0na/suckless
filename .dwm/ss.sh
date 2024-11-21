#!/bin/bash

function get_volume {
  pamixer --get-volume
}

function is_mute {
  pamixer --get-mute
}

# function is_audio_mute {
#   get_mute=`amixer set Capture toggle`
#   if [ $get_mute ]; then

#   fi
# }

function send_notification {
    DIR=`dirname "$0"`
    volume=`get_volume`
    # Make the bar with the special character ─ (it's not dash -)
    # https://en.wikipedia.org/wiki/Box-drawing_character
#bar=$(seq -s "─" $(($volume/5)) | sed 's/[0-9]//g')
    if [ "$volume" = "0" ]; then
      icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-muted.svg"
$DIR/notify-send.sh "$volume""      " -i "$icon_name" -t 2000 -h int:value:"$volume" -h string:synchronous:"─" --replace=555
    else
	    if [  "$volume" -lt "10" ]; then
	      icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-low.svg"
$DIR/notify-send.sh "$volume""     " -i "$icon_name" --replace=555 -t 2000
    else
        if [ "$volume" -lt "30" ]; then
            icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-low.svg"
        else
            if [ "$volume" -lt "70" ]; then
                icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-medium.svg"
            else
                icon_name="/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-high.svg"
            fi
        fi
    fi
fi
bar=$(seq -s "─" $(($volume/5)) | sed 's/[0-9]//g')
# Send the notification
$DIR/notify-send.sh "$volume""     ""$bar" -i "$icon_name" -t 2000 -h int:value:"$volume" -h string:synchronous:"$bar" --replace=555

}

case $1 in
  up)
    # Set the volume on (if it was muted)
    #pamixer -t
    # Increase volume
    pamixer -i 5
    send_notification
    ;;
  down)
    # Set the volume on (if it was muted)
    #pamixer -t
    # Decrease the volume
    pamixer -d 5
    send_notification
    ;;
  mute)
    # Toggle mute
    pamixer -t
    if is_mute ; then
      DIR=`dirname "$0"`
      $DIR/notify-send.sh -i "/home/kolpona/.icons/BeautyLine/actions/scalable/audio-volume-muted.svg" --replace=555 -u normal "Mute" -t 2000
    else
      send_notification
    fi
    ;;
esac
