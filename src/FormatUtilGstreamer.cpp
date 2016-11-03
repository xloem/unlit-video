#include <stdexcept>
#include <string>

#include "FormatUtilGstreamer.hpp"

class Initializer {
public:
  Initializer()
  {
    gst_init(nullptr, nullptr);
  }
  ~Initializer()
  {
    gst_deinit();
  }
} initializer;

void Gstreamer::handle(GError * & error)
{
  if (error == nullptr)
    return;

  std::string message = error->message;
  g_clear_error(&error);

  throw new std::runtime_error(message);
}

