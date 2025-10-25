#!/bin/bash

# Redirect stdout and stderr to a log file
exec > ~/startx.log 2>&1

# Keybinds (common to all WMs)
pkill xbindkeys
xbindkeys &

# Set default sink to a reasonable volume
pactl set-sink-volume @DEFAULT_SINK@ 50% 

# Default session is kde-wayland if none is provided as an argument
session=${1:-'dwm'}

case $session in
  dwm)
    # Starting compositor
    pkill picom
    picom -f &
    
    # Set accordingly
    #xrandr --output DP-1 3440x1440 --primary
    #xrandr --output HDMI-1 1920x1080 --left-of DP-1

    # Setting wallpaper
    pkill fehbg_slideshow
    ~/scripts/fehbg_slideshow &

    # Lockscreen
    pkill xautolock
    xautolock -time 10 -locker "slock" -detectsleep &

    # Starting DWM status
    pkill status.sh
    ~/.config/dwm/scripts/status.sh &

    # Start DWM
    exec dwm
    ;;
  cinnamon)
    exec cinnamon-session
    ;;
  *)
    ;;
esac

