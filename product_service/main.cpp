#include "http_product_server.h"

int main(int argc, char* argv[]) {
  HTTPProductServer app;
  return app.run(argc, argv);
}
