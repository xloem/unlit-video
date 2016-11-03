#pragma once

extern "C" {
#include <gst/gst.h>
}

class Gstreamer
{
public:
  static void handle(GError * & error);
};

template<typename T, void (*unref)(T)>
class Unref
{
public:
  Unref()
  {}

  Unref(T &&value)
  : value(value)
  {}

  operator T &()
  {
    return value;
  }

  ~Unref()
  {
    unref(value);
  }

private:
  T value;
};

using GstSampleRef = Unref<GstSample *, gst_sample_unref>;

