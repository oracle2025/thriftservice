#include "MultiplicationService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::tutorial;

class MultiplicationServiceHandler : virtual public MultiplicationServiceIf {
 public:
  MultiplicationServiceHandler() {
    // Your initialization goes here
  }

  int32_t multiply(const int32_t n1, const int32_t n2) {
    // Your implementation goes here
    printf("multiply\n");
    return n1 * n2;
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  auto handler = std::make_shared<MultiplicationServiceHandler>(); //::apache::thrift::stdcxx::shared_ptr<MultiplicationServiceHandler> handler(new MultiplicationServiceHandler());
  //::apache::thrift::stdcxx::shared_ptr<MultiplicationServiceHandler> handler(new MultiplicationServiceHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new MultiplicationServiceProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}


