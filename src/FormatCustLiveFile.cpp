
#include "FormatCustLiveFile.hpp"

extern "C" {
#include <gst/gst.h>
}

FormatCustLiveFile::FormatCustLiveFile(std::string deviceUri)
{
  std::string pipelineStr = "playbin2 uri=" + deviceUri;
  pipeline = gst_parse_launch(pipelineStr.c_str(), nullptr);
}

FormatCustLiveFile::~FormatCustLiveFile()
{
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
}
