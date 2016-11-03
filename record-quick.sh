#!/bin/sh
gst-launch-1.0 -v uridecodebin uri=v4l2:// ! video/x-raw ! filesink location=$1
