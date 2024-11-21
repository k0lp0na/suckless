#!/usr/bin/bash

while true :; do

	status="  $(pamixer --get-volume-human) :$(acpi | awk '{print $4}')  $(date '+%a,%Y-%m-%d  %I:%M %p') "
	xsetroot -name "$status"
	echo "$status"

	sleep 60

done
