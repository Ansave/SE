#include "http_cart_server.h"

int main(int argc, char* argv[]) {
  HTTPCartServer app;
  return app.run(argc, argv);
}
