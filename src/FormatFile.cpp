#include "FormatFile.hpp"

#include "FormatUtilGstreamer.hpp"
#include <iostream>
#include <stdexcept>

extern "C" {
#include <gst/gst.h>
}

FormatFile::FormatFile(std::string path)
{
  GError *error = nullptr;

  std::string pipelineStr = "filesrc location=" + path + " ! decodebin ! appsink name=sink";
  pipeline = gst_parse_launch(pipelineStr.c_str(), &error);

  Gstreamer::handle(error);

  sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");

  GstStateChangeReturn scret = gst_element_set_state(pipeline, GST_STATE_PAUSED);
  if (scret != GST_STATE_CHANGE_FAILURE)
    scret = gst_element_get_state(pipeline, nullptr, nullptr, 5 * GST_SECOND);
  if (scret == GST_STATE_CHANGE_FAILURE)
    throw std::runtime_error("failed to play");
}

unsigned long long FormatFile::frames()
{
  int64_t ret;
  gst_element_query_duration(pipeline, GST_FORMAT_DEFAULT, &ret);

  return ret;
}

void FormatFile::frame(unsigned long long position, std::vector<float> & output)
{
  // TODO: this will almost always be used sequentially.  Play the stream rather than seeking.

  gst_element_seek_simple(pipeline, GST_FORMAT_DEFAULT, GST_SEEK_FLAG_FLUSH, position);
  
  GstSampleRef sample;
  g_signal_emit_by_name(sink, "pull-preroll", &sample, nullptr);
  if (!sample) throw std::runtime_error("sample not returned");

  GstCaps * caps = gst_sample_get_caps(sample);
  bool res = true;
  if (caps) {
    GstStructure * s = gst_caps_get_structure(caps, 0);
    res = gst_structure_get_int(s, "width", &_width) | gst_structure_get_int(s, "height", &_height);
  }
  if (res) throw std::runtime_error("could not get frame format");
  
  GstBuffer * buffer = gst_sample_get_buffer(sample);
  
  
}

FormatFile::~FormatFile()
{
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
}
