#include <iostream>
#include <memory>
#include <string>
#include <iterator>
#include <map>

#include <grpcpp/grpcpp.h>
#include "gerbil.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using gerbil::Request;
using gerbil::Response;
using gerbil::GerbilRPC;
using gerbil::NdArray;
using google::protobuf::Map;
using google::protobuf::Value;


class GerbilServiceImpl final: public GerbilRPC::Service{
	Status MeanShiftSP(ServerContext* context, const Request* request,
						Response* response) override{
		
		auto ndarray = NdArray();
		ndarray.set_data(NULL);
		ndarray.set_shape(0, 2);
		ndarray.set_shape(1, 2);
		ndarray.set_dtype("float");		
		response->mutable_image()->CopyFrom(ndarray);

		auto map = response->mutable_metainfo();
		auto value = Value();
		value.set_string_value("Cabbage");
		(*map)["Label"] = value;
		return Status::OK;
	}
	// add more rpc below
};

void RunServer(){
	std::string server_address("127.0.0.1:9090");
	GerbilServiceImpl service;
	ServerBuilder builder;

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();

}

int main(){
	RunServer();
	return 0;
}

