#pragma once

#include <string>
#include <vector>

class FormatFile
{
public:
  FormatFile(std::string path);
  ~FormatFile();

  unsigned int width();
  unsigned int height();
  unsigned int channels();
  unsigned long long frames();
  
  void frame(unsigned long long position, std::vector<float> & output);

private:
  struct _GstElement * pipeline;
  struct _GstElement * sink;
  int _width;
  int _height;
  unsigned int _channels;
};
